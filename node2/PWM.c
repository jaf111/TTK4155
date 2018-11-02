#ifndef F_CPU
#define F_CPU 16000000	//Clock Speed (Oscillator)#include <util/delay.h>	//Functions for busy-wait delay loops

#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <stdio.h> 		//Standard constants and functions for C (printf..., scanf...)
#include <avr/interrupt.h>	//Interruptions for AVR micro
	
#include "uart.h"
#include "PWM.h"

uint8_t PWM_setPrescaler(uint16_t presc_value) {	//To set the prescaler in the PWM output
	uint8_t pres_config = 0;
	switch(presc_value) {			//As all CSxx occupy the same position, one can just use the same all the time
		case 1:		pres_config = (1<<CS00) | (0<<CS01) | (0<<CS02);	//PWM's clock activated, with prescaler N=1
		break;
		case 8: 	pres_config = (0<<CS00) | (1<<CS01) | (0<<CS02);	//PWM's clock activated, with prescaler N=8
		break;
		case 64: 	pres_config = (1<<CS00) | (1<<CS01) | (0<<CS02);	//PWM's clock activated, with prescaler N=64
		break;
		case 256: 	pres_config = (0<<CS00) | (0<<CS01) | (1<<CS02);	//PWM's clock activated, with prescaler N=256
		break;
		case 1024:	pres_config = (1<<CS00) | (0<<CS01) | (1<<CS02);	//PWM's clock activated, with prescaler N=1024
		break;
		default:	pres_config = (0<<CS00) | (0<<CS01) | (0<<CS02);	//PWM's clock deactivated
	}
	return pres_config;
}

void PWM_PB5_init(uint16_t prescaler, uint16_t frequency) {		//PWM in timer 1, channel A (PB5)
	TCCR1A |= (0<<WGM10) | (1<<WGM11);	 //Configure fast PWM (mode 14), with value TOP in ICR1
	TCCR1B |= (1<<WGM12) | (1<<WGM13);

	TCCR1B |= PWM_setPrescaler(prescaler);	//Prescaler is set in the PWM output

	TCCR1A |= (0<<COM1A0) | (1<<COM1A1);	//PWM output in channel A (called OC1A) enabled. it clears on Compare Match, and sets at BOTTOM (non-inverting mode)
	DDRB |= (1<<DDB5);		//OC1A is physically connected in Port B, Pin 5 (PB5), so such pin (bit DDB5, register DDRB) is defined as output (1=output, 0=input)

	uint16_t TOP = (F_CPU/frequency) / prescaler - 1;
	ICR1 = TOP;		//ICR1 (defined as TOP) is loaded according to the requested frequency
	
	OCR1A = 0x0000;		//Width of the PWM (initialized to 0 = NOT WORKING)
}

void PWM_PE3_init(uint16_t prescaler, uint16_t frequency) {		//PWM in timer 3, channel A (PE3)
	TCCR3A |= (0<<WGM30) | (1<<WGM31);	 //Configure fast PWM (mode 14), with value TOP in ICR3
	TCCR3B |= (1<<WGM32) | (1<<WGM33);
	
	TCCR3B |= PWM_setPrescaler(prescaler);	//Prescaler is set in the PWM output

	TCCR3A |= (0<<COM3A0) | (1<<COM3A1);	//PWM output in channel A (called OC3A) enabled. it clears on Compare Match, and sets at BOTTOM (non-inverting mode)
	DDRE |= (1<<DDE3);	//OC3A is physically connected in Port E, Pin 3 (PB3), so such pin (bit DDB3, register DDRE) is defined as output (1=output, 0=input)

	uint16_t TOP = (F_CPU/frequency) / prescaler - 1;
	ICR3 = TOP;		//ICR3 (defined as TOP) is loaded according to the requested frequency
	
	OCR3A = 0x0000;		//Width of the PWM (initialized to 0 = NOT WORKING)
}

void Timer_PB7_init(uint16_t prescaler, uint16_t frequency) {		//(internal) Timer of 8 bits, in PB7
	TCCR0A |= (0<<WGM00) | (1<<WGM01);	 //Configure Clear Timer on Compare Match (CTC), mode 2. TOP value is OCR0A
	TCCR0B |= (0<<WGM02);
	
	TCCR0B |= PWM_setPrescaler(prescaler);	//Prescaler is set in the PWM output

	TCCR0A |= (0<<COM0A0) | (1<<COM0A1);	//Clear OC0A on Compare Match

	uint16_t TOP = (F_CPU/(frequency*2*prescaler)) - 1;
	OCR0A = TOP;		//ICR3 (defined as TOP) is loaded according to the requested frequency
}

void Set_PWMwidth(char* ch_PWM, uint8_t PWM_width) {
	if (ch_PWM == "PB5") {OCR1A = PWM_width;}
	else if (ch_PWM == "PE3") {OCR3A = PWM_width;}
}

#endif