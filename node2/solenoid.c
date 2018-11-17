#ifndef F_CPU
#define F_CPU 16000000	//Clock Speed (Oscillator)

#include <util/delay.h>	//Functions for busy-wait delay loops
#include <avr/io.h>
#include <stdio.h>

#include "solenoid.h"		//Prototypes of functions here defined


void solenoid_init() {		//Solenoid (PB6 [D12 Arduino]) initialization
	DDRB |= (1 << DDB6);	//Enable pin 6 (bit DDB6) of Port B (register DDRB)
	PORTB &= ~(1 << PB6);	//Clear pin 6 (bit PB6) in PORT B (register PORTB), leave other bits unchanged
}

void solenoid_ON() {		//Solenoid activation
    PORTB |= (1 << PB6);	//Set pin 6 (bit PB6) in PORT B (register PORTB) to 1, leave other bits unchanged
}

void solenoid_OFF() {		//Solenoid activation
    PORTB &= ~(1 << PB6);	//Clear pin 6 (bit PB6) in PORT B (register PORTB), leave other bits unchanged
}

void solenoid_push() {		//Solenoid push
    solenoid_ON();
	_delay_ms(100);
    solenoid_OFF();
    _delay_ms(10);
}

#endif