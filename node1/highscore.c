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

void print_highscore(){

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
		fprintf(UART_p, "array_pos: %d\r\n", array_pos); 

	}
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

#endif //F_CPU

