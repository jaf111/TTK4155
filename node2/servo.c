#include <stdio.h> 		//Standard constants and functions for C (printf..., scanf...)
	
#include "PWM.h"
#include "servo.h"

#define MAX_Width  100 	//131	//2.1ms at 50Hz		// Max value is decreased because of manual calibration 
#define IDLE_Width 75 	//94	//1.5ms at 50Hz		// Servo is NOT centered at midpoint value for duty cycle. Bad servo?
#define MIN_Width 56	//0.9ms at 50Hz


uint8_t servo_dir = 0;

void servo_init() {		//PWM initialization to control the servo
	PWM_PB5_init(256, 50);		//PWM connected in PB5. Prescaler N=256, and Frequency of 50Hz
	move_servo(IDLE_Width);		//Servo is initialized in the middle position
}

void move_servo(uint8_t width) {
	servo_dir = 0.175*width + MIN_Width;	//Linear relation
	//0.294 = (MAX_Width - MIN_Width) * 255 --> It changes to 0,175 to calibrate the servo!
	
	if (servo_dir > MAX_Width) {servo_dir = MAX_Width;}	//To be sure MAX and MIN
	if (servo_dir < MIN_Width) {servo_dir = MIN_Width;}	//are not surpassed!

	set_PWMwidth("PB5", servo_dir);
}