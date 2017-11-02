# DIY-Multiprotocol-TX-Module

![Screenshot](http://static.rcgroups.net/forums/attachments/4/0/8/5/8/3/t7952733-114-thumb-P4100002.JPG?d=1433910155) ![Screenshot](http://static.rcgroups.net/forums/attachments/4/0/8/5/8/3/t7952734-189-thumb-P4100003.JPG?d=1433910159)

Fork du projet https://github.com/pascallanger/DIY-Multiprotocol-TX-Module

Afin d'ajouter :
- Un rebind hardware en PPM
- La radio TARANIS (TAERB, B = rebind ;-) ) et redéclaration des radios



Programme des évolutions :
- Ajout du futur protocole INAV


#Schematic
![Screenshot](http://static.rcgroups.net/forums/attachments/4/0/8/5/8/3/a8443844-119-multiprotocol_diagram_rotary_serial_2.jpg)

Notes:
- Attention: All modules are 3.3V only, never power them with 5V.


#Protocoles ajoutés mais non testés (Issue de Deviation)
##Other
###OPENLRS
Empty protocol

##A7105 RF Module
###HUBSAN
Models: Hubsan H102D, H107/L/C/D and Hubsan H107P/C+/D+

Autobind protocol

Telemetry enabled for battery voltage and TX RSSI

Option=vTX frequency (H107D) 5645 - 5900 MHz

CH1|CH2|CH3|CH4|CH5|CH6|CH7|CH8|CH9
---|---|---|---|---|---|---|---|---
A|E|T|R|FLIP|LIGHT|PICTURE|VIDEO|HEADLESS
####Sub_protocol H301
CH5|CH6|CH7|CH8
---|---|---|---
LED|STAB|RTH|VIDEO

####Sub_protocol H501
CH5|CH6|CH7|CH8|CH9|CH10|CH11|CH12
---|---|---|---|---|---|---|---|---|---|---|---
FLIP|LIGHT|RTH|VIDEO|HEADLESS|GPS_HOLD|ALT_HOLD|SNAPSHOT

###Joysway
CH1|CH2|CH3|CH4
---|---|---|---
A|E|T|R

##CC2500 RF Module
###SKYARTEC
CH1|CH2|CH3|CH4|CH5|CH6|CH7
---|---|---|---|---|---|---
 ? | ? | ? | ? | ? | ? | ? 

##NRF24L01 RF Module
###BAYANG
Models: EAchine H8(C) mini, BayangToys X6/X7/X9, JJRC JJ850, Floureon H101 ...

Autobind protocol

CH1|CH2|CH3|CH4|CH5|CH6|CH7|CH8|CH9|CH10
---|---|---|---|---|---|---|---|---|----
A|E|T|R|FLIP|RTH|PICTURE|VIDEO|HEADLESS|INVERTED

####Sub_protocol IRDRONE
####Sub_protocol X16_AH

###BLUEFLY
Autobind

CH1|CH2|CH3|CH4|CH5|CH6
---|---|---|---|---|---
A|E|T|R|GEAR|PITCH

###CABELL
CH1|CH2|CH3|CH4|CH5|CH6|CH7|CH8|CH9|CH10|CH11|CH12|CH13|CH14|CH15|CH16
---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----
CH1|CH2|CH3|CH4|CH5|CH6|CH7|CH8|CH9|CH10|CH11|CH12|CH13|CH14|CH15|CH16

####Sub_protocol SET_FAIL_SAFE
####Sub_protocol UNBIND

###CFLIE
Modele: CrazyFlie Nano quad

Autobind

CH1|CH2|CH3|CH4
---|---|---|---
A|E|T|R

###E012
Autobind

CH1|CH2|CH3|CH4|CH5|CH6|CH7
---|---|---|---|---|---|---
A|E|T|R|FLIP|HEADLESS|RTH

###ESKY150

Autobind

CH1|CH2|CH3|CH4
---|---|---|---
A|E|T|R

###FBL100
Autobind

CH1|CH2|CH3|CH4|CH5|CH6|CH7|CH8
---|---|---|---|---|---|---|---
 ? | ? | ? | ? | ? | ? | ? | ? 

####Sub_protocol HP100
Same channels assignement as above.

###H377
CH1|CH2|CH3|CH4|CH5|CH6|CH7|CH8
---|---|---|---|---|---|---|---
A|E|T|R|CH5|CH6|CH7|CH8

###GW008
Modele: There are 3 versions of this small quad, this protocol is for the one with a XNS104 IC in the stock Tx and PAN159CY IC in the quad.
The xn297 version is compatible with the CX10 protocol (green pcb).
The LT8910 version is not supported yet.

This PR also includes enhanced packet mode support for xn297 emulation (tx & rx).

Forum thread: https://www.deviationtx.com/forum/protocol-development/6420-global-drone-skull-drone-or-gw008

Autobind

CH1|CH2|CH3|CH4|CH5|CH6
---|---|---|---
A|E|T|R||FLIP

###HM830
Modele: HM Hobby HM830 RC Paper Airplane

Autobind

CH1|CH2|CH3|CH4|CH5
---|---|---|---
A|Turbo|T|Trim|Bouton

###INAV
En cours de passage

###NE260
Modele: Nine Eagles SoloPro

Autobind

CH1|CH2|CH3|CH4
---|---|---|---
A|E|T|R

###Q303

Autobind

CH1|CH2|CH3|CH4|CH5|CH6|CH7|CH8|CH9|CH10|CH11
---|---|---|---|---|---|---|---|---|---|---
A|E|T|R|AHOLD|FLIP|SNAPSHOT|VIDEO|HEADLESS|RTH|GIMBAL

####Sub_protocol CX35

Autobind

CH1|CH2|CH3|CH4|CH5|CH6|CH7|CH8|CH9|CH10|CH11
---|---|---|---|---|---|---|---|---|---|---
A|E|T|R|ARM|FLIP|SNAPSHOT|VIDEO|HEADLESS|RTH| on Q303, full range on CX35

####Sub_protocol CX10D

Autobind

CH1|CH2|CH3|CH4|CH5|CH6
---|---|---|---|---|---
A|E|T|R|---|FLIP

####Sub_protocol CX10WD

Autobind

CH1|CH2|CH3|CH4|CH5|CH6
---|---|---|---|---|---
A|E|T|R|ARM|FLIP

###UDI
Modele: Known UDI 2.4GHz protocol variants, all using BK2421
* UDI U819 coaxial 3ch helicoper
* UDI U816/817/818 quadcopters
  - "V1" with orange LED on TX, U816 RX labeled '' , U817/U818 RX labeled 'UD-U817B'
  - "V2" with red LEDs on TX, U816 RX labeled '', U817/U818 RX labeled 'UD-U817OG'
  - "V3" with green LEDs on TX. Did not get my hands on yet.
* U830 mini quadcopter with tilt steering ("Protocol 2014")
* U839 nano quadcopter ("Protocol 2014")

Autobind

CH1|CH2|CH3|CH4|CH5|CH6|CH7|CH8|CH9|CH10
---|---|---|---|---|---|---|---|---|---
A|E|T|R|FLIP 360|FLIP|VIDEO|LED|MODE 2

####Sub_protocol U816_V1 (orange)
####Sub_protocol U816_V2 (red)
####Sub_protocol U839_2014
Same channels assignement as above.

###D'autres à venir