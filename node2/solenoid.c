#ifndef F_CPU
#define F_CPU 16000000	//Clock Speed (Oscillator)

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

#include "solenoid.h"		//Prototypes of functions here defined


void solenoid_init() {
	DDRB |= (1 << DDB6);	//Pin 6 in Port B set as output (DDB6 - DDRB)
	PORTB &= ~(1 << PB6);	//Clear pin 6, others unchanged
}

void solenoid_ON() {
    PORTB |= (1 << PB6);	//Set pin 6, others unchanged
}

void solenoid_OFF() {
    PORTB &= ~(1 << PB6);
}

void solenoid_push() {
    solenoid_ON();
	_delay_ms(10);
    solenoid_OFF();
    _delay_ms(10);
}

#endif