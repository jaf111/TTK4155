#ifndef PLAY_SONG_H
#define PLAY_SONG_H

#include <avr/pgmspace.h>

/**************************************************
*************** Prototype functions ***************
**************************************************/
void buzzer_init(void);		//Buzzer initialization
void buzzer_on(void);		//Buzzer activation
void buzzer_off(void);		//Buzzer deactivation

void buzz(uint16_t frequency, uint8_t length);	//Reproduces a note

void game_start_song(void);			//Starting song
void game_finish_song(void);		//Finishing song
void game_song(uint8_t song_num);	//Reproduce a song (in game)

void play_mario(void);				//Mario song
void play_adventure(void);			//Adventure time song
void play_song(uint8_t song_num);	//Reproduce a song (in menu)

void my_delay_ms(uint16_t n);		//Delay of ms with variable
void my_delay_us(uint16_t n);		//Delay of us with variable


#endif 	//PLAY_SONG_H