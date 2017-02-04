#ifdef scanner
void Scanner(void) {
	byte rssi[80];
	byte i;

	//on ecrit le crc
	CYRF_WriteRegister(0x15, 0x0000 & 0xFF);//Envoie le poid faible 
	CYRF_WriteRegister(0x16, 0x0000 >> 8); //Envoie du poid fort

	//on passe en mode reception
	CYRF_WriteRegister(0x0E,0x20);//pour mettre le module en mode reception 
	CYRF_WriteRegister(0x0F,0x28);
	delay(100);//on fait une pause

	switch(sub_protocol) {
		#ifdef CYRF6936_INSTALLED
			case SC_CYRF :
				CYRF_WriteRegister(0x15, 0x0000 & 0xFF); CYRF_WriteRegister(0x16, 0x0000 >> 8);    //on ecrit le crc
				CYRF_WriteRegister(0x0E,0x20); CYRF_WriteRegister(0x0F,0x28); //pour mettre le module en mode reception 
				for(i=0;i<80;i++) {
					CYRF_WriteRegister(0x00,ch);  //on attribue le canal a mesure
					rssi[i] = CYRF_ReadRegister(0x13) & 0x1F; //on fait une première requetete pour lancer le process de mesure
					CYRF_WriteRegister(0x05, 0x87);//on bascule l'ensemble en reception
					rssi[i] = CYRF_ReadRegister(0x13) & 0x1F;//et je sauvegarde la force du signal
				}
				break;
		#endif
		#ifdef A7105_INSTALLED
			case SC_A7105 :
				CYRF_WriteRegister(0x15, 0x0000 & 0xFF); CYRF_WriteRegister(0x16, 0x0000 >> 8);    //on ecrit le crc
				CYRF_WriteRegister(0x0E,0x20); CYRF_WriteRegister(0x0F,0x28); //pour mettre le module en mode reception 
				for(i=0;i<80;i++) {
					CYRF_WriteRegister(0x00,ch);  //on attribue le canal a mesure
					rssi[i] = CYRF_ReadRegister(0x13) & 0x1F; //on fait une première requetete pour lancer le process de mesure
					CYRF_WriteRegister(0x05, 0x87);//on bascule l'ensemble en reception
					rssi[i] = CYRF_ReadRegister(0x13) & 0x1F;//et je sauvegarde la force du signal
				}
				break;
		#endif
	}
	delay(500);
}
#endif