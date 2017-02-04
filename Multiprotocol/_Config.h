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
/** Multiprotocol module configuration file ***/
/**********************************************/

/********************/
/***  BOARD TYPE  ***/
/********************/
//Uncomment one of the line below if you have a different module not based on the original Multi Atmega328p design which includes the 4-in-1.
//If you don't know then leave them commented.
#ifdef __arm__
	#define STM32_BOARD	// Let's automatically select this board if arm is selected since this is the only one for now...
#endif

/*******************/
/*** TX SETTINGS ***/
/*******************/
//Modify the channel order based on your TX: AETR, TAER, RETA...
//Examples: Flysky & DEVO is AETR, JR/Spektrum radio is TAER, Multiplex is AERT...
//Default is AETR.
#define EATR

//Uncomment to reverse the direction of the specified channel for all protocols
//#define REVERSE_AILERON
//#define REVERSE_ELEVATOR
//#define REVERSE_THROTTLE
//#define REVERSE_RUDDER

//Comment to disable the bind feature on a channel
#define ENABLE_BIND_CH
//Set the channel number used for bind. Default is 16.
#define BIND_CH	16


/**************************/
/*** RF CHIPS INSTALLED ***/
/**************************/
//There are 4 RF components supported. If one of them is not installed you must comment it using "//".
//If a chip is not installed all associated protocols are disabled.
//4-in-1 modules have all RF chips installed
//!!!If a RF chip is present it MUST be marked as installed!!! or weird things will happen you have been warned.
	#define A7105_INSTALLED
	#define CYRF6936_INSTALLED
//	#define CC2500_INSTALLED
	#define NRF24L01_INSTALLED


/****************************/
/*** PROTOCOLS TO INCLUDE ***/
/****************************/
//In this section select the protocols you want to be accessible when using the module.
//All the protocols will not fit in the Atmega328p module so you need to pick and choose.
//Comment the protocols you are not using with "//" to save Flash space.

//The protocols below need an A7105 to be installed
	#define	JOYSWAY_A7105_INO
	
	#define	FLYSKY_A7105_INO
	#define	HUBSAN_A7105_INO
	#define	AFHDS2A_A7105_INO
//The protocols below need a CYRF6936 to be installed
	#define	DEVO_CYRF6936_INO
	#define	DSM_CYRF6936_INO
//	#define	J6PRO_CYRF6936_INO
//	#define	WK2x01_CYRF6936_INO

//The protocols below need a CC2500 to be installed
	#define	SKYARTEC_CC2500_INO
	
	#define	FRSKYV_CC2500_INO
	#define	FRSKYD_CC2500_INO
	#define	FRSKYX_CC2500_INO
	#define SFHSS_CC2500_INO

//The protocols below need a NRF24L01 to be installed
	#define	HM830_NRF24L01_INO
//	#define	CFlie_NRF24L01_INO //!\\			//pb voie gaz
//	#define	H377_NRF24L01_INO
//	#define	ESKY150_NRF24L01_INO
//	#define	HonTai_NRF24L01_INO
//	#define	UDI_NRF24L01_INO
//	#define	NE260_NRF24L01_INO
//	#define	BlueFly_NRF24L01_INO	//probleme gene id
//	#define	FBL100_NRF24L01_INO	// finir id 				//!\\			//pb voie ???
//	#define	INAV_NRF24L01_INO	//	a faire
	
	#define	BAYANG_NRF24L01_INO
	#define	CG023_NRF24L01_INO
	#define	CX10_NRF24L01_INO		// Include Q2X2 protocol
//	#define	ESKY_NRF24L01_INO
//	#define	HISKY_NRF24L01_INO
	#define	KN_NRF24L01_INO
//	#define	SLT_NRF24L01_INO
	#define	SYMAX_NRF24L01_INO
	#define	V2X2_NRF24L01_INO
	#define	YD717_NRF24L01_INO
//	#define	MT99XX_NRF24L01_INO
//	#define	MJXQ_NRF24L01_INO
//	#define	SHENQI_NRF24L01_INO
//	#define	FY326_NRF24L01_INO
//	#define	FQ777_NRF24L01_INO
//	#define	ASSAN_NRF24L01_INO
//	#define	HONTAI_NRF24L01_INO
//	#define Q303_NRF24L01_INO

/**************************/
/*** TELEMETRY SETTINGS ***/
/**************************/
//In this section you can configure the telemetry.

//If you do not plan using the telemetry comment this global setting using "//" and skip to the next section.
#define TELEMETRY

//Comment to invert the polarity of the output telemetry serial signal.
//This function takes quite some flash space and processor power on an atmega.
//For OpenTX and ersky9x it must be uncommented.
//On a 9XR_PRO running ersky9x both commented and uncommented will work depending on the radio setting Invert COM1 under the Telemetry menu.
//On other addon/replacement boards like the 9xtreme board or the Ar9x board, you need to uncomment the line below.
//For er9x it depends if you have an inveter mod or not on the telemetry pin. If you don't have an inverter comment this line.
#define INVERT_TELEMETRY

//Comment if you don't want to send Multi status telemetry frames (Protocol available, Bind in progress, version...)
//Use with er9x/erksy9x, for OpenTX MULTI_TELEMETRY below is preferred instead
//#define MULTI_STATUS

//Uncomment to send Multi status and allow OpenTX to autodetect the telemetry format
//Supported by OpenTX version 2.2 RC9 and newer. NOT supported by er9x/ersky9x use MULTI_STATUS instead.
//#define MULTI_TELEMETRY

//Comment a line to disable a specific protocol telemetry
	#define DSM_TELEMETRY				// Forward received telemetry packet directly to TX to be decoded
	#define SPORT_TELEMETRY				// Use FrSkyX SPORT format to send telemetry to TX
	#define AFHDS2A_FW_TELEMETRY		// Forward received telemetry packet directly to TX to be decoded
	#define HUB_TELEMETRY				// Use FrSkyD Hub format to send telemetry to TX
	#define AFHDS2A_HUB_TELEMETRY		// Use FrSkyD Hub format to send telemetry to TX
	#define BAYANG_HUB_TELEMETRY		// Use FrSkyD Hub format to send telemetry to TX
	#define HUBSAN_HUB_TELEMETRY		// Use FrSkyD Hub format to send telemetry to TX


/****************************/
/*** SERIAL MODE SETTINGS ***/
/****************************/
//In this section you can configure the serial mode.
//The serial mode enables full editing of all the parameters in the GUI of the radio.
//This is available natively for ER9X and ERSKY9X. It is available for OpenTX on Taranis with a special version.

//If you do not plan to use the Serial mode comment this line using "//" to save Flash space
#define ENABLE_SERIAL

/******************************/
/*** NUNCHUCK MODE SETTINGS ***/
/******************************/
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

/*************************/
/*** PPM MODE SETTINGS ***/
/*************************/
//In this section you can configure all details about PPM.
//If you do not plan to use the PPM mode comment this line using "//" to save Flash space, you don't need to configure anything below in this case
#define ENABLE_PPM

/*** TX END POINTS ***/
//It is important for the module to know the endpoints of your radio.
//Below are some standard transmitters already preconfigured.
//Uncomment only the one which matches your transmitter.
//#define TX_ER9X			//ER9X/ERSKY9X/OpenTX	( 988<->2012µs)
#define TX_TARANIS			//TARANIS AETR (1100<->1900µs)
//#define TX_DEVO7			//DEVO					(1120<->1920µs)
//#define TX_SPEKTRUM		//Spektrum				(1100<->1900µs)
//#define TX_HISKY			//HISKY					(1100<->1900µs)
//#define TX_MPX			//Multiplex MC2020		(1250<->1950µs)
//#define TX_CUSTOM			//Custom

// The lines below are used to set the end points in microseconds (µs) if you have selected TX_CUSTOM.
// A few things to consider:
//  - If you put too big values compared to your TX you won't be able to reach the extremes which is bad for throttle as an example
//  - If you put too low values you won't be able to use your full stick range, it will be maxed out before reaching the ends
//  - Centered stick value is usually 1500. It should match the middle between MIN and MAX, ie Center=(MAX-MIN)/2+MIN. If your TX is not centered you can adjust the value MIN or MAX.
//  - 100% is the value when the model is by default, 125% is the value when you extend the servo travel which is only used by some protocols
#if defined(TX_CUSTOM)
	#define PPM_MAX_100	1900	//	100%
	#define PPM_MIN_100	1100	//	100%
	#define PPM_MAX_125	2000	//	125%
	#define PPM_MIN_125	1000	//	125%
#endif

//The table below indicates which protocol to run when a specific position on the dial has been selected.
//All fields and values are explained below. Everything is configurable from here like in the Serial mode.
//Example: You can associate multiple times the same protocol to different dial positions to take advantage of the model match (RX_Num)
const PPM_Parameters PPM_prot[15]=	{
//	Dial	Protocol 		Sub protocol	RX_Num	Power		Auto Bind		Option
/*	1	*/	{MODE_FLYSKY,	Flysky		,	0	,	P_HIGH	,	AUTOBIND	,	0		},
/*	2	*/	{MODE_HUBSAN,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	3	*/	{MODE_FRSKYD,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	40		},	// option=fine freq tuning
/*	4	*/	{MODE_HISKY	,	Hisky		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	5	*/	{MODE_V2X2	,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	6	*/	{MODE_DSM	,	DSM2_22		,	0	,	P_HIGH	,	NO_AUTOBIND	,	6		},	// option=number of channels
/*	7	*/	{MODE_DEVO	,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	8	*/	{MODE_YD717	,	YD717		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	9	*/	{MODE_KN	,	WLTOYS		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	10	*/	{MODE_SYMAX	,	SYMAX		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	11	*/	{MODE_SLT	,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	12	*/	{MODE_CX10	,	CX10_BLUE	,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	13	*/	{MODE_CG023	,	CG023		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	14	*/	{MODE_BAYANG,	BAYANG		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
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
	MODE_FRSKYD
		NONE
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
	MODE_FRSKYX
		CH_16
		CH_8
		EU_16
		EU_8
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
	MODE_FRSKYV
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