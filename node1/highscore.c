#include <stdio.h>			
#include <avr/io.h> 		


#include "oled.h"	
#include "buttons.h"
#include "adc.h"		



void print_highscore(){

}

void create_name(){
	char new_name[8];
	int char_selector = 0;
	oled_pos(3,0);
	fprintf(OLED_p, "Name: ", 0);

	while(!(BUTTON_R && BUTTON_R)){
		
		fprintf(OLED_p, new_name, 0);
		oled_pos(5,10);
		fprrintf(OLED_p, display_letter(char_selector), 0);

	}
}


char display_letter(char_selector){
	
	if (ADC_read(JOY_DU) >= 220) { //If joystick is moved UP
		if (char_selector == 0){
			char_selector = 25;
		}
		return ('A' + char_selector)
	}
	if (ADC_read(JOY_DU) <= 30) { //If joystick is moved DOWN
		if (char_selector == 25){
			char_selector = 0;
		}
		return('A' + char_selector)
	}
}

