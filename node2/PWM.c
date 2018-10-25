#include <util/delay.h>	//Functions for busy-wait delay loops
#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <stdio.h> 		//Standard constants and functions for C (printf..., scanf...)
	
#include "uart.h"
#include "PWM.h"

void PWM_init() {
	TCCR1A |= (0<<WGM10) | (1<<WGM11);	 //Configure fast PWM (mode 14), with value TOP = ICR1
	TCCR1B |= (1<<WGM12) | (1<<WGM13);

	TCCR1B |= (0<<CS00) | (0<<CS01) | (1<<CS02);	//PWM's clock activated, with prescaler N=256

	TCCR1A |= (0<<COM1A0) | (1<<COM1A1);	//PWM output in channel A (called OC1A) enabled. it clears on Compare Match, and sets at BOTTOM (non-inverting mode)
	DDRB |= (1<<DDB5);		//OC1A is physically connected in Port B, Pin 5 (PB5), so such pin (bit DDB5, register DDRB) is defined as output (1=output, 0=input)

	TIM16_WriteICR1(0x04E1);		//ICR1 (defined as TOP) must be 0x04E1 to ensure f_out = 50Hz
	TIM16_WriteOCR1A(0x0000);		//Width of the PWM (0 = NOT WORKING)
}

void PWM_Left() {
	TIM16_WriteOCR1A(0x0038);		//0x38 (56d) gives a pulse of 0,9 width
}

void PWM_Center() {
	TIM16_WriteOCR1A(0x005E);		//0x5E (94d) gives a pulse of 1,5 width
}

void PWM_Right() {
	TIM16_WriteOCR1A(0x0083);		//0x83 (131d) gives a pulse of 2,1 width
}

uint8_t TIM16_ReadTCNT1() {
	unsigned char sreg;
	uint8_t i;
	/* Save global interrupt flag */
	sreg = SREG;
	/* Disable interrupts */
	__disable_interrupt();
	/* Read TCNT1 into i */
	i = TCNT1;
	/* Restore global interrupt flag */
	SREG = sreg;
	return i;
}

void TIM16_WriteICR1(uint16_t i) {
	unsigned char sreg;

	//Save global interrupt flag
	sreg = SREG;
	//Disable interrupts
	__disable_interrupt();
	//Set ICR1 to i
	ICR1H = 0x00FF & (i >> 8);	//Higher part of ICR1
	ICR1L = 0x00FF & i;			//Lower part of ICR1
	//ICR1 = i;

	//Restore global interrupt flag
	SREG = sreg;
}

void TIM16_WriteOCR1A(uint16_t i) {
	unsigned char sreg;

	//Save global interrupt flag
	sreg = SREG;
	//Disable interrupts
	__disable_interrupt();
	//Set OCR1A to i
	OCR1AH = 0x00FF & (i >> 8);	//Higher part of OCR1A
	OCR1AL = 0x00FF & i;			//Lower part of OCR1A
	//OCR1A = i;

	//Restore global interrupt flag
	SREG = sreg;
}