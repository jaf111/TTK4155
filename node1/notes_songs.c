/*#include <util/delay.h>	//Functions for busy-wait delay loops
#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...) 
#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)

#include "uart.h"			//Added to use fprintf function
#include "notes_songs.h"	//Prototype functions


void buzzer_init() {		//Buzzer from USB board connected in MISC pin 3
	DDRB |= (1 << DDB3);	//Enable pin 0 (bit DDB0) of Port B (register DDRB)
	PORTB |= (1 << PB3);	//Set pin 0 (bit PB0) in PORT B (register PORTB) to 1, leave other bits unchanged
}

void buzzer_on() {
	PORTB &= ~(1 << PB3);	//Clear pin 0 (bit PB0) in PORT B (register PORTB), leave other bits unchanged
}

void buzzer_off() {
	PORTB |= (1 << PB3);	//Set pin 0 (bit PB0) in PORT B (register PORTB) to 1, leave other bits unchanged
}

void buzz(uint16_t frequency, uint16_t length) {
	uint16_t delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
	// 1 second's worth of microseconds, divided by the frequency, then split in half since there are two phases to each cycle
	
	uint16_t numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
	// multiply frequency, which is really cycles per second, by the number of seconds to get the total number of cycles to produce
	
	for (uint16_t i=0; i<numCycles; i++) { // for the calculated length of time...
		buzzer_on(); 			// write the buzzer pin high to push out the diaphram
		_delay_us(delayValue);	// wait for the calculated delay value
		buzzer_off(); 			// write the buzzer pin low to pull back the diaphram
		_delay_us(delayValue);	// wait again or the calculated delay value
	}
}

void play_song() {		// iterate over the notes of the melody:
	/*fprintf(UART_p, "Mario Theme", 0);
	
	uint8_t size = sizeof(mario_melody) / sizeof(uint8_t);
	for (uint8_t thisNote = 0; thisNote<size; thisNote++) {
		//to calculate the note duration, take 1 second divided by the note type
		//e.g. quarter note = 1000/4, eighth note = 1000/8, etc.
		uint8_t noteDuration = 1000 / mario_tempo[thisNote];

		buzz(mario_melody[thisNote], noteDuration);		//Time in ms!!

		//to distinguish the notes, set a minimum time between them.
		uint8_t pauseBetweenNotes = noteDuration * 1.30;	//the note's duration + 30%
		_delay_ms(pauseBetweenNotes);

		//stop the tone playing:
		buzz(0, noteDuration);
	}
}*/