#include <stdio.h> 		//Standard constants and functions for C (printf..., scanf...)
	
#include "PWM.h"
#include "servo.h"

#define MAX_Width 131	//2.1ms at 50Hz
#define IDLE_Width 94	//1.5ms at 50Hz
#define MIN_Width 56	//0.9ms at 50Hz

void Servo_init() {		//PWM initialization to control the servo
	PWM_PB5_init(256, 50);	//PWM connected in PB5. Prescaler N=256, and Frequency of 50Hz
}

void Move_Servo(uint8_t width) {
	uint8_t Servo_dir = 0;
	Servo_dir = 0.294*width + MIN_Width;	//Linear relation
	//0.294 = (MAX_Width - MIN_Width) * 255
	
	if (Servo_dir > MAX_Width) {Servo_dir = MAX_Width;}	//To be sure MAX and MIN
	if (Servo_dir < MIN_Width) {Servo_dir = MIN_Width;}	//are not surpassed!

	Set_PWMwidth("PB5", Servo_dir);
}