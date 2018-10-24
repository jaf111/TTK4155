#include <util/delay.h>	//Functions for busy-wait delay loops
#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <stdio.h> 		//Standard constants and functions for C (printf..., scanf...)
	
#include "uart.h"
#include "PWM.h"

//#define TOP		DDB7
//#define BOTTOM	0x00

void PWM_init(void) {
	TCCR0A |= (1<<WGM00) | (1<<WGM01);	 //Configure fast PWM mode, with value TOP = 0xFF
	TCCR0B |= (0<<WGM02);

	TCCR0B |= (1<<CS00) | (0<<CS01) | (1<<CS02);	//clk I/O /1024 (From prescaler)

	//OC0A (PWM output) is connected in PB7, and enabled when previous configuration
	DDRB |= (1<<DDB7);	//Pin 7 (bit DDB7) of PORT B (register DDRB) as a output (1=output, 0=input)
	DDRG |= (1<<DDG5);

	OCR0A = 0x70;	//Width of the PWM (a random number to test now)
}

void PWM_ON(void) {
	TCCR0A |= (0<<COM0A0) | (1<<COM0A1);	//PWM output (OC0A) enabled. Clear OC0A on Compare Match, set OC0A at BOTTOM (non-inverting mode)
}

void PWM_OFF(void) {
	TCCR0A |= (0<<COM0A0) | (0<<COM0A1);	//PWM output (OC0A) disabled.
}