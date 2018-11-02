#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <stdio.h> 		//Standard constants and functions for C (printf..., scanf...)
#include <float.h>
	
#include "uart.h"
#include "PWM.h"
#include "pid_contr.h"

//Continuous version =>	u = Kp*e + Ki*∫edt + Kd*(de/dt) where e is the error (the difference between actual and target
//Discrete version =>	u(n) = Kp*e(n) + T*Ki*∑e(i) + (Kd/T)*(e(n)−e(n−1)), where T is the sampling period.

uint8_t PID_output = 0;
uint8_t error = 0;
uint8_t previous_error = 0;
uint8_t Ku = 0;		//Ultimate gain
uint8_t Kp = 0;		//Proptional constant
uint8_t Ki = 0;		//Integral constant
uint8_t Kd = 0;		//Derivative constant
uint8_t integral = 0;
uint8_t derivative = 0;
float T = 0;

void pid_init(uint8_t pid_type, uint16_t frequency) {		//PID initializaton & constants calculation
	Timer_PB7_init(256, frequency);	//Internal timer enabled with the requested frequency and prescaler 256
	T = 1/frequency;

	switch(pid_type) {		//The PID callibration os done by using the Ziegler–Nichols method
		case 1:			//P type
			Kp = 0.5*Ku;
		break;
		case 2:			//PI type
			Kp = 0.45*Ku;
			Ki = 1.2*Kp/T;
		break;
		case 3:			//PID type
			Kp = 0.6*Ku;
			Ki = 2*Kp/T;	//Ti = Kp/Ki
			Kd = Kp*T/8;	//Td = Kd/Kp
		break;
		default:
	}
}

uint8_t pid_controller(uint8_t setpoint) {	//Calculate the corrected output. This function must be called according the period T
	//uint8_t measured_value = read_encoder();	//FUNCTION TO BE IMPLEMENTED
	error = setpoint - measured_value;

	integral = integral + error*T;		//Integral of the error
	derivative = (err - previous_error)/T;	//Differential of the error

	PID_output = Kp*error + Ki*integral + Kd*derivative;	//Derivative part should not be used with coils (like motors) as increases the noise...
	previous_error = error;

	return PID_output;
}