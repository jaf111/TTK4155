#ifndef NOTES_SONGS_H
#define NOTES_SONGS_H

#include <avr/pgmspace.h>

/**************************************************
*************** Prototype functions ***************
**************************************************/
void buzzer_init();		//Buzzer initialization
void buzzer_on();		//Buzzer activation
void buzzer_off();		//Buzzer deactivation
void play_song();		//Reproduces a song
void buzz(uint16_t frequency, uint8_t length);	//Reproduces a note
void my_delay_ms(uint8_t n);	//Delay of ms with variable
void my_delay_us(uint16_t n);	//Delay of us with variable


/**************************************************
**************** All musical notes ****************
**************************************************/
#define NOTE_B0	 31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


/**************************************************
****************** Songs + Tempo ******************
**************************************************/
//https://github.com/gumslone/raspi_buzzer_player/blob/master/buzzer_player.py
const uint16_t PROGMEM mario_melody[] = {
  NOTE_E7,NOTE_E7,0,NOTE_E7,0,NOTE_C7,NOTE_E7,0,NOTE_G7,0,0,0,NOTE_G6,0,0,
  0,NOTE_C7,0,0,NOTE_G6,0,0,NOTE_E6,0,0,NOTE_A6,0,NOTE_B6,0,NOTE_AS6,
  NOTE_A6,0,NOTE_G6,NOTE_E7,NOTE_G7,NOTE_A7,0,NOTE_F7,NOTE_G7,0,NOTE_E7,0,NOTE_C7,NOTE_D7,NOTE_B6,
  0,0,NOTE_C7,0,0,NOTE_G6,0,0,NOTE_E6,0,0,NOTE_A6,0,NOTE_B6,0,
  NOTE_AS6,NOTE_A6,0,NOTE_G6,NOTE_E7,NOTE_G7,NOTE_A7,0,NOTE_F7,NOTE_G7,0,NOTE_E7,0,NOTE_C7,NOTE_D7,
  NOTE_B6,0,0
};
const uint8_t PROGMEM mario_tempo[] = {
	12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
	12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
	12,12,9,9,9,12,12,12,12,12,12,12,12,12,12,12,
	12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
	12,12,9,9,9,12,12,12,12,12,12,12,12,12,12,12,12
};
const uint16_t PROGMEM underworld_melody[] = {
	NOTE_C4,NOTE_C5,NOTE_A3,NOTE_A4,NOTE_AS3,NOTE_AS4,0,0,
	NOTE_C4,NOTE_C5,NOTE_A3,NOTE_A4,NOTE_AS3,NOTE_AS4,0,0,  
	NOTE_F3,NOTE_F4,NOTE_D3,NOTE_D4,NOTE_DS3,NOTE_DS4,0,0,
	NOTE_F3,NOTE_F4,NOTE_D3,NOTE_D4,NOTE_DS3,NOTE_DS4,0,0,
	NOTE_DS4,NOTE_CS4,NOTE_D4,NOTE_CS4,NOTE_DS4,NOTE_DS4,NOTE_GS3,NOTE_G3,
	NOTE_CS4,NOTE_C4,NOTE_FS4,NOTE_F4,NOTE_E3,NOTE_AS4,NOTE_A4,
	NOTE_GS4,NOTE_DS4,NOTE_B3,NOTE_AS3,NOTE_A3,NOTE_GS3,0,0,0
};
const uint8_t PROGMEM underworld_tempo[] = {
	12,12,12,12,12,12,6,3,12,12,12,12,12,12,6,3,
	12,12,12,12,12,12,6,3,12,12,12,12,12,12,6,6,
	18,18,18,6,6,6,6,6,6,18,18,18,18,18,18,10,
	10,10,10,10,10,3,3,3
};
/*const uint16_t PROGMEM adventure_time_melody = {
    notes['D5'],notes['G5'],notes['G5'],notes['G5'],notes['G5'],notes['FS5'],
    notes['FS5'],notes['E5'],notes['D5'],notes['E5'],notes['D5'],notes['D5'],
    notes['C5'],notes['B5'],notes['A5'],notes['G4'],0,notes['C5'],notes['B5'],
    notes['A5'],notes['G4'],0,notes['G5'],0,notes['G5'],notes['G5'],0,notes['G5'],
    notes['FS5'],0,notes['E5'],notes['E5'],notes['D5'],notes['D5'],notes['C5'],
    notes['C5'],notes['C5'],notes['D5'],notes['D5'],notes['A5'], notes['B5'],
    notes['A5'],notes['G4'],notes['G5']
};
const uint8_t PROGMEM adventure_time_tempo = {
	24,24,12,12,12,24,12,24,24,24,12,24,12,12,12,
	12,24,12,24,24,12,24,24,24,24,12,24,12,24,24,
	24,12,12,24,8,24,24,8,8,24,12,24,24,12 
};
const uint16_t PROGMEM star_wars_melody = {
	notes['G4'],notes['G4'],notes['G4'],notes['EB4'],0,notes['BB4'],notes['G4'],
	notes['EB4'],0,notes['BB4'],notes['G4'],0,notes['D4'],notes['D4'],notes['D4'],
	notes['EB4'],0,notes['BB3'],notes['FS3'],notes['EB3'],0,notes['BB3'],notes['G3'],
	0,notes['G4'],0,notes['G3'],notes['G3'],0,notes['G4'],0,notes['FS4'],notes['F4'],
	notes['E4'],notes['EB4'],notes['E4'],0,notes['GS3'],notes['CS3'],0,notes['C3'],
	notes['B3'],notes['BB3'],notes['A3'],notes['BB3'],0,notes['EB3'],notes['FS3'],
	notes['EB3'],notes['FS3'],notes['BB3'],0,notes['G3'],notes['BB3'],notes['D4'],
	0,notes['G4'],0,notes['G3'],notes['G3'],0,notes['G4'],0,notes['FS4'],notes['F4'],
	notes['E4'],notes['EB4'],notes['E4'],0,notes['GS3'],notes['CS3'],0,notes['C3'],
	notes['B3'],notes['BB3'],notes['A3'],notes['BB3'],0,notes['EB3'],notes['FS3'],
	notes['EB3'],notes['BB3'],notes['G3'],notes['EB3'],0,notes['BB3'],notes['G3']
};
const uint8_t PROGMEM star_wars_tempo = {
	2,2,2,4,8,6,2,4,8,6,2,8,2,2,2,4,8,6,2,4,8,6,2,8,2,
	16,4,4,8,2,8,4,6,6,4,4,8,4,2,8,4,4,6,4,2,8,4,2,4,4,
	2,8,4,6,2,8,2,16,4,4,8,2,8,4,6,6,4,4,8,4,2,8,4,4,6,
	4,2,8,4,2,2,4,2,4,8,4,2
};
const uint16_t PROGMEM popcorn_melody = {
	notes['A4'],notes['G4'],notes['A4'],notes['E4'],notes['C4'],notes['E4'],notes['A3'],notes['A4'],
	notes['G4'],notes['A4'],notes['E4'],notes['C4'],notes['E4'],notes['A3'],notes['A4'],notes['B4'],
	notes['C5'],notes['B4'],notes['C5'],notes['A4'],notes['B4'],notes['A4'],notes['B4'],notes['G4'],
	notes['A4'],notes['G4'],notes['A4'],notes['F4'],notes['A4'],notes['A4'],notes['G4'],notes['A4'],
	notes['E4'],notes['C4'],notes['E4'],notes['A3'],notes['A4'],notes['G4'],notes['A4'],notes['E4'],
	notes['C4'],notes['E4'],notes['A3'],notes['A4'],notes['B4'],notes['C5'],notes['B4'],notes['C5'],
	notes['A4'],notes['B4'],notes['A4'],notes['B4'],notes['G4'],notes['A4'],notes['G4'],notes['A4'],
	notes['B4'],notes['C5'],notes['E5'],notes['D5'],notes['E5'],notes['C5'],notes['G4'],notes['C5'],
	notes['E4'],notes['E5'],notes['D5'],notes['E5'],notes['C5'],notes['G4'],notes['C5'],notes['E4'],
	notes['E5'],notes['FS5'],notes['G5'],notes['FS5'],notes['G5'],notes['E5'],notes['FS5'],notes['E5'],
	notes['FS5'],notes['D5'],notes['E5'],notes['D5'],notes['E5'],notes['C5'],notes['E5'],	
	###
	notes['E5'],notes['D5'],notes['E5'],notes['C5'],notes['G4'],notes['C5'],notes['E4'],notes['E5'],
	notes['D5'],notes['E5'],notes['C5'],notes['G4'],notes['C5'],notes['E4'],notes['E5'],notes['FS5'],
	notes['G5'],notes['FS5'],notes['G5'],notes['E5'],notes['FS5'],notes['E5'],notes['FS5'],notes['D5'],
	notes['E5'],notes['D5'],notes['B4'],notes['D5'],notes['E5']
};
const uint8_t PROGMEM popcorn_tempo = {
	8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,
	8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,
	8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,
	8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4
};
const uint16_t PROGMEM twinkle_twinkle_melody = {
	notes['C4'],notes['C4'],notes['G4'],notes['G4'],notes['A4'],notes['A4'],notes['G4'],
	notes['F4'],notes['F4'],notes['E4'],notes['E4'],notes['D4'],notes['D4'],notes['C4'],
	notes['G4'],notes['G4'],notes['F4'],notes['F4'],notes['E4'],notes['E4'],notes['D4'],
	notes['G4'],notes['G4'],notes['F4'],notes['F4'],notes['E4'],notes['E4'],notes['D4'],
	notes['C4'],notes['C4'],notes['G4'],notes['G4'],notes['A4'],notes['A4'],notes['G4'],
	notes['F4'],notes['F4'],notes['E4'],notes['E4'],notes['D4'],notes['D4'],notes['C4']
};
const uint8_t PROGMEM twinkle_twinkle_tempo = {
	4,4,4,4,4,4,2,4,4,4,4,4,4,2,4,4,4,4,4,4,2,4,4,
	4,4,4,4,2,4,4,4,4,4,4,2,4,4,4,4,4,4,2
};
const uint16_t PROGMEM crazy_frog_melody = {
	notes['A4'],notes['C5'],notes['A4'],notes['A4'],notes['D5'],notes['A4'],notes['G4'],
	notes['A4'],notes['E5'],notes['A4'],notes['A4'],notes['F5'],notes['E5'],notes['C5'],
	notes['A4'],notes['E5'],notes['A5'],notes['A4'],notes['G4'],notes['G4'],notes['E4'],
	notes['B4'],notes['A4'],0,notes['A4'],notes['C5'],notes['A4'],notes['A4'],notes['D5'],
	notes['A4'],notes['G4'], notes['A4'],notes['E5'],notes['A4'],notes['A4'],notes['F5'],
	notes['E5'],notes['C5'],notes['A4'],notes['E5'],notes['A5'],notes['A4'],notes['G4'],
	notes['G4'],notes['E4'],notes['B4'],notes['A4'],0,notes['A3'],notes['G3'],notes['E3'],
	notes['D3'],notes['A4'],notes['C5'],notes['A4'],notes['A4'],notes['D5'],notes['A4'],
	notes['G4'],notes['A4'],notes['E5'],notes['A4'],notes['A4'],notes['F5'],notes['E5'],
	notes['C5'],notes['A4'],notes['E5'],notes['A5'],notes['A4'],notes['G4'],notes['G4'],
	notes['E4'],notes['B4'],notes['A4']
};
const uint8_t PROGMEM crazy_frog_tempo = {
	2,4,4,8,4,4,4,2,4,4,8,4,4,4,4,4,4,8,4,8,4,4,1,4,2,
	4,4,8,4,4,4,2,4,4,8,4,4,4,4,4,4,8,4,8,4,4,1,4,8,4,
	4,4,2,4,4,8,4,4,4,2,4,4,8,4,4,4,4,4,4,8,4,8,4,4,1
};
const uint16_t PROGMEM deck_the_halls_melody = {
	notes['G5'],notes['F5'],notes['E5'],notes['D5'],notes['C5'],notes['D5'],notes['E5'],
	notes['C5'],notes['D5'],notes['E5'],notes['F5'],notes['D5'],notes['E5'],notes['D5'],
	notes['C5'],notes['B4'],notes['C5'],0,notes['G5'],notes['F5'],notes['E5'],notes['D5'],
	notes['C5'],notes['D5'],notes['E5'],notes['C5'],notes['D5'],notes['E5'],notes['F5'],
	notes['D5'],notes['E5'],notes['D5'],notes['C5'],notes['B4'],notes['C5'],0,notes['D5'],
	notes['E5'],notes['F5'],notes['D5'],notes['E5'],notes['F5'],notes['G5'],notes['D5'],
	notes['E5'],notes['F5'],notes['G5'],notes['A5'],notes['B5'],notes['C6'],notes['B5'],
	notes['A5'],notes['G5'],0,notes['G5'],notes['F5'],notes['E5'],notes['D5'],notes['C5'],
	notes['D5'],notes['E5'],notes['C5'],notes['D5'],notes['E5'],notes['F5'],notes['D5'],
	notes['E5'],notes['D5'],notes['C5'],notes['B4'],notes['C5'],0
};
const uint8_t PROGMEM deck_the_halls_tempo = {
	2,4,2,2,2,2,2,2,4,4,4,4,2,4,2,2,2,2,2,4,2,2,2,2,2,
	2,4,4,4,4,2,4,2,2,2,2,2,4,2,2,2,4,2,2,4,4,2,4,4,2,
	2,2,2,2,2,4,2,2,2,2,2,2,4,4,4,4,2,4,2,2,2,2
};
const uint16_t PROGMEM manaderna_melody = {
	notes['E4'],notes['E4'],notes['F4'],notes['G4'],notes['G4'],notes['F4'],notes['E4'],
	notes['D4'],notes['C4'],notes['C4'],notes['D4'],notes['E4'],notes['E4'],0,notes['D4'],
	notes['D4'],0,notes['E4'],notes['E4'],notes['F4'],notes['G4'],notes['G4'],notes['F4'],
	notes['E4'],notes['D4'],notes['C4'],notes['C4'],notes['D4'],notes['E4'],notes['D4'],0,
	notes['C4'],notes['C4'],0,notes['D4'],notes['D4'],notes['E4'],notes['C4'],notes['D4'],
	notes['E4'],notes['F4'],notes['E4'],notes['C4'],notes['D4'],notes['E4'],notes['F4'],
	notes['E4'],notes['D4'],notes['C4'],notes['D4'],notes['G3'],0,notes['E4'],notes['E4'],
	notes['F4'],notes['G4'],notes['G4'],notes['F4'],notes['E4'],notes['D4'],notes['C4'],
	notes['C4'],notes['D4'],notes['E4'],notes['D4'],0,notes['C4'],notes['C4']
};
const uint8_t PROGMEM manaderna_tempo = {
	2,2,2,2,2,2,2,2,2,2,2,2,2,4,4,2,4,2,2,2,2,2,2,
	2,2,2,2,2,2,2,4,4,2,4,2,2,2,2,2,4,4,2,2,2,4,4,
	2,2,2,2,1,4,2,2,2,2,2,2,2,2,2,2,2,2,2,4,4,2
};
const uint16_t PROGMEM bonnagard_melody = {
	notes['C5'],notes['C5'],notes['C5'],notes['G4'],notes['A4'],notes['A4'],notes['G4'],
	notes['E5'],notes['E5'],notes['D5'],notes['D5'],notes['C5'],0,notes['G4'],notes['C5'],
	notes['C5'],notes['C5'],notes['G4'],notes['A4'],notes['A4'],notes['G4'],notes['E5'],
	notes['E5'],notes['D5'],notes['D5'],notes['C5'],0,notes['G4'],notes['G4'],notes['C5'],
	notes['C5'],notes['C5'],notes['G4'],notes['G4'],notes['C5'],notes['C5'],notes['G4'],
	notes['C5'],notes['C5'],notes['C5'],notes['C5'],notes['C5'],notes['C5'],notes['C5'],
	notes['C5'],notes['C5'],notes['C5'],notes['C5'],notes['C5'],0,notes['C5'],notes['C5'],
	notes['C5'],notes['G4'],notes['A4'],notes['A4'],notes['G4'],notes['E5'],notes['E5'],
	notes['D5'],notes['D5'],notes['C5'],0
};
const uint8_t PROGMEM bonnagard_tempo = {
	2,2,2,2,2,2,1,2,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,
	2,1,2,4,4,2,2,2,4,4,2,2,1,4,4,2,4,4,2,4,4,4,4,2,
	2,4,2,2,2,2,2,2,1,2,2,2,2,1,1
};
const uint16_t PROGMEM inal_countdown_melody = {
	notes['A3'],notes['E5'],notes['D5'],notes['E5'],notes['A4'],notes['F3'],notes['F5'],
	notes['E5'],notes['F5'],notes['E5'],notes['D5'],notes['D3'],notes['F5'],notes['E5'],
	notes['F5'],notes['A4'],notes['G3'],0,notes['D5'],notes['C5'],notes['D5'],notes['C5'],
	notes['B4'],notes['D5'],notes['C5'],notes['A3'],notes['E5'],notes['D5'],notes['E5'],
	notes['A4'],notes['F3'],notes['F5'],notes['E5'],notes['F5'],notes['E5'],notes['D5'],
	notes['D3'],notes['F5'],notes['E5'],notes['F5'],notes['A4'],notes['G3'],0,notes['D5'],
	notes['C5'],notes['D5'],notes['C5'],notes['B4'],notes['D5'],notes['C5'],notes['B4'],
	notes['C5'],notes['D5'],notes['C5'],notes['D5'],notes['E5'],notes['D5'],notes['C5'],
	notes['B4'],notes['A4'],notes['F5'],notes['E5'],notes['E5'],notes['F5'],notes['E5'],
	notes['D5'],notes['E5']
};
const uint8_t PROGMEM final_countdown_tempo = {
	1,16,16,4,4,1,16,16,8,8,4,1,16,16,4,4,2,4,16,16,8,8,8,
	8,4,4,16,16,4,4,1,16,16,8,8,4,1,16,16,4,4,2,4,16,16,8,
	8,8,8,4,16,16,4,16,16,8,8,8,8,4,4,2,8,4,16,16,1
};*/

#endif 	//NOTES_SONGS_H