#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...) 
#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <avr/interrupt.h>

#include "buttons.h"
#include "IR.h"
#include "motor.h"
#include "servo.h"

uint8_t time_score;
uint8_t game_over = 0;

ISR(TIMER2_OVF_vect){
	time_score++;		// Increment time score by a second
}

void game_init(){
	time_score = 0;
	 //Timer2 Settings: Timer Prescaler /64,
 	TCCR2 |= (1<<CS22);    // turn on CS22 bit
 	TCCR2 &= ~((1<<CS21) | (1<<CS20));    // turn off CS21 and CS20 bits
 // Use normal mode
 	TCCR2 &= ~((1<<WGM21) | (1<<WGM20));   // turn off WGM21 and WGM20 bits
 	TCNT1 = 
 	TIMSK = (1 << TOIE1);
	// Calibrate motor position etc . . . . . .

}

void game_play(){
	game_init();




}