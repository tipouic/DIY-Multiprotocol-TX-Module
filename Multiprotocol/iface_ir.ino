/*
 This project is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 IrTxAdapter is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License 
 if not, see <http://www.gnu.org/licenses/>.
 
 */

 #ifdef tx_ir
#define IR_CLOCK_RATE 38000L
#define IR_HIGH TCCR2A &= ~_BV(COM2A1)
#define IR_LOW TCCR2A |= _BV(COM2A1)

#define idf 0x5475c52a

void irSend() {
	// delay between 2 packets must be 40ms minimum in CPPM mode
	switch(sub_protocol) {
		case SH_602X:		irSHsendPacket(shBuildPacket());	break;
		case SYMA_S107_32:	irSYsendPacket(syBuildPacket());	break;
		case WLTOYS_IR:		irWLsendPacket(wlBuildPacket());	break;
		default: ;
	}
}

void ir_init () {
	pinMode(IR_PIN, OUTPUT);
	digitalWrite(IR_PIN, LOW);
	// setup IR carrier
	TCCR2A = _BV(WGM20);
	#if IR_PIN == 3
		byte s = 8000 / (IR_CLOCK_RATE / 1000);
	#elif IR_PIN == 11 
		byte s = 8000 / ((IR_CLOCK_RATE<<1) / 1000);
		TCCR2A |= _BV(COM2A0);
	#endif
	TCCR2B = _BV(WGM22) | _BV(CS20);
	OCR2A = s;
	OCR2B = s >> 1;
}

// Syma "genuine" S107(g) IR protocol:
/*
 carrier frequency: 38kHz or 57KHz
 (all timings in �s)
 constant packet length
 header: 2000 pulse, 2000 space, 1000 pulse
 zero: 380 pulse, 220 space
 one: 320 pulse, 600 space
 end: 140000 space
 length of data: 32 bits

    byte0  |   byte1   |   byte 2  |   byte3
 A BBBBBBB | C DDDDDDD | E FFFFFFF | I JJJJJJJ

 A = always 0
 B = yaw (127=full left - 0=full right) center depends of yaw trim
 C = always 0
 D = pitch (127=full backward, 0=full forward)
 E = band (1=A, 0=B ?)
 F = throttle (0-127)
 I = always 0
 J = yaw trim (127=full left, 0=full right), looks like the RX does not use this value, but the TX use it internally to adjust yaw center and window 

*/

enum {
	SYBAND_A = (uint8_t)0x80,
	SYBAND_B = (uint8_t)0x00	
};
void irSYsendHeader() {	IR_HIGH;	delayMicroseconds(2000);	IR_LOW;	delayMicroseconds(2000);	IR_HIGH; }
void irSYsendZero() {	IR_HIGH;	delayMicroseconds(380);		IR_LOW;	delayMicroseconds(220);		IR_HIGH; }
void irSYsendOne() {	IR_HIGH;	delayMicroseconds(320);		IR_LOW;	delayMicroseconds(600);		IR_HIGH; }
void irSYsendPacket(uint32_t packet) {
	noInterrupts();
	irSYsendHeader();
	for(uint8_t b=32; b>0; b--) { if( packet & (uint32_t)1<<(b-1)) { irSYsendOne(); } else { irSYsendZero(); }}
	delayMicroseconds(380);
	IR_LOW;
	interrupts();
	delay(100);
}
uint32_t syBuildPacket() {
	int8_t packet[4]={0,0,0,0};
	packet[1] = map(Servo_data[ELEVATOR], servo_min_100, servo_max_100, 127, 0);
	packet[2] = SYBAND_A | map(Servo_data[THROTTLE], servo_min_100, servo_max_100, 0, 127);
	packet[3] = map(Servo_data[AUX1], servo_min_100, servo_max_100, 127, 0);
	int16_t yaw_center = map( packet[3], 0, 127, 45, 82);
	bool windowed=true;
#ifdef DYNAMIC_RUDDER_TRIM
	windowed=false;
#endif
	if(Servo_data[RUDDER] <= servo_mid)
		packet[0] = map( Servo_data[RUDDER], servo_min_100, servo_mid, windowed ? constrain(yaw_center+45, 0, 127) : 127, yaw_center);
	else
		packet[0] = map( Servo_data[RUDDER], servo_mid, servo_max_100, yaw_center, windowed ? constrain(yaw_center-45, 0, 127) : 0);
	return (uint32_t)(((uint32_t)packet[0]<<24) | ((uint32_t)packet[1]<<16) | ((uint16_t)packet[2]<<8) | packet[3]);
}

// San Huan 602x IR protocol:
/*
 carrier frequency: 38kHz
 (all timings in µs)
 constant packet length
 header: 3750 pulse, 1000 space
 zero: 700 pulse, 300 space
 one: 300 pulse, 700 space
 end: 40000 space
 length of data: 32 bits

    byte0  |   byte1   |    byte 2   |   byte3
 A BBBBBBB | CCCC DDDD | E F G HHHHH | II JJJJJJ

 A = always 0
 B = throttle (0-120)
 C = yaw (0-15, 0 is neutral)
 D = pitch (0-15, 0 is neutral)
 E = yaw direction  1=left rudder, 0=right rudder
 F = pitch direction  1=nose up, 0=nose down
 G = yaw trim direction  1=trim left, 0=trim right
 H = yaw trim (0-31)
 I = band 11=A, 10=B, 01=C
 J = checksum ((byte0 + byte1 + byte2 + 0x0F) & 0x3F)

*/
enum {
	SHBAND_A = (uint8_t)0xc0,
	SHBAND_B = (uint8_t)0x80,
	SHBAND_C = (uint8_t)0x40
};
void irSHsendHeader() {	IR_HIGH;	delayMicroseconds(3750);	IR_LOW;	delayMicroseconds(1000);	IR_HIGH; }
void irSHsendZero() {	IR_HIGH;	delayMicroseconds(700); 	IR_LOW;	delayMicroseconds(300); 	IR_HIGH; }
void irSHsendOne() {	IR_HIGH;	delayMicroseconds(300);		IR_LOW;	delayMicroseconds(700);		IR_HIGH; }
void irSHsendPacket(uint32_t packet) {
	noInterrupts();
	irSHsendHeader();
	for(uint8_t b=32; b>0; b--) { if( packet & (uint32_t)1<<(b-1)) { irSHsendOne(); } else { irSHsendZero(); }}
	IR_LOW;
	interrupts();
	delay(40);
}
uint32_t shBuildPacket() {
	uint8_t packet[4] = {0,0,0,0};
	packet[0] = map(Servo_data[THROTTLE], servo_min_100, servo_max_100, 0, 120); // throttle
	packet[1] = map(Servo_data[RUDDER], servo_mid, Servo_data[RUDDER] > servo_mid ? servo_max_100 : servo_min_100, 0, 15) << 4; // yaw
	packet[1] |= map(Servo_data[ELEVATOR], servo_mid, Servo_data[ELEVATOR] > servo_mid ? servo_max_100 : servo_min_100, 0, 15); // pitch
	if( Servo_data[AUX1] > servo_mid)
		packet[2] |= (1<<5); // yaw trim direction
	packet[2] |= map(Servo_data[AUX1], servo_mid, Servo_data[AUX1] > servo_mid ? servo_max_100 : servo_min_100, 0, 31); // yaw trim
#if DYNAMIC_RUDDER_TRIM	
	int yawtrim = Servo_data[AUX1]<servo_mid ? (int)-(packet[2] & 0x1F) : (int)(packet[2] & 0x1F); // [-31;31]
	packet[2] &= ~0x3F;
	if(Servo_data[RUDDER]<servo_mid) 
		yawtrim = map(Servo_data[RUDDER], servo_min_100, servo_mid, -31, yawtrim); 
	else
		yawtrim = map(Servo_data[RUDDER], servo_max_100,  servo_mid, 31, yawtrim);
	if(yawtrim <=0)
		packet[2] |= (1<<5);
	packet[2] |= abs(yawtrim) & 0x1F;
#endif
	if( Servo_data[RUDDER] <= servo_mid)
		packet[2] |= (1<<7); // yaw direction
	if( Servo_data[ELEVATOR] <= servo_mid)
		packet[2] |= (1<<6); // pitch direction
	packet[3] = SHBAND_A | ((packet[0] + packet[1] + packet[2] + 0x0F) & 0x3F); // band + checksum
	return (uint32_t)(((uint32_t)packet[0]<<24) | ((uint32_t)packet[1]<<16) | ((uint16_t)packet[2]<<8) | packet[3]);
}

// WLToys EV-05
/*
 32 bits, transition time encoding
 
 header = 1400�s
 zero = 300 �s
 one = 800 �s
 70ms between packets
 
 ATTTTTTT YYYYPPPP XX?????? ?D?BCCCC

 A = 0, 1 if 0% throttle
 T = throttle ( 0 - 127 )
 Y = yaw ( left = 1, center = 8, right = 15 )
 P = pitch ( backward = 1, center = 8, forward = 15)
 X = band ( A = 01, B = 10, C = 11 )
 D = boost ( 1 = on )
 B = bubbles ( 1 = on )
 C = checksum = (N1+N2+N3+N4+N5+N6+N7+1)%16
 TODO : checksum calculation is wrong, sometimes the result should be 1 less
*/
uint32_t wlBuildPacket() {
	uint8_t packet[4] = {0,0,0,0};
	
	// throttle
	packet[0] = map(Servo_data[THROTTLE], servo_min_100, servo_max_100, 0, 127);
	if(packet[0] <5 ) // idle
		return (int32_t) 0b10000000100010000100000000001100; // as captured
		//packet[0] |= 0x80;
	// yaw
	packet[1] = map(Servo_data[RUDDER], servo_min_100, servo_max_100, 1, 15) << 4;
	// pitch
	packet[1] |= map(Servo_data[ELEVATOR], servo_min_100, servo_max_100, 1, 15);
	// unknown (band + ???)
	packet[2] |= 64; // BAND A
	// options
	// TODO: add channel/buttons for boost, leds, bubbles ...
	
	uint8_t checksum = (((packet[0]>>4)&0x0F) + (packet[0]&0x0F) + ((packet[1]>>4)&0x0F) + (packet[1]&0x0F) + 
	                ((packet[2]>>4)&0x0F) + (packet[2]&0x0F) + ((packet[3]>>4)&0x0F) + 1 ) % 16;  
	packet[3] |= checksum;
	return (uint32_t)(((uint32_t)packet[0]<<24) | ((uint32_t)packet[1]<<16) | ((uint16_t)packet[2]<<8) | packet[3]);
}
void irWLsendPacket(uint32_t packet) {
	noInterrupts();
	bool state = false;
	// header
	IR_HIGH;
	delayMicroseconds(1450);
	IR_LOW;
	// packet
	for(uint8_t b=32; b>0; b--) {
		if( packet & (uint32_t)1<<(b-1)) { delayMicroseconds(state ? 800 : 800); }
		else { delayMicroseconds(state ? 350 : 300); }
		if(state) {
			IR_LOW;	
			state=false;
		} else {
			IR_HIGH;
			state=true;
		}
	}
	IR_LOW;
	interrupts();
	delay(70);
}

#endif