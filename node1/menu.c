#include <stdio.h>
#include <avr/io.h>
#include "menu.h"
#include "uart.h"
#include "oled.h"
#include "buttons.h"
#include "adc.h"

#define menu_col_max 6

uint8_t pointerUP = 1;
uint8_t pointerLR = 0;


typedef struct menu{
	char name[];
	struct menu* parent;
	struct menu* children;
	int8_t num_sub;
	void *(*menu_list)();

} menu;


menu* create_menu(char name, int8_t num_sub){
	menu* new_menu = malloc(sizeof(new_menu));
	new_menu->name = name;
	new_menu->num_sub = num_sub;
	new_menu->parent = NULL;
	new_menu->children = NULL;
	new_menu->menu_list = NULL;

	return new_menu;
}

menu* insert_menu(menu* main, char* name, int menu_col, int8_t num_sub, void (*menu_list)()){
	main = malloc(sizeof(main));
	main->num_sub += num_sub;   
	main->children[menu_col].name = name;
	main->children[menu_col].parent = main;
	main->children[menu_col].menu_list = (void*) menu_list;

	return main->children;
	
}


char* menu_matrix[15][menu_col_max] = {
	{"MENU 1", "    sub1_opt1", "sub1_opt2", "sub2_opt3", "", ""},
	{"SUB1 OPT1", "a", "b", "c", "", ""},
	{"SUB1 OPT2", "a", "b", "c", "d", ""},
	{"SUB1 OPT3", "a", "b", "c", "d", "e"},
	{"MENU 2", "sub2_opt1", "sub2_opt2", "sub2_opt3", "sub2_opt4", "sub2_opt5"},
	{"SUB2 OPT1", "a", "b", "c", "", ""},
	{"SUB2 OPT2", "a", "b", "c", "d", ""},
	{"SUB2 OPT3", "a", "b", "c", "d", "e"},
	{"SUB2 OPT4", "a", "b", "c", "", ""},
	{"SUB2 OPT5", "a", "b", "c", "d", "e"},
	{"MENU 3", "sub3_opt1", "sub3_opt2", "sub3_opt3", "sub3_opt4", ""},
	{"SUB3 OPT1", "a", "b", "c", "d", ""},
	{"SUB3 OPT2", "a", "b", "", "", ""},
	{"SUB3 OPT3", "a", "b", "c", "d", "e"},
	{"SUB3 OPT4", "a", "b", "c", "", ""}
};

//menu_sys[3][menu_col_max = {"", "print_highscore"}

void menu_init(){
	/*node * head = NULL

	head = malloc(sizeof(node));

	head->name = "Main Menu";
	head->parent = NULL;*/
	

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

	if (ADC_read(JOY_DU) >= 250) {		//UP
		OLED_clear_arrow(pointerUP, 5);
		pointerUP--;
		if (pointerUP < 1) {pointerUP = menu_length-1;}
	}
	else if (ADC_read(JOY_DU) <= 5) {	//DOWN
		OLED_clear_arrow(pointerUP, 5);
		pointerUP++;
		if (pointerUP > menu_length-1) {pointerUP = 1;}
	}
	else if (ADC_read(JOY_LR) >= 250) {	//RIGHT
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

//void print_highscore();



