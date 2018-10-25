#ifndef F_CPU
#define F_CPU 16000000	//Clock Speed (Oscillator)#include <util/delay.h>	//Functions for busy-wait delay loops

#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <stdio.h> 		//Standard constants and functions for C (printf..., scanf...)
#include <avr/interrupt.h>	//Interruptions for AVR micro
	
#include "uart.h"
#include "PWM.h"

#define MAX_Width 131	//2.1ms at 50Hz
#define IDLE_Width 94	//1.5ms at 50Hz
#define MIN_Width 56	//0.9ms at 50Hz

void PWM_init(uint16_t prescaler, uint16_t frequency) {		//PWM in timer 1, channel A (PB5)
	TCCR1A |= (0<<WGM10) | (1<<WGM11);	 //Configure fast PWM (mode 14), with value TOP in ICR1
	TCCR1B |= (1<<WGM12) | (1<<WGM13);

	switch(prescaler) {
		case 1 :
			TCCR1B |= (1<<CS00) | (0<<CS01) | (0<<CS02);	//PWM's clock activated, with prescaler N=1
		break;
		case 8 :
			TCCR1B |= (0<<CS00) | (1<<CS01) | (0<<CS02);	//PWM's clock activated, with prescaler N=8
		break;
		case 64 :
			TCCR1B |= (1<<CS00) | (1<<CS01) | (0<<CS02);	//PWM's clock activated, with prescaler N=64
		break;
		case 256 :
			TCCR1B |= (0<<CS00) | (0<<CS01) | (1<<CS02);	//PWM's clock activated, with prescaler N=256
		break;
		case 1024 :
			TCCR1B |= (1<<CS00) | (0<<CS01) | (1<<CS02);	//PWM's clock activated, with prescaler N=1024
		break;
		default :
			TCCR1B |= (0<<CS00) | (0<<CS01) | (0<<CS02);	//PWM's clock deactivated
	}

	TCCR1A |= (0<<COM1A0) | (1<<COM1A1);	//PWM output in channel A (called OC1A) enabled. it clears on Compare Match, and sets at BOTTOM (non-inverting mode)
	DDRB |= (1<<DDB5);		//OC1A is physically connected in Port B, Pin 5 (PB5), so such pin (bit DDB5, register DDRB) is defined as output (1=output, 0=input)

	uint16_t TOP = (F_CPU/frequency) / prescaler - 1;
	ICR1 = TOP;		//ICR1 (defined as TOP) is loaded according to the requested frequency
	
	OCR1A = 0x0000;		//Width of the PWM (initialized to 0 = NOT WORKING)
}

void PWM_MaxLeft() {
	OCR1A = MIN_Width;
}

void PWM_Center() {
	OCR1A = IDLE_Width;
}

void PWM_MaxRight() {
	OCR1A = MAX_Width;
}

void Modify_PWM(uint8_t width) {
	uint8_t PWM_width = 0;
	PWM_width = 0.294*width + MIN_Width;	//Linear relation

	if (PWM_width > MAX_Width) {PWM_width = MAX_Width;}
	if (PWM_width < MIN_Width) {PWM_width = MIN_Width;}

	OCR1A = PWM_width;
}

#endif