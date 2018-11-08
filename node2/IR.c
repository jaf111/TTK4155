#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...) 
#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)

#include "IR.h"
#include "adc.h"

uint8_t index = 0;
uint8_t n_readings = 4;
uint8_t IR_readings[4];
uint16_t IR_sum = 0;
uint8_t IR_init = 0;



void IR_init(){
	for (uint8_t i = 0; i < n_readings; i++){
		IR_readings[i] = ADC_read();		// Fill readings with IR initial values
		IR_sum += IR_readings[i];			// Initialize sum
	}
	IR_init = IR_read_filtered();
}

uint8_t IR_triggered(){
	IR_val = IR_read_filtered();
	if (IR_val < (IR_init-50)){				// Cutoff for deciding if player missed the ball
		return 0x01;						// return 1 => Player missed the ball
	} else{
		return 0x00;						// Return 0 => No ball registered in IR line
	}
}

uint8_t IR_read_filtered(){
	IR_sum -= IR_readings[index];			//Make sure sum is total of only the 4 last measurements

	IR_readings[index] = ADC_read(JOY_LR);	//Read raw data from photodiode

	IR_sum += IR_readings[index];			//Add measurement to total value

	index++;

	if (index >= n_readings){
		index = 0;
	}

	uint8_t IR_avg = IR_sum / n_readings;	//Calculate and update IR value with the average of the 4 last measurements

	return IR_avg;
}