#ifndef MENU_H
#define MENU_H

#define menu_col_max 6

typedef struct{
	char* name;
	struct t_menu* parent;
	struct t_menu* head;
	struct t_menu* children;
	//int8_t select;
} t_menu;


t_menu* menu(char* name, t_menu* parent);
void init_head(t_menu* menu, t_menu* children);
void set_children(t_menu* menu, t_menu* children);
t_menu* menu_system(void);
void print_menu(t_menu* menu);
void menu_init();

char* menu_matrix[5][menu_col_max];
void print_sub_menu(uint8_t menNum);
void cursor_move();

#endif //menu.H