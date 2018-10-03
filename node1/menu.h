#ifndef MENU_H
#define MENU_H

#define menu_col_max 6

typedef struct menu{
	char* name;
	struct menu* parent;
	struct menu* children[4];
	int8_t select;
} menu;


//struct menu* create_menu(char name, struct menu* parent, struct menu* child1, struct menu* child2, struct menu* child3, int8_t num_sub);
//struct menu* insert_menu(struct menu* main, char* name, int menu_col, int8_t num_sub);

menu* init_menu1(menu new_menu);

char* menu_matrix[5][menu_col_max];


void print_sub_menu(uint8_t menNum);
void menu_init();
void cursor_move();

#endif //menu.H