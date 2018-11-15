#ifndef F_CPU
#define F_CPU 4915200	//Clock Speed (Oscillator)

#include <stdio.h>			
#include <avr/io.h> 
#include <stdlib.h>
#include <util/delay.h>			


#include "oled.h"	
#include "buttons.h"
#include "adc.h"
#include "highscore.h"		

int char_selector = 0;
int array_pos = 0;


highscore_t nr7;
highscore_t nr6;
highscore_t nr5;
highscore_t nr4;
highscore_t nr3;
highscore_t nr2;
highscore_t nr1;

highscore_t new_score;


void highscore_init(){
	nr7 = (highscore_t){NULL, NULL, NULL};
	nr6 = (highscore_t){NULL, NULL, &nr7};
	nr5 = (highscore_t){NULL, NULL, &nr6};
	nr4 = (highscore_t){NULL, NULL, &nr5};
	nr3 = (highscore_t){NULL, NULL, &nr4};
	nr2 = (highscore_t){NULL, NULL, &nr3};
	nr1 = (highscore_t){NULL, 10, &nr2}; 
		
	new_score = (highscore_t){NULL, NULL, NULL};

}


void print_highscore(){
	OLED_clear_all();
	OLED_update();
	uint8_t line = 1;
	highscore_t* highscore;
	highscore = &nr1;

	while(highscore->next != NULL || (line < 8)) {
		OLED_pos(line, 20);
		OLED_print_all(line);
		OLED_pos(line, 24);
		OLED_print_all(highscore->name);
		OLED_pos(line, 40);
		OLED_print_all(highscore->score);
		line++;
		highscore = highscore->next;
	}
	OLED_home();
}


highscore_t create_name(highscore_t * foo){
	OLED_clear_all();
	OLED_update(); 
	char new_name[8] = {0};
	//char new_name = malloc(sizeof(char) * 9);
	
	if(!new_name){
		//fprintf (UART_p, "error\r\n", 0);
    	return;
	}
	int char_selector = 0;
	OLED_pos(3,0);
	OLED_print_all("Name: ");//fprintf(OLED_p, "Name: ", 0);
	
	while(!(BUTTON_R && BUTTON_L)){
		OLED_update(); 
		OLED_pos(3,40);
		OLED_print_all(foo->name);
		OLED_pos(5,30);
		OLED_print_char(letter_select());
		_delay_ms(200);

		if(BUTTON_R && array_pos <= 4){
			foo->new_name[array_pos] = letter_select();
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
		fprintf(UART_p, "%s\n\r",new_name);
		fprintf(UART_p, "\r\n",0);
		 

	}
	return foo;
}


char letter_select(){
	char letter = 'A'; //starts select on A
	
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


void insert_score(char* name, uint8_t* score){
	highscore_t* highscore;
	highscore = &nr1;
	int place = check_score(score);
	if (place == 0){
		return;
	}

	for (int i = 1; i < place; i++){
	 	highscore = highscore->next;
	}
	highscore_copy(highscore, highscore->next);
	highscore->name = name;
	highscore->score = score;
}


void highscore_copy(highscore_t* highscore_current, highscore_t* highscore_next){
	char name = highscore_next->name;
	uint8_t score = highscore_next->score;
	highscore_next->name = highscore_current;
	highscore_next->score = highscore_current->score; 
	if (highscore_next->next = NULL){
		return;
	}

	highscore_current = highscore_current->next;
	highscore_current->name = name;
	highscore_current->score = score;
	highscore_copy(highscore_current, highscore_current->next);	
}


int check_score(uint8_t* score){
	highscore_t* highscore;
	highscore = &nr1;
	int place = 1;
	int line = 1; 
	while(highscore->next && (line < 7)){
		line++;
		if (score > &(highscore->score)){
			return place;
		}
		highscore = highscore->next;
		place += 1;
	}

	return 0;
}




#endif //F_CPU

