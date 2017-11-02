/*
 This project is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Deviation is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Deviation.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef E012_NRF24L01_INO

#include "iface_nrf24l01.h"

#define E012_BIND_COUNT 500
#define dbgprintf if(0) printf

// stock Tx has 4525us interval between packets
// we send at higher rate to mitigate hs6200 having 
// a hard time to decode packets sent by a nrf24l01
#define E012_PACKET_PERIOD       1000
#define E012_INITIAL_WAIT        500
#define E012_ADDRESS_LENGTH      5
#define E012_NUM_RF_CHANNELS     4
#define E012_PACKET_SIZE         15

static uint8_t tx_addr[E012_ADDRESS_LENGTH];

enum {
    BIND,
    DATA
};

static void __attribute__((unused)) E012_send_packet(uint8_t bind)
{
	packet[0] = rx_tx_addr[1];
	if(bind) {
		packet[1] = 0xaa;
		memcpy(&packet[2], hopping_frequency, E012_NUM_RF_CHANNELS);
		memcpy(&packet[6], rx_tx_addr, E012_ADDRESS_LENGTH);
	}
	else {
		packet[1] = 0x01
				| GET_FLAG(Servo_AUX3, 0x04)	//RTH
				| GET_FLAG(Servo_AUX2, 0x10)	//HEADLESS
				| GET_FLAG(Servo_AUX1, 0x40);	// flip
		packet[2] = convert_channel_8b_scale(AILERON, 0xc8, 0x00);
		packet[3] = convert_channel_8b_scale(ELEVATOR, 0x00, 0xc8);
		packet[4] = convert_channel_8b_scale(RUDDER, 0xc8, 0x00);
		packet[5] = convert_channel_8b_scale(THROTTLE, 0x00, 0xc8);
		packet[6] = 0xaa;
		packet[7] = 0x02; // rate (0-2)
		packet[8] = 0x00;
		packet[9] = 0x00;
		packet[10]= 0x00;
	}
	packet[11] = 0x00;
	packet[12] = 0x00;
	packet[13] = 0x56; 
	packet[14] = rx_tx_addr[2];
	
	// Power on, TX mode, CRC enabled
	HS6200_Configure(_BV(NRF24L01_00_EN_CRC) | _BV(NRF24L01_00_CRCO) | _BV(NRF24L01_00_PWR_UP));
	NRF24L01_WriteReg(NRF24L01_05_RF_CH, bind ? 0x3c : hopping_frequency[hopping_frequency_no++]);
	hopping_frequency_no %= E012_NUM_RF_CHANNELS;
	
	NRF24L01_WriteReg(NRF24L01_07_STATUS, 0x70);
	NRF24L01_FlushTx();
	
	HS6200_WritePayload(packet, E012_PACKET_SIZE);
}

static void __attribute__((unused)) E012_init()
{
	NRF24L01_Initialize();
	NRF24L01_SetTxRxMode(TX_EN);
	HS6200_SetTXAddr((uint8_t *)"\x55,\x42,\x9C,\x8F,\xC9", E012_ADDRESS_LENGTH);
	NRF24L01_FlushTx();
	NRF24L01_FlushRx();
	NRF24L01_WriteReg(NRF24L01_07_STATUS, 0x70);     // Clear data ready, data sent, and retransmit
	NRF24L01_WriteReg(NRF24L01_01_EN_AA, 0x00);      // No Auto Acknowldgement on all data pipes
	NRF24L01_WriteReg(NRF24L01_03_SETUP_AW, 0x03);
	NRF24L01_WriteReg(NRF24L01_04_SETUP_RETR, 0x00); // no retransmits
	NRF24L01_SetBitrate(NRF24L01_BR_1M);             // 1 Mbps
	NRF24L01_SetPower();
	NRF24L01_Activate(0x73);                          // Activate feature register
	NRF24L01_WriteReg(NRF24L01_1C_DYNPD, 0x00);       // Disable dynamic payload length on all pipes
	NRF24L01_WriteReg(NRF24L01_1D_FEATURE, 0x01);     // Set feature bits on
	NRF24L01_Activate(0x73);
}

static void __attribute__((unused)) E012_initialize_txid()
{
	// rf channels 
	// hack: use only 1 out of 4 channels as it seems the hs6200
	// has a hard time decoding packets sent by the nrf24l01
	for(int8_t i=0; i<E012_NUM_RF_CHANNELS; i++) {
		//hopping_frequency[i] = 0x30 + (((MProtocol_id >> (i*8)) & 0xff) % 0x21); 
		hopping_frequency[i] = MProtocol_id % 0x51; // hack
	}
}

static uint16_t E012_callback()
{
	if (IS_BIND_DONE_on) 
		E012_send_packet(0);
	else {
		if (bind_counter == 0) {
			HS6200_SetTXAddr(rx_tx_addr, 5);
			phase = DATA;
			BIND_DONE;
		} else {
			E012_send_packet(1);
			bind_counter--;
		}
	}
	return E012_PACKET_PERIOD;
}

static uint16_t initE012()
{
	BIND_IN_PROGRESS;	// autobind protocol
	E012_initialize_txid();
	E012_init();
	bind_counter = E012_BIND_COUNT;
	hopping_frequency_no = 0;
	return E012_INITIAL_WAIT+E012_PACKET_PERIOD;
}

#endif
