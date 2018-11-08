#ifndef F_CPU
#define F_CPU 16000000	//Clock Speed (Oscillator)

#include <util/delay.h>	//Functions for busy-wait delay loops
#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...) 
#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <avr/pgmspace.h>	//Interfaces to access data stored in program space (flash memory) of AVR

#include "uart.h"			//Added to use fprintf function
#include "notes_songs.h"	//Prototype functions

void buzzer_init() {		//Buzzer from USB board connected in MISC pin 3
	DDRB |= (1 << DDB4);	//Enable pin 4 (bit DDB4) of PORT B (register DDRB)
	PORTB &= ~(1 << PB4);	//Clear pin 4 (bit PB4) in PORT B (register PORTB), leave other bits unchanged
}

void buzzer_on() {
	PORTB |= (1 << PB4);	//Set pin 4 (bit PB4) in PORT B (register PORTB) to 1, leave other bits unchanged
}

void buzzer_off() {
	PORTB &= ~(1 << PB4);	//Clear pin 4 (bit PB4) in PORT B (register PORTB), leave other bits unchanged
}

void buzz(uint16_t frequency, uint8_t length) {
	if (length == 0) {return;}		//If length is 0, it means the songs is over

	uint16_t delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
	// 1 second's worth of microseconds, divided by the frequency, then split in half since there are two phases to each cycle
	
	uint16_t numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
	// multiply frequency (cycles per second), by the number of seconds to get the total number of cycles to produce

	for (uint16_t i=0; i<numCycles; i++) { // for the calculated length of time...
		buzzer_on(); 			// write the buzzer pin high to push out the diaphram
		my_delay_us(delayValue);	// wait for the calculated delay value
		buzzer_off(); 			// write the buzzer pin low to pull back the diaphram
		my_delay_us(delayValue);	// wait again or the calculated delay value
	}
}

void play_song(uint8_t song_num) {		// iterate over the notes of the melody:
	fprintf(UART_p, "Mario Theme \n\r", 0);
	
	uint8_t size = sizeof(songs_melody[song_num]) / sizeof(uint16_t);
	//fprintf(UART_p, "SIZE %4d   \n\r", sizeof(uint8_t));
	for (uint8_t thisNote = 0; thisNote<size; thisNote++) {
		//to calculate the note duration, take 1 second divided by the note type
		//e.g. quarter note = 1000/4, eighth note = 1000/8, etc.
		uint8_t noteDuration = pgm_read_byte(&(songs_tempo[song_num][thisNote]));
		if (noteDuration != 0) {
			noteDuration = 1000 / pgm_read_byte(&(songs_tempo[song_num][thisNote]));
		} else {noteDuration = 0;}

		buzz(pgm_read_word(&(songs_melody[song_num][thisNote])), noteDuration);	//Time in ms!!

		//to distinguish the notes, set a minimum time between them.
		uint8_t pauseBetweenNotes = noteDuration * 1.30;	//the note's duration + 30%
		my_delay_ms(pauseBetweenNotes);

		//stop the tone playing:
		buzz(0, noteDuration);
	}
}

void my_delay_ms(uint8_t n) {	//Delay of ms using a variable as input
	while(n--) {
		_delay_ms(1);
	}
}

void my_delay_us(uint16_t n) {	//Delay of us using a variable as input
	while(n--) {
		_delay_us(1);
	}
}

#endif