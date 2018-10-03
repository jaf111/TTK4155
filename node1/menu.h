#ifndef MENU_H
#define MENU_H


menu* create_menu(char name, int8_t num_sub);
menu* insert_menu(menu* main, char* name, int menu_col, int8_t num_sub, void (*menu_list)());



void print_sub_menu(uint8_t menNum);
void cursor_move();

#endif //menu.H