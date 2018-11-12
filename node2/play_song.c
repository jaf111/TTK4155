#ifndef F_CPU
#define F_CPU 16000000	//Clock Speed (Oscillator)

#include <util/delay.h>	//Functions for busy-wait delay loops
#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...) 
#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <avr/pgmspace.h>	//Interfaces to access data stored in program space (flash memory) of AVR

#include "uart.h"			//Added to use fprintf function
#include "notes_songs.h"	//Notes & Songs (stored in FLASH)

void buzzer_init() {		//Buzzer from USB board connected in MISC pin 3
	DDRE |= (1 << DDE2);	//Enable pin 2 (bit DDB4) of PORT B (register DDRB)
	PORTE &= ~(1 << PE2);	//Clear pin 2 (bit PB2) in PORT B (register PORTB), leave other bits unchanged
}

void buzzer_on() {
	PORTE |= (1 << PE2);	//Set pin 2 (bit PB2) in PORT B (register PORTB) to 1, leave other bits unchanged
}

void buzzer_off() {
	PORTE &= ~(1 << PE2);	//Clear pin 2 (bit PB2) in PORT B (register PORTB), leave other bits unchanged
}

void buzz(uint16_t frequency, uint8_t length) {
	uint16_t delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
	// 1 second's worth of microseconds, divided by the frequency, then split in half since there are two phases to each cycle
	
	uint16_t numCycles = (frequency * length) / 1000; // calculate the number of cycles for proper timing
	// multiply frequency (cycles per second), by the number of seconds to get the total number of cycles to produce

	for (uint16_t i=0; i<numCycles; i++) { // for the calculated length of time...
		buzzer_on(); 			// write the buzzer pin high to push out the diaphram
		my_delay_us(delayValue);	// wait for the calculated delay value
		buzzer_off(); 			// write the buzzer pin low to pull back the diaphram
		my_delay_us(delayValue);	// wait again or the calculated delay value
	}
}

void play_song(uint8_t song_num) {		// iterate over the notes of the melody:
	uint8_t size = sizeof(songs_melody[song_num]) / sizeof(uint16_t);
	fprintf(UART_p, "SIZE %4d   \n\r", size);

	for (uint8_t thisNote=0; thisNote<size; thisNote++) {
		//to calculate the note duration, take 1 second divided by the note type
		//e.g. quarter note = 1000/4, eighth note = 1000/8, etc.
		
		uint8_t noteDuration = pgm_read_byte(&(songs_tempo[song_num][thisNote]));
		if (noteDuration != 0) {
			noteDuration = 1000 / noteDuration;	//Duration in ms!
		} else {
			fprintf(UART_p, "thisNote %4d \n\r", thisNote);
			return;		//If noteDuration = 0, it means the songs is over
		}

		buzz(pgm_read_word(&(songs_melody[song_num][thisNote])), noteDuration);	//Time in ms!!

		//to distinguish the notes, set a minimum time between them.
		uint16_t pauseBetweenNotes = noteDuration * 1.30;	//the note's duration + 30%
		my_delay_ms(pauseBetweenNotes);

		//stop the tone playing:
		buzz(0, noteDuration);
	}
}

/*void play_song(uint8_t song_num) {		// iterate over the notes of the melody:
	uint8_t size = sizeof(mario_melody) / sizeof(uint16_t);
	fprintf(UART_p, "SIZE %4d   \n\r", size);

	for (uint8_t thisNote = 0; thisNote<size; thisNote++) {
		//to calculate the note duration, take 1 second divided by the note type
		//e.g. quarter note = 1000/4, eighth note = 1000/8, etc.
		uint8_t noteDuration = 1000 / pgm_read_byte(&(mario_tempo[thisNote]));

		buzz(pgm_read_word(&(mario_melody[thisNote])), noteDuration);		//Time in ms!!

		//to distinguish the notes, set a minimum time between them.
		uint16_t pauseBetweenNotes = noteDuration * 1.30;	//the note's duration + 30%
		my_delay_ms(pauseBetweenNotes);

		//stop the tone playing:
		buzz(0, noteDuration);
	}
}*/

void my_delay_ms(uint16_t n) {	//Delay of ms using a variable as input
	while(n--) {
		_delay_ms(1);
	}
}

void my_delay_us(uint16_t n) {	//Delay of us using a variable as input
	while(n--) {
		_delay_us(1);
	}
}

void play_mario() 		{play_song(0);}		//Mario song
void play_underworld()	{play_song(1);}		//Underworld song
void play_adventure()	{play_song(2);}		//Adventure time song
void play_star_wars()	{play_song(3);}		//Star Wars song
void play_popcorn()		{play_song(4);}		//Popcorn song
void play_twinkle()		{play_song(5);}		//Twinkle Twinkle song
void play_frog()		{play_song(6);}		//Crazy frog song
void play_halls()		{play_song(7);}		//Deck_the_halls song
void play_manaderna()	{play_song(8);}		//Manaderna song
void play_bonnagard()	{play_song(9);}		//Bonnagard song
void play_countdown()	{play_song(10);}	//Final countdown song


#endif