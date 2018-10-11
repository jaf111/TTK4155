#ifndef MENU_H
#define MENU_H

#define menu_col_max 6	//Maxim number of lines per menu

typedef struct{
	char* name;
	struct t_menu* parent;
	struct t_menu* children;
	struct t_menu* sibling;
	//int8_t select;
} t_menu;

t_menu* menu(char* name, t_menu* parent);
void set_sibling(t_menu* menu, t_menu* new_sibling);
void set_children(t_menu* menu, t_menu* new_children);
t_menu* menu_system(void);
void print_menu(t_menu* menu);
void menu_init();	//Menu initialization

char* menu_matrix[5][menu_col_max];
void print_sub_menu(uint8_t menNum);//Print/refresh the current screen
void cursor_move();	//To manage the arrow in the current screen

#endif //menu.H