#ifndef PLAY_SONG_H
#define PLAY_SONG_H

#include <avr/pgmspace.h>

/**************************************************
*************** Prototype functions ***************
**************************************************/
void buzzer_init();		//Buzzer initialization
void buzzer_on();		//Buzzer activation
void buzzer_off();		//Buzzer deactivation
void play_song(uint8_t song_num);	//Reproduces a song
void buzz(uint16_t frequency, uint8_t length);	//Reproduces a note
void my_delay_ms(uint16_t n);	//Delay of ms with variable
void my_delay_us(uint16_t n);	//Delay of us with variable

void play_mario();		//Mario song
void play_underworld();	//Underworld song
void play_adventure();	//Adventure time song
void play_star_wars();	//Star Wars song
void play_popcorn();	//Popcorn song
void play_twinkle();	//Twinkle Twinkle song
void play_frog();		//Crazy frog song
void play_halls();		//Deck_the_halls song
void play_manaderna();	//Manaderna song
void play_bonnagard();	//Bonnagard song
void play_countdown();	//Final countdown song

#endif 	//PLAY_SONG_H