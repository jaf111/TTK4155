#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <stdio.h> 		//Standard constants and functions for C (printf..., scanf...)
#include <avr/interrupt.h>	//Functions to implement the interruptions
#include "stdint.h"

#include "pid.h"
#include "uart.h"
#include "PWM.h"
#include "motor.h"

#define Kpp	0.75
#define Kii	0.07
#define Kdd	0.02
#define SCALING_FACTOR  128		// OPTIMIZED TO 128??
#define BYTE_RANGE  35			// encoder_max/255

uint8_t int_tim82 = 0;

int16_t error2 = 0;
int16_t p_term = 0;
int16_t d_term = 0;
int32_t i_term = 0;
int32_t output = 0;
int32_t totalError = 0;

void pid2_Init(pidData_t *pid, uint16_t frequency) {	// Set up PID controller parameters
	PWM_PE3_init(256, frequency);
	
	// Start values for PID controller
	pid->sumError = 0;
	pid->lastProcessValue = 0;
	// Tuning constants for PID loop
	pid->P_Factor = Kpp * SCALING_FACTOR;
	pid->I_Factor = Kii * SCALING_FACTOR;
	pid->D_Factor = Kdd * SCALING_FACTOR;
	// Limits to avoid overflow
	pid->maxError = MAX_INT / (pid->P_Factor + 1);
	pid->maxSumError = MAX_I_TERM / (pid->I_Factor + 1);
}

int16_t pid2_Controller(pidData_t *pid_st, uint8_t setPoint, int16_t processValue) {
	if (int_tim82 == 1) {
		int_tim82 = 0;

		error2 = setPoint - processValue/BYTE_RANGE;
		//fprintf(UART_p, "error2 %4d \r\n", error2);

		if((error2 < 10) && (error2 > -10)) {
			pid_st->sumError = 0;
		}

		// Calculate Pterm and limit error overflow
		if (error2 > pid_st->maxError) {
			p_term = MAX_INT;
		}
		else if (error2 < -pid_st->maxError) {
			p_term = -MAX_INT;
		}
		else {
			p_term = (pid_st->P_Factor + (3/error2)) * error2;
		}
		
		// Calculate Iterm and limit integral runaway
		totalError = pid_st->sumError + error2;
		if(totalError > pid_st->maxSumError) {
			i_term = MAX_I_TERM;
			pid_st->sumError = pid_st->maxSumError;
		}
		else if(totalError < -pid_st->maxSumError) {
			i_term = -MAX_I_TERM;
			pid_st->sumError = -pid_st->maxSumError;
		}
		else {
			pid_st->sumError = totalError;
			i_term = pid_st->I_Factor * pid_st->sumError;
		}

		// Calculate Dterm
		d_term = pid_st->D_Factor * (pid_st->lastProcessValue - processValue);

		pid_st->lastProcessValue = processValue;


		output = ((p_term + i_term + d_term) / SCALING_FACTOR);

//		fprintf(UART_p, "encoder %4d \r\n", processValue/BYTE_RANGE);
		

		/*if(output > MAX_INT) {
			output = MAX_INT;
		}
		else if(output < -MAX_INT) {
			output = -MAX_INT;
		}*/
		if(output > 120) {
			output = 120;
		}
		else if(output < -120) {
			output = -120;
		}
		else if ((output < 55) && (output > 20)) {
			output = 55;
		}
		else if ((output > -55) && (output < -20)) {
			output = -55;
		}

		//fprintf(UART_p, "output %4d", output);
		fprintf(UART_p, ", setPoint %4d", setPoint);
		fprintf(UART_p, ", processValue %4d \r\n", processValue/BYTE_RANGE);

	}
	return((int16_t)output);
}

void pid_Reset_Integrator(pidData_t *pid_st) {
	pid_st->sumError = 0;
}

int16_t get_setPoint() {	//To put here the value read from CAN??
	return 1;
}

int16_t get_measuredValue() {
	return -motor_read_encoder();
}

ISR(TIMER3_COMPA_vect) {	
	int_tim82 = 1;	//Global variable for internal 8-bits timer interruption
}