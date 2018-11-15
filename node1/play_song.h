#ifndef PLAY_SONG_H
#define PLAY_SONG_H

#include <avr/pgmspace.h>

/**************************************************
*************** Prototype functions ***************
**************************************************/
void buzzer_init(void);		//Buzzer initialization
void buzzer_on(void);		//Buzzer activation
void buzzer_off(void);		//Buzzer deactivation
void play_song(uint8_t song_num);	//Reproduces a song
void buzz(uint16_t frequency, uint8_t length);	//Reproduces a note
void my_delay_ms(uint16_t n);	//Delay of ms with variable
void my_delay_us(uint16_t n);	//Delay of us with variable

void play_mario(void);			//Mario song
void play_underworld(void);		//Underworld song
void play_adventure(void);		//Adventure time song
void play_star_wars(void);		//Star Wars song
void play_popcorn(void);		//Popcorn song
void play_twinkle(void);		//Twinkle Twinkle song
void play_frog(void);			//Crazy frog song
void play_halls(void);			//Deck_the_halls song
void play_manaderna(void);		//Manaderna song
void play_bonnagard(void);		//Bonnagard song
void play_countdown(void);		//Final countdown song

#endif 	//PLAY_SONG_H