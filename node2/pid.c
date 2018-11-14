/*This file has been prepared for Doxygen automatic documentation generation.*/
#include "pid.h"
#include "stdint.h"

#include "PWM.h"
#include "motor.h"

#define Kp	1.00
#define Ki	1.00
#define Kd	0.00
#define SCALING_FACTOR  128		// OPTIMIZED TO 128??

void pid2_Init(struct PID_DATA *pid, uint16_t frequency) {	// Set up PID controller parameters
	PWM_PE3_init(256, frequency);
	
	// Start values for PID controller
	pid->sumError = 0;
	pid->lastProcessValue = 0;
	// Tuning constants for PID loop
	pid->P_Factor = Kp * SCALING_FACTOR;
	pid->I_Factor = Ki * SCALING_FACTOR;
	pid->D_Factor = Kd * SCALING_FACTOR;
	// Limits to avoid overflow
	pid->maxError = MAX_INT / (pid->P_Factor + 1);
	pid->maxSumError = MAX_I_TERM / (pid->I_Factor + 1);
}

int16_t pid2_Controller(struct PID_DATA *pid_st, int16_t setPoint, int16_t processValue) {
	if (int_tim8 == 1) {
		int_tim8 = 0;
		
		int16_t error, p_term, d_term;
		int32_t i_term, output, totalError;

		//setpoint *= motor_encoder_max/255;	//To have setpoint and processValue in the same range...
		error = setPoint - processValue;

		// Calculate Pterm and limit error overflow
		if (error > pid_st->maxError) {
			p_term = MAX_INT;
		}
		else if (error < -pid_st->maxError) {
			p_term = -MAX_INT;
		}
		else {
			p_term = pid_st->P_Factor * error;
		}

		// Calculate Iterm and limit integral runaway
		totalError = pid_st->sumError + error;
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

		output = (p_term + i_term + d_term) / SCALING_FACTOR;
		if(output > MAX_INT) {
			output = MAX_INT;
		}
		else if(output < -MAX_INT) {
			output = -MAX_INT;
		}
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
	int_tim8 = 1;	//Global variable for internal 8-bits timer interruption
}