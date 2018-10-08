#include <avr/io.h>			//Specific IO for AVR micro (all registers defined inside)
#include "led.h"			//Prototypes of functions here defined

void led_init() {
	DDRB |= (1 << DDB0);	//Enable pin 0 (bit DDB0) of Port B (register DDRB)
	PORTB |= (1 << PB0);	//Set pin 0 (bit PB0) in PORT B (register PORTB) to 1, leave other bits unchanged
}

void led_turn_on() {
	PORTB &= ~(1 << PB0);	//Clear pin 0 (bit PB0) in PORT B (register PORTB), leave other bits unchanged
}

void led_turn_off() {
	PORTB |= (1 << PB0);	//Set pin 0 (bit PB0) in PORT B (register PORTB) to 1, leave other bits unchanged
}