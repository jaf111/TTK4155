#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include "menu.h"
#include "uart.h"
#include "oled.h"
#include "buttons.h"
#include "adc.h"

uint8_t pointerUP = 1;
uint8_t pointerLR = 0;


menu main_menu, game, scores, hacking, options;

/*struct menu* create_menu(char name, struct menu* parent, struct menu* child1, struct menu* child2, struct menu* child3, int8_t num_sub){
	//menu* new_menu = malloc(sizeof(new_menu));
	new_menu.name = name;
	new_menu.parent = &parent;
	new_menu.children[0] = child1;
	new_menu.children[1] = child2;
	new_menu.children[2] = child3;
	new_menu.children[3] = NULL;
	new_menu.num_sub = num_sub;
	
	return new_menu;
}*/

/*menu* init_menu1(menu* new_menu){
	new_menu->name = "Main menu";
	new_menu->parent = NULL;
	new_menu->children[0] = &game;
	new_menu->children[1] = NULL;
	new_menu->children[2] = NULL;
	new_menu->num_sub = 0;

	fprintf(OLED_p, "%d\n", (new_menu->num_sub));

}*/

menu* init_menu1(menu new_menu){
	new_menu.name = "Main menu";
	new_menu.parent = NULL;
	new_menu.children[0] = &game;
	new_menu.children[1] = NULL;
	new_menu.children[2] = &hacking;
	new_menu.children[3] = NULL;
	new_menu.select = 0;

	//fprintf(OLED_p, "%d", (new_menu.select));
}

/*struct menu* insert_menu(struct menu* main, char* name, int menu_col, int8_t num_sub){
	main = malloc(sizeof(main));
	main->num_sub += num_sub;   
	main->children[menu_col].name = name;
	main->children[menu_col].parent = main;
	
	return main->children;
	
}*/

char* menu_matrix[5][menu_col_max] = {
	{"---Main Menu---", "Game", "Scores", "Hacking", "Options", ""},
	{"Game", "a", "b", "c", "", ""},
	{"Scores", "a", "b", "c", "d", ""},
	{"Hacking", "Screensaver", "b", "c", "d", "e"},
	{"Options", "Change font", "Brightness", "sub2_opt3", "sub2_opt4", "sub2_opt5"},
};


void menu_init(){
	OLED_clear_all();
}



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

void cursor_move() {
	OLED_pos(pointerUP, 5);
	OLED_print_arrow(pointerUP, 5);

	if (ADC_read(JOY_DU) >= 255) {		//UP
		OLED_clear_arrow(pointerUP, 5);
		pointerUP--;
		if (pointerUP < 1) {pointerUP = menu_length-1;}
	}
	else if (ADC_read(JOY_DU) <= 5) {	//DOWN
		OLED_clear_arrow(pointerUP, 5);
		pointerUP++;
		if (pointerUP > menu_length-1) {pointerUP = 1;}
	}
	else if (ADC_read(JOY_LR) >= 255) {	//RIGHT
		if (pointerLR == 0) {
			OLED_clear_all();
			pointerLR = pointerUP;
			pointerUP = 1;
		}
	}
	else if (ADC_read(JOY_LR) <= 5) {	//LEFT
		if (pointerLR != 0) {
			OLED_clear_all();
			pointerLR = 0;
			pointerUP = 1;
		}
	}
	_delay_ms(1000);
	
	fprintf(UART_p, "pointerUP: %4d     ", pointerUP);
	fprintf(UART_p, "pointerLR: %4d \n\r", pointerLR);
}





