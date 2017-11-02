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

	//The protocols below need a A7105 to be installed
	#define	FLYSKY_A7105_INO
	#define	AFHDS2A_A7105_INO
	#define	HUBSAN_A7105_INO
	#define	JOYSWAY_A7105_INO

	//The protocols below need a CC2500 to be installed
	#define	FRSKYD_CC2500_INO
	#define	FRSKYV_CC2500_INO
	#define	FRSKYX_CC2500_INO
	#define	SFHSS_CC2500_INO
	#define	SKYARTEC_CC2500_INO

	//The protocols below need a CYRF6936 to be installed
	#define	DEVO_CYRF6936_INO
	#define	DSM_CYRF6936_INO
	#define	J6PRO_CYRF6936_INO
	#define	WK2x01_CYRF6936_INO

	//The protocols below need a NRF24L01 to be installed
	#define	ASSAN_NRF24L01_INO
	#define	BAYANG_NRF24L01_INO
	#define	BLUEFLY_NRF24L01_INO	//probleme gene id
	#define	CABELL_NRF24L01_INO
	#define	CFLIE_NRF24L01_INO	//!\			//pb voie gaz
	#define	CG023_NRF24L01_INO
	#define	CX10_NRF24L01_INO	// Include Q2X2 protocol
	#define	DM002_NRF24L01_INO
	#define	E012_NRF24L01_INO
	#define	ESKY_NRF24L01_INO
	#define	ESKY150_NRF24L01_INO
	#define	FBL100_NRF24L01_INO	// finir id 				//!\			//pb voie ???
	#define	FQ777_NRF24L01_INO
	#define	FY326_NRF24L01_INO
	#define	GW008_NRF24L01_INO
	#define	H377_NRF24L01_INO
	#define	HISKY_NRF24L01_INO
	#define	HM830_NRF24L01_INO
	#define	HONTAI_NRF24L01_INO
	#define	INAV_NRF24L01_INO	//	a faire
	#define	KN_NRF24L01_INO
	#define	MJXQ_NRF24L01_INO
	#define	MT99XX_NRF24L01_INO
	#define	NE260_NRF24L01_INO
	#define	Q303_NRF24L01_INO
	#define	SLT_NRF24L01_INO
	#define	SHENQI_NRF24L01_INO
	#define	SYMAX_NRF24L01_INO
	#define	UDI_NRF24L01_INO
	#define	V2X2_NRF24L01_INO
	#define	YD717_NRF24L01_INO
	
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
