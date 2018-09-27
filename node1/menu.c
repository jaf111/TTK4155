#include <avr/io.h>
#include"menu.h"

void menu_init(){
	node * head = NULL

	head = malloc(sizeof(node));

	head->name = "Main Menu";
	head->parent = NULL;
	
}