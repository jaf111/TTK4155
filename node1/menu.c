#include <util/delay.h>	//Functions for busy-wait delay loops
#include <stdlib.h>		//Functions for dynamic memory management and process control
#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...)
#include <avr/io.h>		//Specific IO for AVR micro (all registers defined inside)
#include <avr/pgmspace.h>	//Interfaces to access data stored in program space (flash memory) of AVR

#include "menu.h"		//Prototype of functions here implemented
#include "uart.h"		//Prototype functions of USART unit
#include "oled.h"		//Prototype functions of OLED (USB board) unit
#include "buttons.h"	//Prototype functions of buttons (USB board) unit
#include "adc.h"		//Prototype functions of ADC unit

uint8_t pointerUP = 1;	//Arrow position (starts in 1, after title)
uint8_t pointerLR = 0;	//Menu level (menu or sub-menu)

t_menu* current_menu; 

int displayed_lines = 0;

t_menu* menu(char* name, t_menu* parent){
	t_menu* new_menu = malloc(sizeof(t_menu)); 	// PREVIOUSLY: t_menu* new_menu = malloc(sizeof(new_menu)); 
	new_menu->name = name;
	new_menu->parent = parent;
	new_menu->children = NULL;
	new_menu->sibling = NULL;

	return new_menu;
}

void set_sibling(t_menu* menu, t_menu* new_sibling){
	menu->sibling = new_sibling;
}

void set_children(t_menu* menu, t_menu* new_children){
	(menu->children) = (new_children);
}

void menu_system(){
	//Main menu page create
	t_menu* main_menu = menu("---Main Menu---", NULL);
	t_menu* game = menu("Game", main_menu);
	//t_menu* game2 = menu("Game", main_menu);
	t_menu* highscore = menu("Highscore", main_menu);
	t_menu* extras = menu("Extras", main_menu);
	t_menu* options = menu("Options", main_menu);
	
	//Extras page create
	t_menu* screensaver = menu("Screensaver", extras);
	t_menu* songs = menu("Songs", extras);

	//Options page create
	t_menu* brightness = menu("Brightness", options);

	fprintf(UART_p, game->name,0);
	//Main menu config
	set_children(main_menu, game);
	//fprintf(UART_p, game->name,0);
	//fprintf(UART_p, game->name,0);
	set_sibling(game, highscore);
	set_sibling(highscore, extras);
	set_sibling(extras, options);
	fprintf(UART_p, " \r\n",0);
	//Extras config
	set_children(extras, screensaver);
	set_sibling(screensaver, songs);
	
	//Options config
	set_children(options, brightness);

	current_menu = main_menu;
	
	print_menu(current_menu);
	
	//ASK STUDASS
	//fprintf(OLED_p, current_menu->name, 0);
	//OLED_pos(0,20);
	/*current_menu = current_menu->children;
	current_menu = current_menu->sibling;
	current_menu = current_menu->sibling;
	current_menu = current_menu->sibling;
	current_menu = current_menu->sibling;
	
	//current_menu = current_menu->sibling;
	fprintf(OLED_p, current_menu->name, 0);
	/*current_menu = current_menu->children;
	OLED_home();
	fprintf(OLED_p, current_menu->name, 0);*/

	//return current_menu;
}

void print_menu(t_menu* menu){
	OLED_home();
	displayed_lines = 0;

	fprintf(OLED_p, menu->name, 0);
	int line = 1;
	menu = menu->children;
	
	while(menu && line < 5){
		displayed_lines++;
		OLED_pos(line,20);
		fprintf(OLED_p, menu->name,0);
		fprintf(UART_p, menu->name,0);
		line++;
		menu = menu->sibling;
	}
}

void menu_init(){
	OLED_clear_all();
	menu_system();
}

/*void cursor_move() {			//To manage the arrow in the current screen
	OLED_pos(pointerUP, 5);		//Pointer located on left side (column 5) of current option
	OLED_print_arrow(pointerUP, 5);	//Arrow printed

	if (ADC_read(JOY_DU) >= 250) {		//If joystick is moved UP
		OLED_clear_arrow(pointerUP, 5);	//Current arrow removed
		pointerUP--;					//Pointer updated
		if (pointerUP < 1) {
			pointerUP = menu_length-1;	//To ensure a cyclical pointer
		}
	}
	else if (ADC_read(JOY_DU) <= 5) {	//If joystick is moved DOWN
		OLED_clear_arrow(pointerUP, 5);
		pointerUP++;
		if (pointerUP > menu_length-1) {
			pointerUP = 1;
		}
	}
	else if (ADC_read(JOY_LR) >= 250) {	//If joystick is moved RIGHT
		if (pointerLR == 0) {			//Only if I am in a parent screen
			OLED_clear_all();			//All screen is cleared
			pointerLR = pointerUP;		//Arrow position determines sub-menu screen
			pointerUP = 1;				//Arrow placed in the first line again
			///////////////////////
			///THIS WAS ADDED
			/*if (current_menu->head == NULL){
				print_menu(current_menu);
			}
			else{
				current_menu = current_menu->head;
				
				for (int i; i < pointerUP; i++) {
					current_menu = current_menu->children;
					
				}
				print_menu(current_menu);
			}*/
			//////////////////////
	/*	}
	}
	else if (ADC_read(JOY_LR) <= 5) {	//If joystick is moved LEFT
		if (pointerLR != 0) {			//Only if I am in a child screen
			OLED_clear_all();
			pointerLR = 0;				//Go back to the parent screen
			pointerUP = 1;				//Arrow placed in the first line again
			///////////////////////////
			/*if (current_menu->parent == NULL){
				print_menu(current_menu);
			}
			
			else{
				current_menu = current_menu->parent;
				print_menu(current_menu);
			}*/
			//////////////////////

	/*	}
	}

	_delay_ms(500);
	
	fprintf(UART_p, "pointerUP: %4d     ", pointerUP);
	fprintf(UART_p, "pointerLR: %4d \n\r", pointerLR);
}*/


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