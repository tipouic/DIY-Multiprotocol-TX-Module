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

/**********************************************/
/** Nunchuck configuration file ***/
/**********************************************/
//In this section you can configure the NUNCHUCK.
//If you do not plan to use the NUNCHUCK mode comment this line using "//" to save Flash space, you don't need to configure anything below in this case
//#define ENABLE_NUNCHUCK
#define NUNCHUCK_125 110
#define NUNCHUCK_100 90
//	pont diviseur		VCC ------- 240K ------- analogRead(3) ------- 75K ------- GND
#define VBAT_PIN 3 // for Tx adapters with battery
#define VBAT_VAL 340 // for Tx adapters with battery (attention pont divisieur pour avoir 1,1V max ,~=3,404V)
#define VBAT_LIM 330 // for Tx adapters with battery (attention pont divisieur pour avoir 1,1V max , ~=3,302V)
#define BUZZER_PIN 14	//A0

// Attention, fill in the parameter table PPM

/****************/
/*** RF CHIPS ***/
/****************/
//There are 4 RF components supported. If one of them is not installed you must comment it using "//".
//If a chip is not installed all associated protocols are disabled.
//4-in-1 modules have all RF chips installed
//!!!If a RF chip is present it MUST be marked as installed!!! or weird things will happen you have been warned.
// #define LEDIR_INSTALLED

#define A7105_INSTALLED
// #define CC2500_INSTALLED
// #define CYRF6936_INSTALLED	// attention remapping on A0 (PC0)
// #define NRF24L01_INSTALLED
	

//Low power is reducing the transmit power of the multi module. This setting is configurable per model in PPM (table below) or Serial mode (radio GUI).
//It can be activated when flying indoor or small models since the distance is short or if a model is causing issues when flying closed to the TX.
//By default low power is completly disabled on all rf chips to prevent mistakes, but you can enable it by uncommenting the lines below: 
//#define A7105_ENABLE_LOW_POWER
//#define CYRF6936_ENABLE_LOW_POWER
//#define CC2500_ENABLE_LOW_POWER
//#define NRF24L01_ENABLE_LOW_POWER


/****************************/
/*** PROTOCOLS TO INCLUDE ***/
/****************************/
//In this section select the protocols you want to be accessible when using the module.
//All the protocols will not fit in the Atmega328p module so you need to pick and choose.
//Comment the protocols you are not using with "//" to save Flash space.

//The protocols below need an IR LED to be installed
	#define lego

//The protocols below need an A7105 to be installed
	#define	JOYSWAY_A7105_INO
	
	#define	FLYSKY_A7105_INO
	#define	HUBSAN_A7105_INO
	#define	AFHDS2A_A7105_INO

//The protocols below need a CC2500 to be installed
	#define	SKYARTEC_CC2500_INO
	
	#define	FRSKYV_CC2500_INO
	#define	FRSKYD_CC2500_INO
	#define	FRSKYX_CC2500_INO
	#define SFHSS_CC2500_INO

//The protocols below need a NRF24L01 to be installed
	#define	HM830_NRF24L01_INO
	#define	CFLIE_NRF24L01_INO //!\\			//pb voie gaz
	#define	H377_NRF24L01_INO
	#define	ESKY150_NRF24L01_INO
	#define	UDI_NRF24L01_INO
	#define	NE260_NRF24L01_INO
	#define	BLUEFLY_NRF24L01_INO	//probleme gene id
	#define	FBL100_NRF24L01_INO	// finir id 				//!\\			//pb voie ???
	#define	INAV_NRF24L01_INO	//	a faire
	#define CABELL_NRF24L01_INO
	
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
	#define GW008_NRF24L01_INO
	#define DM002_NRF24L01_INO

//The table below indicates which protocol to run when a specific position on the dial has been selected.
//All fields and values are explained below. Everything is configurable from here like in the Serial mode.
//Example: You can associate multiple times the same protocol to different dial positions to take advantage of the model match (RX_Num)
const PPM_Parameters NUN_prot[15]=	{
//	Dial	Protocol 	Sub protocol	Bi_chanels	Power	Auto Bind		Option
/*	1	*/	{MODE_FLYSKY,	Flysky		,	1	,	P_HIGH	,	AUTOBIND	,	0		},
/*	2	*/	{MODE_FLYSKY,	Flysky		,	0	,	P_HIGH	,	AUTOBIND	,	0		},
/*	3	*/	{MODE_HUBSAN,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	40		},
/*	4	*/	{MODE_SERIAL,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	5	*/	{MODE_CX10	,	CX10_BLUE	,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	6	*/	{MODE_CABELL,	CABELL_V3	,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	7	*/	{MODE_CG023	,	CG023		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	8	*/	{MODE_BAYANG,	BAYANG		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},

/*	9	*/	{MODE_KN	,	WLTOYS		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	10	*/	{MODE_SYMAX	,	SYMAX		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	11	*/	{MODE_SLT	,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	12	*/	{MODE_CX10	,	CX10_BLUE	,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	13	*/	{MODE_DEVO	,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	14	*/	{MODE_YD717	,	YD717		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	15	*/	{MODE_SYMAX	,	SYMAX5C		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		}
};
/* Available protocols and associated sub protocols to pick and choose from
	MODE_FLYSKY
		Flysky
		V9X9
		V6X6
		V912
		CX20
	MODE_HUBSAN
		NONE
	MODE_FRSKYV
		NONE
	MODE_FRSKYD
		NONE
	MODE_FRSKYX
		CH_16
		CH_8
		EU_16
		EU_8
	MODE_HISKY
		Hisky
		HK310
	MODE_V2X2
		V2X2
		JXD506
	MODE_DSM
		DSM2_22
		DSM2_11
		DSMX_22
		DSMX_11
	MODE_DEVO
		NONE
	MODE_YD717
		YD717
		SKYWLKR
		SYMAX4
		XINXUN
		NIHUI
	MODE_KN
		WLTOYS
		FEILUN
	MODE_SYMAX
		SYMAX
		SYMAX5C
	MODE_SLT
		NONE
	MODE_CX10
		CX10_GREEN
		CX10_BLUE
		DM007
		JC3015_1
		JC3015_2
		MK33041
	MODE_Q2X2
		Q222
		Q242
		Q282
	MODE_SLT
		SLT
		VISTA
	MODE_CG023
		CG023
		YD829
		H8_3D
	MODE_BAYANG
		BAYANG
		H8S3D
	MODE_ESKY
		NONE
	MODE_MT99XX
		MT99
		H7
		YZ
		LS
		FY805
	MODE_MJXQ
		WLH08
		X600
		X800
		H26D
		E010
		H26WH
	MODE_SHENQI
		NONE
	MODE_FY326
		FY326
		FY319
	MODE_SFHSS
		NONE
	MODE_J6PRO
		NONE
	MODE_FQ777
		NONE
	MODE_ASSAN
		NONE
	MODE_HONTAI
		FORMAT_HONTAI
		FORMAT_JJRCX1
		FORMAT_X5C1
		FORMAT_FQ777_951
	MODE_AFHDS2A
		PWM_IBUS
		PPM_IBUS
		PWM_SBUS
		PPM_SBUS
	MODE_WK2X01
		WK2801
		WK2401
		W6_5_1
		W6_6_1
		W6_HEL
		W6_HEL_I
	MODE_Q303
		Q303
		CX35
		CX10D
		CX10WD
	MODE_GW008
		NONE
	MODE_DM002
		NONE
	MODE_CABELL
		CABELL_V3
		CABELL_SET_FAIL_SAFE
		CABELL_UNBIND
*/

// RX_Num is used for model match. Using RX_Num	values different for each receiver will prevent starting a model with the false config loaded...
// RX_Num value is between 0 and 15.

// Power P_HIGH or P_LOW: High or low power setting for the transmission.
// For indoor P_LOW is more than enough.

// Auto Bind	AUTOBIND or NO_AUTOBIND
// For protocols which does not require binding at each power up (like Flysky, FrSky...), you might still want a bind to be initiated each time you power up the TX.
// As an example, it's usefull for the WLTOYS F929/F939/F949/F959 (all using the Flysky protocol) which requires a bind at each power up.
// It also enables the Bind from channel feature, allowing to execute a bind by toggling a designated channel.

// Option: the value is between -128 and +127.
// The option value is only valid for some protocols, read this page for more information: https://github.com/pascallanger/DIY-Multiprotocol-TX-Module/blob/master/Protocols_Details.md


/**************************/
/***   STATIC CONFIG    ***/
/**************************/
#define CYRF_RST_pin	0		//A0 = PC0
#undef TELEMETRY
#define ENABLE_BIND_CH
#define BIND_CH	16
#undef WAIT_FOR_BIND
