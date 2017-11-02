#ifdef lego

#include "LegoIr.h"
LegoIr pf;

void lego_init() {
	pf.begin(IR_PIN, 0);  // IR LED pin , channel 0 - 3 (in order to change the channel, just execute this line again)
	bind_counter=5;
}

void lego_calback() {
	static byte speedOld[8];
	static byte speed[8];
	static byte pwm[8];
	static unsigned long previousMillis;
	
	// read joystick positions into an array-----
	// speed[0] = map(Servo_data[0], servo_min_125, servo_max_125, 0, 100);
	// speed[1] = map(Servo_data[1], servo_min_125, servo_max_125, 0, 100);
	
	// compute pwm value for "red" and "blue" motor, if speed has changed more than +/- 3, or every 0.6s
	// NOTE: one IR pulse at least every 1.2 s is required in order to prevent the vehivle from stopping
	// due to a signal timeout!
	if(option != bind_counter) {
		if(option==0) { 	hopping_frequency_no = 1; }
		else if(option>4) {	hopping_frequency_no = 4; }
		else {				hopping_frequency_no = option; }
		bind_counter = option;
	}
	
	for (int i = 0; i < hopping_frequency_no; i ++) {
		speed[i*2+0] = map(Servo_data[i*2+0], servo_min_125, servo_max_125, 0, 100);
		speed[i*2+1] = map(Servo_data[i*2+1], servo_min_125, servo_max_125, 0, 100);
		if (
			(speedOld[i*2+0] - 3) > speed[i*2+0] || (speedOld[i*2+0] + 3) < speed[i*2+0] ||
			(speedOld[i*2+1] - 3) > speed[i*2+1] || (speedOld[i*2+1] + 3) < speed[i*2+1] ||
			millis() - previousMillis >= 600
		) {
			speedOld[i*2+0] = speed[i*2+0];			pwm[i*2+0] = pf.pwm_convert(speed[i*2+0]);
			speedOld[i*2+1] = speed[i*2+1];			pwm[i*2+1] = pf.pwm_convert(speed[i*2+1]);
			previousMillis = millis();
			
			pf.begin(IR_PIN, i);  // IR LED pin , channel 0 - 3 (in order to change the channel, just execute this line again)
			cli();
			pf.combo_pwm(pwm[i*2+1], pwm[i*2+0]);
			sei();
		}
	}
}
#endif