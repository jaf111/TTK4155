#include <avr/io.h>
#include "led.h"

//Using Port B, pin PB0 on ATmega162

void led_init(){
	DDRB |= (1 << DDB0);
	PORTB |= (1 << PB0);
}

void led_turn_on(){
	PORTB &= ~(1 << PB0);
}

void led_turn_off(){
	PORTB |= (1 << PB0);
}