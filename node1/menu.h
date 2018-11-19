#ifndef MENU_H
#define MENU_H

#define menu_col_max 6	//Maxim number of lines per menu

#define main_menu_id	0x00		// Menus have IDs in order to retrieve their names from PROGMEM
#define game_id			0x01		// See menu_names.h in order to see what is stored in PROGMEM for menu.c
#define highscore_id	0x02
#define extras_id		0x03
#define options_id		0x04
#define screensaver_id	0x05
#define songs_id		0x06
#define paint_id		0x07
#define brightness_id	0x08
#define low_id			0x09
#define high_id 		0x0A

typedef struct{
	uint8_t menu_id;
	struct t_menu* parent;
	struct t_menu* children;
	struct t_menu* sibling;
} t_menu;

t_menu* menu(char* name, t_menu* parent);
void set_sibling(t_menu* menu, t_menu* new_sibling);
void set_children(t_menu* menu, t_menu* new_children);
void menu_system();
void print_menu(t_menu* menu);
void menu_init();	//Menu initialization
void cursor_move();	//To manage the arrow in the current screen
void menu_handler(void);

//-----------------------------------------------------------------

char* menu_matrix[5][menu_col_max];
void print_sub_menu(uint8_t menNum);//Print/refresh the current screen


#endif //menu.H