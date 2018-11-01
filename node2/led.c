#include <avr/io.h>			//Specific IO for AVR micro (all registers defined inside)
#include "led.h"			//Prototypes of functions here defined

void led_init() {
	DDRA |= (1 << DDA0);	//Enable pin 0 (bit DDA0) of Port A (register DDRA) as a output (1=output, 0=input)
	PORTA |= (1 << PINA0);	//Set pin PA0) in PORT A high, leave other bits unchanged
}

void led_turn_off() {
	PORTA &= ~(1 << PINA0);	//Clear pin 0 (bit PA0) in PORT A (register PORTA), leave other bits unchanged
}

void led_turn_on() {
	PORTA |= (1 << PINA0);	//Set pin 0 (bit PA0) in PORT A (register PORTA) to 1, leave other bits unchanged
}


/*void led_init() {
	DDRL |= (1 << DDL0);	//Enable pin 0 (bit DDL0) of Port L (register DDRL)
	PORTL |= (1 << PL0);	//Set pin 0 (bit PL0) in PORT L (register PORTL) to 1, leave other bits unchanged
}

void led_turn_off() {
	PORTL &= ~(1 << PL0);	//Clear pin 0 (bit PB0) in PORT B (register PORTB), leave other bits unchanged
}

void led_turn_on() {
	PORTL |= (1 << PL0);	//Set pin 0 (bit PB0) in PORT B (register PORTB) to 1, leave other bits unchanged
}*/