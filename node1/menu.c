#ifndef F_CPU
#define F_CPU 4915200	//Clock Speed (Oscillator)

#include <util/delay.h>	//Functions for busy-wait delay loops
#include <stdlib.h>		//Functions for dynamic memory management and process control
#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...)
#include <avr/io.h>		//Specific IO for AVR micro (all registers defined inside)
#include <avr/pgmspace.h>	//Interfaces to access data stored in program space (flash memory) of AVR
#include <string.h>
#include <avr/interrupt.h>

#include "menu.h"		//Prototype of functions here implemented
#include "uart.h"		//Prototype functions of USART unit
#include "oled.h"		//Prototype functions of OLED (USB board) unit
#include "buttons.h"	//Prototype functions of buttons (USB board) unit
#include "adc.h"		//Prototype functions of ADC unit
#include "can.h"		//Prototype functions of CAN unit

uint8_t pointerUP = 1;	//Arrow position (starts in 1, after title)
uint8_t pointerLR = 0;	//Menu level (menu or sub-menu)

t_menu* current_menu; 

int displayed_lines = 0;
int currsor_io = 0;

t_menu main_menu;
t_menu game;
t_menu highscore;
t_menu extras;
t_menu options;
t_menu screensaver;
t_menu songs;
t_menu paint;
t_menu brightness;


void menu_system() {
	//Main menu page create
	main_menu = (t_menu){"---Main Menu---", NULL, NULL, NULL}; 
	game = (t_menu){"Game", &main_menu, NULL, NULL};
	highscore = (t_menu){"Highscore", &main_menu, NULL, NULL};
	extras = (t_menu){"Extras", &main_menu, NULL, NULL};
	options = (t_menu){"Options", &main_menu, NULL, NULL};

	//Extras page create
	screensaver = (t_menu){"Screensaver", &extras, NULL, NULL};
	songs = (t_menu){"Songs", &extras, NULL, NULL};
	paint = (t_menu){"Paint", &extras, NULL, NULL};

	//Options page create
	brightness = (t_menu){"Brightness", &options, NULL, NULL};

	//Main menu config
	main_menu.children = &game;
	game.sibling = &highscore;
	highscore.sibling = &extras;
	extras.sibling = &options;
	
	//Extras config
	extras.children = &screensaver;
	screensaver.sibling = &songs;
	songs.sibling = &paint;
	
	//Options config
	options.children = &brightness;
	current_menu = &main_menu;
	print_menu(current_menu);
}

void print_menu(t_menu* menu){
	OLED_clear_all();       		//Entire screen is cleared
	displayed_lines = 0;

	fprintf(OLED_p, menu->name, 0);
	uint8_t line = 1;

	menu = menu->children;
	while(menu && (line < 5)) {
		displayed_lines++;
		OLED_pos(line,20);
		fprintf(OLED_p, menu->name,0);
		line++;
		menu = menu->sibling;
	}
	OLED_home();
}

void menu_init(){
	OLED_clear_all();
	menu_system();
}

uint8_t JoyDU_last = 0;
uint8_t JoyDU_now = 0;
uint8_t JoyLR_last = 0;
uint8_t JoyLR_now = 0;

/*
t_menu* menu_cursor = &main_menu.children;

void menu_navigate(joy_direction_t joy_dir){
	OLED_pos(pointerUP, 5);			//Pointer located on left side (column 5) of current option
	OLED_print_arrow(pointerUP, 5);	//Arrow printed
	switch (joy_dir){
		case JOY_NEUTRAL:
			break;
		case JOY_UP:
			OLED_clear_arrow(pointerUP, 5);	//Current arrow removed
			pointerUP--;					//Pointer updated
			if (pointerUP < 1) {
				pointerUP = displayed_lines-1;	//To ensure a cyclical pointer
			}
			break;
		case JOY_DOWN:
			OLED_clear_arrow(pointerUP, 5);
			pointerUP++;
			if (pointerUP > displayed_lines) {
				pointerUP = 1;
			}
	}
}
*/

void cursor_move() {			//To manage the arrow in the current screen
	OLED_pos(pointerUP, 5);		//Pointer located on left side (column 5) of current option
	if (currsor_io == 0){
		OLED_print_arrow(pointerUP, 5);	
	}

	/*JoyDU_now = ADC_read(JOY_DU);
	JoyLR_now = ADC_read(JOY_LR);

	if ((JoyDU_now != JoyDU_last) && (JoyLR_now != JoyLR_last)) {
		 JoyDU_last = JoyDU_now;
		 JoyLR_last = JoyLR_now;*/


		if (ADC_read(JOY_DU) >= 220) {		//If joystick is moved UP
			OLED_clear_arrow(pointerUP, 5);	//Current arrow removed
			pointerUP--;					//Pointer updated
			if (pointerUP < 1) {
				pointerUP = displayed_lines-1;	//To ensure a cyclical pointer
			}
		}
		else if (ADC_read(JOY_DU) <= 30) {	//If joystick is moved DOWN
			OLED_clear_arrow(pointerUP, 5);
			pointerUP++;
			if (pointerUP > displayed_lines) {
				pointerUP = 1;
			}
		}
		else if (ADC_read(JOY_LR) >= 220) {	//If joystick is moved RIGHT
			if (current_menu->children == NULL){
				return;
			}
			else{
				OLED_home();
				current_menu = current_menu->children;
				
				//fprintf(OLED_p, current_menu->name, 0);

				for (int i = 0; i < pointerUP - 1; i++) {
					current_menu = current_menu->sibling;
				}
				print_menu(current_menu);
				pointerLR = pointerUP;		//Arrow position determines sub-menu screen
				pointerUP = 1;				//Arrow placed in the first line again
				menu_handler();
			}
			
		}
		else if (ADC_read(JOY_LR) <= 30) {	//If joystick is moved LEFT
			if (pointerLR != 0) {			//Only if I am in a child screen
				OLED_clear_all();
				pointerLR = 0;				//Go back to the parent screen
				pointerUP = 1;				//Arrow placed in the first line again
			}
			if (current_menu->parent == NULL){
				return;
			}
				
			else{
				currsor_io = 0;
				current_menu = current_menu->parent;
				print_menu(current_menu);
				//menu_handler();
			}
		}
	//}
	_delay_ms(100);
}


void menu_handler(void){				// Executes menu options
	if(current_menu == &screensaver){
		OLED_clear_all();
		currsor_io = 1;
		OLED_screen_Saver();

	} else if (current_menu == &paint){
		OLED_clear_all();
		currsor_io = 1;
		OLED_paint();

	} else if (current_menu == &game){
		uint8_t score = game_node1_play();
		//current_menu = &main_menu;
	}
}



/*
void ext_INT0_ON(void) {
	DDRD &= ~(1 << PD2); 	//PD2 set as input (1=output, 0=input). Leave others unchanged

	MCUCR |= (1<<ISC01) | (1<<ISC00);	//Rising edge activation for INT0
	GICR |= (1<<INT0);					//External interrupt 0 enabled (pin PD2)
}

void ext_INT0_OFF(void) {
	DDRD &= ~(1 << PD2); 	//disable pin PD2
	GICR &= ~(1<<INT0);		//External interrupt 0 disabled
}

ISR(EXT_INT0_vect) {	
	;
}

*/



////////////////////////////////////////////////////////////


/*
char* menu_matrix[5][menu_col_max] = {
	{"---Main Menu---", "Game", "Scores", "Extras", "Options", ""},
	{"Game", "a", "b", "c", "", ""},
	{"Scores", "a", "b", "c", "d", ""},
	{"Hacking", "Screensaver", "b", "c", "d", "e"},
	{"Options", "Change font", "Brightness", "sub2_opt3", "sub2_opt4", "sub2_opt5"},
};


size_t menu_length = 0;

void print_sub_menu(uint8_t menNum) {
	menNum = menNum + pointerLR;

	OLED_pos(0, 0);
	OLED_print(menu_matrix[menNum][0]);
	
	//size_t n = sizeof(menu_print[menNum]) / sizeof(char*);
	//fprintf(UART_p, "Util: %4d \n\r", n);

	menu_length = 0;		//To know how many positions inside the array are really valid
	for(int j=0; j < menu_col_max; j++) {
		if (menu_matrix[menNum][j] != "") menu_length++;
	}
	//fprintf(UART_p, "Util: %4d \n\r", menu_length);

	for(int i = 1; i < menu_length; i++){
		OLED_pos(i, 20);
		OLED_print(menu_matrix[menNum][i]);
	}

	fprintf(UART_p, "menNum: %4d     ", menNum);
}
*/


// gdb server (avr)

#endif //F_CPU*/