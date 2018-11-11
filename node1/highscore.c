#ifndef F_CPU
#define F_CPU 4915200	//Clock Speed (Oscillator)

#include <stdio.h>			
#include <avr/io.h> 
#include <util/delay.h>			


#include "oled.h"	
#include "buttons.h"
#include "adc.h"
#include "highscore.h"		

int char_selector;
int array_pos = 0;


highscore_t nr1;
highscore_t nr2;
highscore_t nr3;
highscore_t nr4;
highscore_t nr5;
highscore_t nr6;
highscore_t nr7;
highscore_t new_score;


void highscore_init(){
	nr1 = (highscore_t){NULL, NULL, &nr2}; 
	nr2 = (highscore_t){NULL, NULL, &nr3};
	nr3 = (highscore_t){NULL, NULL, &nr4};
	nr4 = (highscore_t){NULL, NULL, &nr5};
	nr5 = (highscore_t){NULL, NULL, &nr6};
	nr6 = (highscore_t){NULL, NULL, &nr7};
	nr7 = (highscore_t){NULL, NULL, NULL};

}


void print_highscore(){
	OLED_clear_all();
	uint8_t line = 1;
	highscore_t* highscore;
	highscore = nr1;

	while(highscore && (line < 7)) {
		OLED_pos(line,20);
		fprintf(OLED_p, menu->name,0);
		line++;
		highscore = highscore->next;
	}
	OLED_home();
}


void create_name(){
	OLED_update(); 
	char new_name[8];
	int char_selector = 0;
	OLED_pos(3,0);
	fprintf(OLED_p, "Name: ", 0);
	
	while(!(BUTTON_R && BUTTON_R)){
		OLED_update(); 
		OLED_pos(3,40);
		OLED_print_all(new_name);
		OLED_pos(5,30);
		OLED_print_char(letter_select());
		_delay_ms(200);

		if(BUTTON_R && array_pos <= 4){
			new_name[array_pos] = letter_select();
			array_pos += 1;
		}
		if(BUTTON_L && array_pos >= 0){
			new_name[array_pos] = ' ';
			array_pos -= 1;
			new_name[array_pos] = ' ';
			if (array_pos <= 0){
				array_pos = 0;
			}
		} 

	}
	new_score = (highscore_t){new_name, NULL};
}


char letter_select(){
	char letter = 'A';
	
	if (ADC_read(JOY_DU) >= 220) { //moved UP
		if (char_selector <= 0){
			char_selector = 25;
			return(letter + char_selector);
		}
		char_selector -= 1;
		
	}
	if (ADC_read(JOY_DU) <= 30) { //moved DOWN
		if (char_selector >= 25){
			char_selector = 0;
			return(letter + char_selector);
			
		}
		char_selector += 1;
		 		
	}
	return(letter + char_selector);
}


void insert_score(char* name, uint8_t score){
	highscore_t* highscore;
	highscore = nr1;
	int place = check_score(score);
	
	if (place == 0){
		return;
	}
	highscore_copy(place);

	for (int i = 1; i < place; i++){
	 	highscore = highscore->next;
	}
	highscore.name = &name;
	highscore.score = score;
}

void highscore_copy(int place){
	//make sure the highscore does not owerwrite itself
	highscore_t* highscore;
	highscore = nr1;
	for (int i = place; i > 0; i--){
		highscore.name = highscore.next;
		highscore.score = score;
	}
}

void check_score(uint8_t score){
	highscore_t* highscore;
	highscore = nr1;
	int place = 1;
	
	while(highscore && (line < 7)){
		if (score > highscore->score){
			return place;
		}
		highscore = highscore->next;
		place += 1;
	}
	return 0;
}





#endif //F_CPU

