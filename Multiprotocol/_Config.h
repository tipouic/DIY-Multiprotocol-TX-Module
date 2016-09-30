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

<<<<<<< HEAD
/** Multiprotocol module configuration file ***/

//Uncomment your TX type
#define TARANIS   //TARANIS TAER (1100<->1900µs)
//#define TX_ER9X			//ER9X AETR (988<->2012µs)
//#define TX_DEVO7		//DEVO7 EATR (1120<->1920µs)
//#define TX_SPEKTRUM	//Spektrum TAER (1100<->1900µs)
//#define TX_HISKY		//HISKY AETR (1100<->1900µs)

//Uncomment to enable telemetry
#define TELEMETRY

//Comment if a module is not installed
#define A7105_INSTALLED
#define CYRF6936_INSTALLED
//#define CC2500_INSTALLED
#define NFR24L01_INSTALLED

//Comment a protocol to exclude it from compilation
#ifdef	A7105_INSTALLED
	#define	JOYSWAY_A7105_INO

	#define	FLYSKY_A7105_INO
	#define	HUBSAN_A7105_INO
#endif
#ifdef	CYRF6936_INSTALLED
	#define	J6PRO_CYRF6936_INO
	#define	WK2x01_CYRF6936_INO
	
	#define	DEVO_CYRF6936_INO
	#define	DSM2_CYRF6936_INO
#endif
#ifdef	CC2500_INSTALLED
	#define	SKYARTEC_CC2500_INO
	
	#define	FRSKY_CC2500_INO
	#define	FRSKYX_CC2500_INO
#endif
#ifdef	NFR24L01_INSTALLED
	#define	HM830_NRF24L01_INO
	#define	CFlie_NRF24L01_INO
	#define	H377_NRF24L01_INO
	#define	ESKY150_NRF24L01_INO
	#define	HonTai_NRF24L01_INO
	#define	UDI_NRF24L01_INO
	#define	NE260_NRF24L01_INO
	#define	BlueFly_NRF24L01_INO	//probleme gene id 
	#define	FBL100_NRF24L01_INO	// finir id
	
	#define	BAYANG_NRF24L01_INO
	#define	CG023_NRF24L01_INO
	#define	CX10_NRF24L01_INO
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
#endif

//Update this table to set which protocol and all associated settings are called for the corresponding dial number
const PPM_Parameters PPM_prot[15]=	{
//	Dial	Protocol 		Sub protocol	RX_Num	Power		Auto Bind		Option
/*	1	*/	{MODE_FLYSKY,	Flysky		,	0	,	P_HIGH	,	AUTOBIND	,	0		},
/*	2	*/	{MODE_HUBSAN,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	3	*/	{MODE_FRSKY	,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0xD7	},	// D7 fine tuning
/*	4	*/	{MODE_HISKY	,	Hisky		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	5	*/	{MODE_V2X2	,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	6	*/	{MODE_DSM2	,	DSM2		,	0	,	P_HIGH	,	NO_AUTOBIND	,	6		},	// 6 channels @ 11ms
/*	7	*/	{MODE_DEVO	,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	8	*/	{MODE_YD717	,	YD717		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	9	*/	{MODE_KN	,	FEILUN		,	0	,	P_HIGH	,	AUTOBIND	,	0		},
=======
/**********************************************/
/** Multiprotocol module configuration file ***/
/**********************************************/

/*******************/
/*** TX SETTINGS ***/
/*******************/
//Modify the channel order based on your TX: AETR, TAER, RETA...
//Examples: Flysky & DEVO is AETR, JR/Spektrum radio is TAER, Multiplex is AERT...
//Default is AETR.
#define AETR


/**************************/
/*** RF CHIPS INSTALLED ***/
/**************************/
//There are 4 RF components supported. If one of them is not installed you must comment it using "//".
//If a chip is not installed all associated protocols are disabled.
//4-in-1 modules have all RF chips installed
//!!!If a RF chip is present it MUST be marked as installed!!! or weird things will happen you have been warned.
#define A7105_INSTALLED
#define CYRF6936_INSTALLED
#define CC2500_INSTALLED
#define NRF24L01_INSTALLED


/****************************/
/*** PROTOCOLS TO INCLUDE ***/
/****************************/
//In this section select the protocols you want to be accessible when using the module.
//All the protocols will not fit in the module so you need to pick and choose.
//Comment the protocols you are not using with "//" to save Flash space.

//The protocols below need an A7105 to be installed
#define	FLYSKY_A7105_INO
#define	HUBSAN_A7105_INO

//The protocols below need a CYRF6936 to be installed
#define	DEVO_CYRF6936_INO
#define	DSM_CYRF6936_INO
#define J6PRO_CYRF6936_INO

//The protocols below need a CC2500 to be installed
#define	FRSKYD_CC2500_INO
#define	FRSKYV_CC2500_INO
#define	FRSKYX_CC2500_INO
#define SFHSS_CC2500_INO

//The protocols below need a NRF24L01 to be installed
#define	BAYANG_NRF24L01_INO
#define	CG023_NRF24L01_INO
#define	CX10_NRF24L01_INO
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


/**************************/
/*** TELEMETRY SETTINGS ***/
/**************************/
//In this section you can configure the telemetry.

//If you do not plan using the telemetry comment this global setting using "//" and skip to the next section.
#define TELEMETRY

//Uncomment to invert the polarity of the telemetry serial signal.
//For ER9X and ERSKY9X it must be commented. For OpenTX it must be uncommented.
//#define INVERT_TELEMETRY

//Comment a line to disable a protocol telemetry
#define DSM_TELEMETRY	
#define SPORT_TELEMETRY	
#define HUB_TELEMETRY


/****************************/
/*** SERIAL MODE SETTINGS ***/
/****************************/
//In this section you can configure the serial mode.
//The serial mode enables full editing of all the parameters in the GUI of the radio.
//This is available natively for ER9X and ERSKY9X. It is available for OpenTX on Taranis with a special version.

//If you do not plan to use the Serial mode comment this line using "//" to save Flash space
#define ENABLE_SERIAL


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
#define TX_ER9X			//ER9X/ERSKY9X/OpenTX	( 988<->2012µs)
//#define TX_DEVO7		//DEVO					(1120<->1920µs)
//#define TX_SPEKTRUM	//Spektrum				(1100<->1900µs)
//#define TX_HISKY		//HISKY					(1100<->1900µs)
//#define TX_MPX		//Multiplex MC2020		(1250<->1950µs)
//#define TX_CUSTOM		//Custom

// The lines below are used to set the end points in microseconds (µs) if you have selected TX_CUSTOM.
// A few things to considered:
//  - If you put too big values compared to your TX you won't be able to reach the extremes which is bad for throttle as an example
//  - If you put too low values you won't be able to use your full stick range, it will be maxed out before reaching the end
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
/*	1	*/	{MODE_FLYSKY,	Flysky		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	2	*/	{MODE_HUBSAN,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	3	*/	{MODE_FRSKYD,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	40		},	// option=fine freq tuning
/*	4	*/	{MODE_HISKY	,	Hisky		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	5	*/	{MODE_V2X2	,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	6	*/	{MODE_DSM	,	DSM2_22		,	0	,	P_HIGH	,	NO_AUTOBIND	,	6		},	// option=number of channels
/*	7	*/	{MODE_DEVO	,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	8	*/	{MODE_YD717	,	YD717		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	9	*/	{MODE_KN	,	WLTOYS		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
>>>>>>> refs/remotes/pascallanger/master
/*	10	*/	{MODE_SYMAX	,	SYMAX		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	11	*/	{MODE_SLT	,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	12	*/	{MODE_CX10	,	CX10_BLUE	,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	13	*/	{MODE_CG023	,	CG023		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	14	*/	{MODE_BAYANG,	0			,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		},
/*	15	*/	{MODE_SYMAX	,	SYMAX5C		,	0	,	P_HIGH	,	NO_AUTOBIND	,	0		}
};
<<<<<<< HEAD
/* Available protocols and associated sub protocols:
=======
/* Available protocols and associated sub protocols to pick and choose from
>>>>>>> refs/remotes/pascallanger/master
	MODE_FLYSKY
		Flysky
		V9X9
		V6X6
		V912
	MODE_HUBSAN
		NONE
<<<<<<< HEAD
	MODE_FRSKY
=======
	MODE_FRSKYD
>>>>>>> refs/remotes/pascallanger/master
		NONE
	MODE_HISKY
		Hisky
		HK310
	MODE_V2X2
		NONE
<<<<<<< HEAD
	MODE_DSM2
		DSM2
		DSMX
=======
	MODE_DSM
		DSM2_22
		DSM2_11
		DSMX_22
		DSMX_11
>>>>>>> refs/remotes/pascallanger/master
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
		Q282
		JC3015_1
		JC3015_2
		MK33041
		Q242
	MODE_CG023
		CG023
		YD829
		H8_3D
	MODE_BAYANG
		NONE
	MODE_FRSKYX
<<<<<<< HEAD
		NONE
=======
		CH_16
		CH_8
>>>>>>> refs/remotes/pascallanger/master
	MODE_ESKY
		NONE
	MODE_MT99XX
		MT99
		H7
		YZ
<<<<<<< HEAD
=======
		LS
>>>>>>> refs/remotes/pascallanger/master
	MODE_MJXQ
		WLH08
		X600
		X800
		H26D
<<<<<<< HEAD
	MODE_SHENQI
		NONE
	MODE_FY326
		FY326
		FY319

RX_Num 		value between 0 and 15

Power		P_HIGH or P_LOW

Auto Bind	AUTOBIND or NO_AUTOBIND

Option		value between 0 and 255. 0xD7 or 0x00 for Frsky fine tuning.
*/

//******************
//TX definitions with timing endpoints and channels order

// Turnigy PPM and channels
#if defined(TX_ER9X)
	#define PPM_MAX		2140
	#define PPM_MIN		860
	#define PPM_MAX_100 2012
	#define PPM_MIN_100 988
	#define AETR
#endif

// Devo PPM and channels
#if defined(TX_DEVO7)
	#define PPM_MAX		2100
	#define PPM_MIN		900
	#define PPM_MAX_100	1920
	#define PPM_MIN_100	1120
	#define EATR
#endif

// SPEKTRUM PPM and channels
#if defined(TX_SPEKTRUM)
	#define PPM_MAX		2000
	#define PPM_MIN		1000
	#define PPM_MAX_100	1900
	#define PPM_MIN_100	1100
	#define TAER
#endif

// TARANIS PPM and channels
#if defined(TARANIS)
	#define PPM_MAX		2000
	#define PPM_MIN		1000
	#define PPM_MAX_100	1900
	#define PPM_MIN_100	1100
	#define EATR
#endif

// HISKY
#if defined(TX_HISKY)
	#define PPM_MAX		2000
	#define PPM_MIN		1000
	#define PPM_MAX_100	1900
	#define PPM_MIN_100	1100
	#define AETR
#endif

#if defined(EATR)
	enum chan_order{
		ELEVATOR=0,
		AILERON,
		THROTTLE,
		RUDDER,
	};
#endif

#if defined(TAER)
	enum chan_order{
		THROTTLE=0,
		AILERON,
		ELEVATOR,
		RUDDER,
	};
#endif

#if defined(AETR)
	enum chan_order{
		AILERON =0,
		ELEVATOR,
		THROTTLE,
		RUDDER,
	};
#endif
enum chan_orders{
	AUX1 =4,
	AUX2,
	AUX3,
	AUX4,
	AUX5,
	AUX6,
	AUX7,
	AUX8,
	AUX9
};

#define PPM_MIN_COMMAND 1250
#define PPM_SWITCH	1550
#define PPM_MAX_COMMAND 1750

//Uncoment the desired serial speed
#define BAUD 100000
//#define BAUD 125000
=======
		E010
	MODE_SHENQI
		NONE
	MODE_FY326
		NONE
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
*/

// RX_Num is used for model match. Using RX_Num	values different for each receiver will prevent starting a model with the false config loaded...
// RX_Num value is between 0 and 15.

// Power P_HIGH or P_LOW: High or low power setting for the transmission.
// For indoor P_LOW is more than enough.

// Auto Bind	AUTOBIND or NO_AUTOBIND
// For protocols which does not require binding at each power up (like Flysky, FrSky...), you might still want a bind to be initiated each time you power up the TX.
// As an exxample, it's usefull for the WLTOYS F929/F939/F949/F959 (all using the Flysky protocol) which requires a bind at each power up.

// Option: the value is between -127 and +127.
// The option value is only valid for some protocols, read this page for more information: https://github.com/pascallanger/DIY-Multiprotocol-TX-Module/blob/master/Protocols_Details.md
>>>>>>> refs/remotes/pascallanger/master
