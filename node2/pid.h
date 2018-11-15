/*This file has been prepared for Doxygen automatic documentation generation.*/
#ifndef PID_H
#define PID_H

#include "stdint.h"

// Maximum value of variables
#define MAX_INT         INT16_MAX		//Max int16 = 0x7fff (no uint!)
#define MAX_LONG        INT32_MAX		//Max int32 = 0x7fffffff (no uint!)
#define MAX_I_TERM      (MAX_LONG/2)

typedef struct {
	int16_t lastProcessValue;
	int32_t sumError;
	int16_t P_Factor;
	int16_t I_Factor;
	int16_t D_Factor;
	int16_t maxError;
	int32_t maxSumError;
} pidData_t;

void pid2_Init(pidData_t *pid, uint16_t frequency);
int16_t pid2_Controller(pidData_t *pid_st, int16_t setPoint, int16_t processValue);
void pid_Reset_Integrator(pidData_t *pid_st);
int16_t get_setPoint(void);
int16_t get_measuredValue(void);

#endif