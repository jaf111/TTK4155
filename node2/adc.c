#include <stdio.h>			//Standard constants and functions for C (printf..., scanf...)
#include <avr/io.h> 		//Specific IO for AVR micro (all registers defined inside)

#include "adc.h"			//Prototypes of functions here defined

void ADC_init(void){
	DDRF |= (1 << DDF0);	//Enable pin 0 (bit DDF0) of Port F
	PORTF &= ~(1 << PF0);	//Set pin to low
	ADCSRA |= (1 << ADEN);	//Turn ADC on
	ADMUX |= (1 << REFS1) | (1 << REFS0); //Internal 2.56V Voltage Reference with external capacitor at AREF pin  
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	
}

uint16_t ADC_read() {
	uint16_t data = 0;
	ADCSRA |= (1 << ADSC); //start conversion
	while(!(ADCSRA & (1 << ADIF))); //loop until ADC conversion completes
	uint16_t data_l = ADCL;
	uint16_t data_h = (ADCH << 8);
	data = data_h + data_l;
	
	return data;
}