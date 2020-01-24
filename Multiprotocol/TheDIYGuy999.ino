// Origin project : https://github.com/TheDIYGuy999/RC_Transmitter

#if defined(TheDIYGuy999_NRF24L01_INO)

#include "iface_nrf24l01.h"
#define RX_EMPTY    0

const float codeVersion = 2.02; // Software revision


// the ID number of the used "radio pipe" must match with the selected ID on the transmitter!
// 10 ID's are available @ the moment
const uint64_t TheDIYGuy999_pipeOut[] = {
  0xE9E8F0F0B1LL, 0xE9E8F0F0B2LL, 0xE9E8F0F0B3LL, 0xE9E8F0F0B4LL, 0xE9E8F0F0B5LL,
  0xE9E8F0F0B6LL, 0xE9E8F0F0B7LL, 0xE9E8F0F0B8LL, 0xE9E8F0F0B9LL, 0xE9E8F0F0B0LL
};
uint64_t TheDIYGuy999_pipeOutCalc;
// Radio channels (126 channels are supported)
byte chPointer = 0; // Channel 1 (the first entry of the array) is active by default
const byte TheDIYGuy999_Chanel[] {
  1, 2
};
#define TheDIYGuy999_optOffset	150
#define TheDIYGuy999_PACKET_SIZE		8

// This struct defines data, which are embedded inside the ACK payload
struct TheDIYGuy999_ackPayload {
  float vcc; // vehicle vcc voltage
  float batteryVoltage; // vehicle battery voltage
  boolean batteryOk; // the vehicle battery voltage is OK!
  byte channel = 1; // the channel number
};
TheDIYGuy999_ackPayload TheDIYGuy999_payload;

RX_num

//================================================================================================
uint16_t initTheDIYGuy999()
{
	RX_num = RX_num % 40;
	TheDIYGuy999_pipeOutCalc = TheDIYGuy999_pipeOut[RX_num%10];
	if((RX_num%10) & 1) TheDIYGuy999_pipeOutCalc -= 1<<5;     // 10
	if(RX_num>=20)   TheDIYGuy999_pipeOutCalc -= 1<<33;  // 20
	
	NRF24L01_Initialize();
	NRF24L01_SetTxRxMode(TX_EN);
	hopping_frequency_no = 0;
	NRF24L01_WriteReg(NRF24L01_05_RF_CH, TheDIYGuy999_Chanel[hopping_frequency_no]);
	
	NRF24L01_SetPower();
	
	NRF24L01_SetBitrate(NRF24L01_BR_250K);
	NRF24L01_WriteReg(NRF24L01_1D_FEATURE, NRF24L01_ReadReg(NRF24L01_1D_FEATURE) | _BV(NRF2401_1D_EN_ACK_PAY) | _BV(NRF2401_1D_EN_DPL));      //  Auto Acknoledgement
	NRF24L01_WriteReg(NRF24L01_01_EN_AA, 0x01);      //  Auto Acknoledgement
	write_register(NRF24L01_04_SETUP_RETR,(5&0xf)<<4 | (5&0xf)<<0);	//	retry
	
	// openpipe
	NRF24L01_WriteRegisterMulti(NRF24L01_0A_RX_ADDR_P0, reinterpret_cast<uint8_t*>(TheDIYGuy999_pipeOutCalc), 5);
	NRF24L01_WriteRegisterMulti(NRF24L01_0B_RX_ADDR_P1, reinterpret_cast<uint8_t*>(TheDIYGuy999_pipeOutCalc), 5);
	NRF24L01_WriteRegisterMulti(NRF24L01_10_TX_ADDR,    reinterpret_cast<uint8_t*>(TheDIYGuy999_pipeOutCalc), 5);
	NRF24L01_WriteReg(NRF24L01_11_RX_PW_P0, TheDIYGuy999_PACKET_SIZE);

	
//================================================================================================
	return 1500;
}

uint16_t TheDIYGuy999_callback()
{
	packet[0]  = map(Channel_data[AILERON], CHANNEL_MIN_125, CHANNEL_MAX_125, 0, 100);
	packet[1]  = map(Channel_data[ELEVATOR], CHANNEL_MIN_125, CHANNEL_MAX_125, 0, 100);
	packet[2]  = map(Channel_data[THROTTLE], CHANNEL_MIN_125, CHANNEL_MAX_125, 0, 100);
	packet[3]  = map(Channel_data[RUDDER], CHANNEL_MIN_125, CHANNEL_MAX_125, 0, 100);
	packet[4]  = (CH5_SW)?1:0;	//	mode1
	packet[5]  = (CH6_SW)?1:0;	//	mode2
	packet[6]  = (CH7_SW)?1:0;	//	momentary
	packet[7]  = map(Channel_data[CH8], CHANNEL_MIN_125, CHANNEL_MAX_125, 0, 100);	//	potar

	if (CH9_SW)
		packet[3] = packet[3] + TheDIYGuy999_optOffset;
	if (CH10_SW)
		packet[1] = packet[1] + TheDIYGuy999_optOffset;

	NRF24L01_SetPower();
	
    // Send radio data and check if transmission was successful
	NRF24L01_WritePayload(packet, TheDIYGuy999_PACKET_SIZE);
	if( ! (NRF24L01_ReadReg(NRF24L01_17_FIFO_STATUS) & _BV(RX_EMPTY))) {
        NRF24L01_ReadPayload(&TheDIYGuy999_payload, sizeof(struct TheDIYGuy999_ackPayload)); // read the payload, if available
		NRF24L01_WriteReg(NRF24L01_07_STATUS, 255);
		NRF24L01_FlushRx();
		
		// Switch channel for next transmission
		hopping_frequency_no ++;
		if (hopping_frequency_no >= sizeof((*TheDIYGuy999_Chanel) / sizeof(byte))) hopping_frequency_no = 0;
		NRF24L01_WriteReg(NRF24L01_05_RF_CH, TheDIYGuy999_Chanel[hopping_frequency_no]);
		
		v_lipo1 = TheDIYGuy999_payload.batteryVoltage;
		v_lipo2 = TheDIYGuy999_payload.vcc;
		RX_RSSI = TheDIYGuy999_payload.channel;
		
	}
	
	//================================================================================================
    return 10;
}

#endif
