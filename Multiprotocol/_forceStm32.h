/*
 This project is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Multiprotocol is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Multiprotocol.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef __arm__
	#define STM32_BOARD	// Let's automatically select this board if arm is selected since this is the only one for now...
	
	/**************************/
	/*** RF CHIPS INSTALLED ***/
	/**************************/
	#define A7105_INSTALLED
	#define CYRF6936_INSTALLED
	#define CC2500_INSTALLED
	#define NRF24L01_INSTALLED
	
	/****************************/
	/*** PROTOCOLS TO INCLUDE ***/
	/****************************/
	//The protocols below need an A7105 to be installed
	#define	JOYSWAY_A7105_INO
	
	#define	FLYSKY_A7105_INO
	#define	HUBSAN_A7105_INO
	#define	AFHDS2A_A7105_INO
	
	//The protocols below need a CYRF6936 to be installed
	#define	DEVO_CYRF6936_INO
	#define	DSM_CYRF6936_INO
	#define	J6PRO_CYRF6936_INO
	#define	WK2x01_CYRF6936_INO
	
	//The protocols below need a CC2500 to be installed
	#define	SKYARTEC_CC2500_INO
	
	#define	FRSKYV_CC2500_INO
	#define	FRSKYD_CC2500_INO
	#define	FRSKYX_CC2500_INO
	#define	SFHSS_CC2500_INO
	
	//The protocols below need a NRF24L01 to be installed
	#define	HM830_NRF24L01_INO
	#define	CFlie_NRF24L01_INO //!\\			//pb voie gaz
	#define	H377_NRF24L01_INO
	#define	ESKY150_NRF24L01_INO
	#define	HonTai_NRF24L01_INO
	#define	UDI_NRF24L01_INO
	#define	NE260_NRF24L01_INO
	#define	BlueFly_NRF24L01_INO	//probleme gene id
	#define	FBL100_NRF24L01_INO	// finir id 				//!\\			//pb voie ???
	#define	INAV_NRF24L01_INO	//	a faire

	#define	BAYANG_NRF24L01_INO
	#define	CG023_NRF24L01_INO
	#define	CX10_NRF24L01_INO		// Include Q2X2 protocol
	#define	ESKY_NRF24L01_INO
	#define	HISKY_NRF24L01_INO
	#define	KN_NRF24L01_INO
	#define	SLT_NRF24L01_INO
	#define	SYMAX_NRF24L01_INO
	#define	V2X2_NRF24L01_INO
	#define	YD717_NRF24L01_INO
	#define	MT99XX_NRF24L01_INO
	#define	MJXQ_NRF24L01_INO
	#define	SHENQI_NRF24L01_INO
	#define	FY326_NRF24L01_INO
	#define	FQ777_NRF24L01_INO
	#define	ASSAN_NRF24L01_INO
	#define	HONTAI_NRF24L01_INO
	#define Q303_NRF24L01_INO
	
	/****************************/
	/*** SERIAL MODE SETTINGS ***/
	/****************************/
	#define ENABLE_SERIAL
	
	/******************************/
	/*** NUNCHUCK MODE SETTINGS ***/
	/******************************/
	#undef ENABLE_NUNCHUCK
	
// replacement map()
int16_t map( int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max)
{
//  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	long y ;
	x -= in_min ;
	y = out_max - out_min ;
	y *= x ;
	x = y / (in_max - in_min) ;
	return x  + out_min ;
}

#endif
