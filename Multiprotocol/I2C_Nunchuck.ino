#ifdef ENABLE_NUNCHUCK
#include <Wire.h>

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 3, NEO_GRB + NEO_KHZ800);

#define BUZZER_INIT LOW
const uint8_t color[] = {
//	rouge	vert	bleu	intensité
	0,		255,	0,		200,	// 	VERT		
	255,	255,	0,		200,	// 	rouge		
	0,		0,		255,	200,	// 	BLEU		
	255,	255,	255,	200,	//  BLANC		
	255,	255,	0,		200,	// 	jaune		
};
#define COLOR_WRITE(nb) strip.setPixelColor(0, color[nb*4], color[nb*4+1], color[nb*4+2]); strip.setBrightness(color[nb*4+3]); strip.show()

#define SEUIL_B 10
#define SEUIL_H 245
uint8_t batteryTX = 255;

#define WII_NUNCHUK_I2C_ADDRESS 0x52	// adresse I2C du nunchuck
uint8_t data[6];  //nunchuck
int chan;	//id data
int num_model=0;
int num_trim[] = {0,0};

uint8_t tpsc=0, tpsz=0;
boolean c=false, z=false,	 cl=false, op=true, zl=false;

int menu=1;	// default hold trottle
#define eeprom_model 5
#define eeprom_base 40

uint8_t nunchuck_flags=0;
#define CHG_DP_FLAG_on			nunchuck_flags |= _BV(0)
#define CHG_DP_FLAG_off			nunchuck_flags &= ~_BV(0)
#define IS_CHG_DP_FLAG_on		( ( nunchuck_flags & _BV(0) ) !=0 )
//
#define INV_D_FLAG_on		nunchuck_flags |= _BV(1)
#define INV_D_FLAG_off		nunchuck_flags &= ~_BV(1)
#define IS_INV_D_FLAG_on	( ( nunchuck_flags & _BV(1) ) !=0 )
//
#define INV_P_FLAG_on		nunchuck_flags |= _BV(2)
#define INV_P_FLAG_off		nunchuck_flags &= ~_BV(2)
#define IS_INV_P_FLAG_on	( ( nunchuck_flags & _BV(2) ) !=0 )
//
#define INV_A_FLAG_on		nunchuck_flags |= _BV(3)
#define INV_A_FLAG_off		nunchuck_flags &= ~_BV(3)
#define IS_INV_A_FLAG_on	( ( nunchuck_flags & _BV(3) ) !=0 )
//
#define POS_MID_FLAG_on		nunchuck_flags |= _BV(4)
#define POS_MID_FLAG_off	nunchuck_flags &= ~_BV(4)
#define IS_POS_MID_FLAG_on	( ( nunchuck_flags & _BV(4) ) !=0 )
//
#define DUAL_FLAG_on		nunchuck_flags |= _BV(5)
#define DUAL_FLAG_off	nunchuck_flags &= ~_BV(5)
#define IS_DUAL_FLAG_on	( ( nunchuck_flags & _BV(5) ) !=0 )
//
#define BIVOIE_on		nunchuck_flags |= _BV(5)
#define BIVOIE_off	nunchuck_flags &= ~_BV(5)
#define IS_BIVOIE_on	( ( nunchuck_flags & _BV(5) ) !=0 )

// Channel value is converted to 16bit values
uint16_t convert_channel_16b(uint16_t num, boolean inv=false) {
	if(inv) {
		return (uint16_t) (map(num,servo_max_125,servo_min_125,SERIAL_MIN_125,SERIAL_MAX_125));
	} else {
		return (uint16_t) (map(num,servo_min_125,servo_max_125,SERIAL_MIN_125,SERIAL_MAX_125));
	}
}

#define DIVISOR_PERCENTS (32)
#define PERCENT_TO_BYTE(P) ((int8_t)((((int)P) * DIVISOR_PERCENTS) / 100))
#define BYTE_TO_PERCENT(P) ((int8_t)((((int)P) * 100) / DIVISOR_PERCENTS))
int16_t expo(int8_t a, int32_t x) {
  return (((BYTE_TO_PERCENT(a) * x  * x) / 100) * x) / (((int32_t)servo_max_125) * servo_max_125) + (100 - BYTE_TO_PERCENT(a)) * x / 100;
}


void nunchuck_init() {
	analogReference(INTERNAL);
	pinMode(BUZZER_PIN, OUTPUT);	digitalWrite(BUZZER_PIN, BUZZER_INIT);
	
	
	/**  Interrupt routines  **/
	TCCR2A = 0b00000010;													//	COM 2A1, 2A0, 2B1, 2B0, - , - , WGM21, WGM20
	TCCR2B = 0b00000110;	// Clock / 256 soit 16 micro-s et WGM22 = 0		// FOC2A, FOC2B, -  , - , WGM22, CS22, CS21, CS20
	TIMSK2 = 0b00000010;	// Interruption locale autorisée par OCIE2A		// -  , - , -  , - , - , OCIE2B, OCIE2A, TOIE2
	OCR2A = 250;			// Interruption du compte à ...
	sei();					// autorisation générale des interruptions
	
	
	strip.begin();
	COLOR_WRITE(0);
//		strip.setPixelColor(0, color[0], color[0+1], color[0+2]); strip.setBrightness(color[0+3]); strip.show();
		
	Wire.begin();
	
	Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
	Wire.write(0xF0);
	Wire.write(0x55);
	Wire.endTransmission();
	
	Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
	Wire.write(0xFB);
	Wire.write(0x00);
	Wire.endTransmission();
	nunchuck_read();
	nunchuck_read();
	
	nunchuck_proto_config(0);
	nunchuck_proto();
}

void nunchuck_proto_config(int config) {
	// sav proto	/	model
	if(config == 1) {
		eeprom_write_byte(eeprom_model, num_model);
		eeprom_write_byte(eeprom_base + num_model*5, MODE_SERIAL);
	} else
	// sav config
	if(config == 2) {
		eeprom_write_byte(eeprom_base + num_model*5 + 1, nunchuck_flags);
		eeprom_write_byte(eeprom_base + num_model*5 + 2, num_trim[0]);
		eeprom_write_byte(eeprom_base + num_model*5 + 3, num_trim[1]);
	} else
	//	lecture
	{
		num_model = eeprom_read_byte(eeprom_model);
		MODE_SERIAL = eeprom_read_byte(eeprom_base + num_model*5);
		nunchuck_flags = eeprom_read_byte(eeprom_base + num_model*5 + 1);
		num_trim[0] = eeprom_read_byte(eeprom_base + num_model*5 + 2);
		num_trim[1] = eeprom_read_byte(eeprom_base + num_model*5 + 3);
	}
}
void nunchuck_proto() {
	if(mode_select == MODE_SERIAL) {	mode_select=0;	} 
	else {
		LED_off;				//led off during protocol init
		modules_reset();		//reset all modules
		mode_select--;
	}
	protocol		=	NUN_prot[mode_select].protocol;
	cur_protocol[1] = protocol;
	sub_protocol   	=	NUN_prot[mode_select].sub_proto;
	RX_num			=	0;
	if(NUN_prot[mode_select].rx_num != 0 ) { nbChannel = NUN_prot[mode_select].rx_num; }	// default 4
	option			=	NUN_prot[mode_select].option;
	if(NUN_prot[mode_select].power)		POWER_FLAG_on;
	if(NUN_prot[mode_select].autobind)	AUTOBIND_FLAG_on;
	mode_select++;
	
	modules_reset();
	protocol_init();
}

void nunchuck_read() {
	// on demande 6 octets au nunchuck
	Wire.requestFrom(WII_NUNCHUK_I2C_ADDRESS, 6);

	chan = 0;
	// tant qu'il y a des donnees
	while(Wire.available()) { data[chan++] = Wire.read(); } // on recupere les donnees

	// on reinitialise le nunchuck pour la prochaine demande
	Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
	Wire.write(0x00);
	Wire.endTransmission();
}
void nunchuck_update() {
	nunchuck_read();
	if(chan >= 5) {
		// on extrait les donnees
		int JX = data[0];
		int JY = data[1];
		double accelX = (data[2] << 2) + ((data[5] & (3 << 2 ) >> 2)) >> 2;	//droite / gauche
		double accelY = (data[3] << 2) + ((data[5] & (3 << 4 ) >> 4)) >> 2;	// av / ar
		double accelZ = (data[4] << 2) + ((data[5] & (3 << 6 ) >> 6)) >> 2;	// haut / bas
		
		//	test touche pause
		if((data[5] >> 1) & 1) { tpsz++; }
		else if(tpsz>300) {
			if(menu==0) {	menu = 1;	}
			else if(menu==1 && (IS_POS_MID_FLAG_on && JY==127 or JY==0)) {	menu = 0;	}
			Servo_data[THROTTLE] = (IS_POS_MID_FLAG_on) ? (SERIAL_MIN_125+SERIAL_MAX_125)/2 : SERIAL_MIN_125;
			COLOR_WRITE(menu);
			tpsz=0;
		}
		
		//	attente retour au neutre pour les menus (evite fausse entree)
		if(zl) { if(JX<SEUIL_H && JX>SEUIL_B && JY<SEUIL_H && JY>SEUIL_B && !((data[5] >> 0) & 1) && !((data[5] >> 1) & 1)) { zl = false; } }
		//	fonctionnement normal (TX)
		else if(menu == 0) {
			// calcul appuis long sur boutton
			if((data[5] >> 0) & 1) { tpsc++; }	// compte temps
			else if(tpsc>300) { cl=!cl;	tpsc=0; }	// RAZ tps + déclaration appuis LONG
			else if(tpsc>10) { c=!c;	tpsc=0; }	// RAZ tps + déclaration appuis COURT
			else { tpsc=0; }	// RAZ tps
			
			if(tpsz>10) { z=!z;	tpsz=0; }
			if(IS_BIVOIE_on) {
				//			 acc						joystick
				if(cl) {	JY = accelY; 	}	else {	accelX = JX;	}
				JX = 0;
				accelY = num_trim[0] + JY*num_trim[1]/100;
			}
		
			Servo_data[THROTTLE]	=	convert_channel_16b(JY);
		}
		//	secu moteur
		else if(menu == 1 && ((data[5] >> 0) & 1)) {
			// appuis C
			if((data[5] >> 0) & 1) { tpsc++; } else if(tpsc<10) { tpsc=0; }	// RAZ tps
			
			if(tpsc>10) { tpsc=0; zl=true; menu++; COLOR_WRITE(menu); }
		}
		//	menu principal
		else if(menu == 2) {
			// appuis C
			if((data[5] >> 0) & 1) { tpsc++; } else if(tpsc<10) { tpsc=0; }	// RAZ tps
			
			// edit servo
			if(JX > SEUIL_H)	{
				// active option bivoies
				if(tpsz>10) { tpsz=0; zl=true; if(IS_BIVOIE_on) { BIVOIE_off; } else { BIVOIE_on; } nunchuck_proto_config(2); } else
				// position gaz (bas / milieu)
				if(tpsc>10) { tpsc=0; zl=true; if(IS_POS_MID_FLAG_on) { POS_MID_FLAG_off; } else { POS_MID_FLAG_on; } nunchuck_proto_config(2); } else
				if(accelX > SEUIL_H)	{ zl=true; if(IS_INV_D_FLAG_on) { INV_D_FLAG_off; } else { INV_D_FLAG_on; } nunchuck_proto_config(2); } else
				if(accelX < SEUIL_B)	{ zl=true; if(IS_CHG_DP_FLAG_on) { CHG_DP_FLAG_off; } else { CHG_DP_FLAG_on; } nunchuck_proto_config(2); } else
				if(accelY > SEUIL_H)	{ zl=true; if(IS_INV_P_FLAG_on) { INV_P_FLAG_off; } else { INV_P_FLAG_on; } nunchuck_proto_config(2); } else
				// trim JX
				if(accelY < SEUIL_B)	{
					zl=true;
					menu = 3;
					COLOR_WRITE(menu);
				}
			} else	
			// model		*****
			if(JY < SEUIL_B)	{
				if(accelX > SEUIL_H)	{ zl=true; num_model++; nunchuck_proto_config(1); } else
				if(accelX < SEUIL_B)	{ zl=true; num_model--; nunchuck_proto_config(1); } else
				
				if(accelY > SEUIL_H)	{ zl=true; mode_select++; nunchuck_proto_config(1); } else
				if(accelY < SEUIL_B)	{ zl=true; mode_select--; nunchuck_proto_config(1); }
			} else	
			// rebind
			if(JY > SEUIL_H)	{ zl=true; CHANGE_PROTOCOL_FLAG_on;	} else
			// option
			if(JX < SEUIL_B)	{  }
			if(tpsc > 300) {	zl=true; menu = 1;	COLOR_WRITE(menu);	}
			
			
		}
		//	menu servo
		else if(menu == 3 || menu == 4) {
			// appuis C
			if((data[5] >> 0) & 1) { tpsc++; } else if(tpsc<10) { tpsc=0; }	// RAZ tps
			if(tpsc>10) {	zl=true; menu = 2;	COLOR_WRITE(menu); nunchuck_proto_config(2);	}
			
			num_trim[menu-3] = JX;
			accelY = num_trim[menu-3];
		}
		
		//	sortie
		if(IS_CHG_DP_FLAG_on){
			Servo_data[RUDDER]		=	convert_channel_16b(accelY, IS_INV_P_FLAG_on);
			Servo_data[ELEVATOR]	=	convert_channel_16b(accelX, IS_INV_D_FLAG_on);
		}
		else {
			Servo_data[ELEVATOR]	=	convert_channel_16b(accelY, IS_INV_P_FLAG_on);
			Servo_data[RUDDER]		=	convert_channel_16b(accelX, IS_INV_D_FLAG_on);
		}
		Servo_data[AILERON]			=	convert_channel_16b(JX, IS_INV_A_FLAG_on);
		Servo_data[AUX1]			=	(z) ? SERIAL_MIN_100 : SERIAL_MAX_100;
		Servo_data[AUX2]			=	(c) ? SERIAL_MIN_100 : SERIAL_MAX_100;
		Servo_data[AUX3]			=	(cl)? SERIAL_MIN_100 : SERIAL_MAX_100;
	}
}

/**  Interrupt routines  4ms **/
ISR (TIMER2_OVF_vect) {
	batteryTX = map(analogRead(VBAT_PIN), 0,1023, 0,430);
	if(batteryTX < VBAT_LIM) {			digitalWrite(BUZZER_PIN, !BUZZER_INIT);	}
	else if(batteryTX < VBAT_VAL) {		digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));	}
	nunchuck_update();
}
#endif