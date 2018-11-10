#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <stdio.h> 		//Standard constants and functions for C (printf..., scanf...)
#include <float.h>
#include <avr/interrupt.h>	//Functions to implement the interruptions
	
#include "uart.h"
#include "PWM.h"
#include "motor.h"
#include "pid_contr.h"	//Function prototypes here defined

//Continuous version =>	u = Kp*e + Ki*∫edt + Kd*(de/dt) where e is the error (the difference between actual and target
//Discrete version =>	u(n) = Kp*e(n) + T*Ki*∑e(i) + (Kd/T)*(e(n)−e(n−1)), where T is the sampling period.

int16_t PID_output = 0;
int16_t error = 0;
int16_t previous_error = 0;
uint8_t Ku = 3;		//Ultimate gain
uint8_t Kp = 0;		//Proptional constant
uint8_t Ki = 0;		//Integral constant
uint8_t Kd = 0;		//Derivative constant
int16_t integral = 0;
int16_t derivative = 0;
uint16_t T = 0;
uint8_t int_tim8 = 0;

void pid_init(uint8_t pid_type, uint16_t frequency) {		//PID initializaton & constants calculation
			//Ultimate gain
	//Timer_PB7_init(1024, frequency);	//Internal timer enabled with the requested frequency and prescaler 256
	PWM_PE3_init(256, frequency);

	T = 1000/frequency;
	
	switch(pid_type) {		//The PID callibration os done by using the Ziegler–Nichols method
		case 1:			//P type
			Kp = 0.5*Ku;
		break;
		case 2:			//PI type
			Kp = 1;//0.45*Ku;
			Ki = 2;//1.2*Kp/T;
		break;
		case 3:			//PID type
			Kp = 0.6*Ku;
			Ki = 2*Kp/T;	//Ti = Kp/Ki
			Kd = Kp*T/8;	//Td = Kd/Kp
		break;
		default:
			;
	}
}

int16_t pid_controller(int16_t setpoint) {	//Calculate the corrected output. This function must be called according the period T
	int16_t measured_value = motor_read_encoder()/2;	//FUNCTION TO BE IMPLEMENTED

	if(int_tim8 == 1) {
		int_tim8 = 0;

		setpoint = setpoint - 128;
		/*if (setpoint == 0) {
			setpoint = measured_value;
		}*/
		
		error = setpoint - measured_value;
		
		if ((error > 7) || (error < -7)) {		//If the error is too big, integral (accumulation) value must be restarted
			integral = 0;
		}

		integral = integral + error*(T/1000);		
		derivative = (error - previous_error)/(T/1000);	
		
		PID_output = Kp*error + Ki*integral + Kd*derivative;	//Derivative part should not be used with coils (like motors) as increases the noise...
		PID_output = PID_output/2;
		fprintf(UART_p, "PID_output %4d \r\n", PID_output);

		previous_error = error;
		//fprintf(UART_p, "error %4d, setpoint %4d, measured_value %4d \r\n", error, setpoint, measured_value);
		//fprintf(UART_p, "P %4d \r\n", Kp);
		//fprintf(UART_p, "PID output: %4d\n", PID_output);
		
		if(PID_output >= 255) {
			PID_output = 255; 
		}
		else if((PID_output < 50) && (PID_output > 20)) {
			PID_output = 50;
		}
		else if(PID_output <= -255) {
			PID_output = -255;
		}
		else if((PID_output > -50) && (PID_output < -20)) {
			PID_output = -50;
		}
		
		//fprintf(UART_p, "REAL PID_output %4d \r\n", PID_output);
	}

	return PID_output;
}

//ISR checks the interruptions vector once the previously defined interruption is executed.
//If a function for it is not defined, the AVR would restart the system automatically

/*ISR(TIMER0_COMPA_vect) {	
	int_tim8 = 1;		//Global variable for internal 8-bits timer interruption
	fprintf(UART_p,"Anterrupt \r\n",0);
}*/

ISR(TIMER3_COMPA_vect) {	
	int_tim8 = 1;		//Global variable for internal 8-bits timer interruption
	//fprintf(UART_p,"Anterddddddddddddddddddddddddddddddddddrupt \r\n",0);
}