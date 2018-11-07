#ifndef OLED_H
#define OLED_H

#include <stdio.h>

typedef enum tools{CIRCLE, RECTANGLE, BRUSH} tools_t;	//Types of paint tools

void write_c(uint8_t cmd);		//To write a (configuration) command into the OLED
void write_d(uint8_t cmd);		//To print data into the OLED
void write_s(uint8_t data);
void OLED_update();
void OLED_frame_fill(uint8_t data);

void OLED_init(void);			//OLED display initialization

void OLED_print_char(char c);	//To print JUST one character
void OLED_print_all(char* word);//To print the whole word/sentence (pointer where char starts)

void OLED_home(void);			//It goes to position 0,0 in OLED

void OLED_goto_line(uint8_t page);		//To go to a specific line in OLED
void OLED_goto_column(uint8_t column);	//To go to a specific column in OLED
void OLED_pos(uint8_t page, uint8_t column);	//Go to requested position

void OLED_clear_line(uint8_t line);	//Clears an entire line/page
void OLED_clear_all(void);			//Clears the whole OLED

void OLED_set_brightness(uint8_t lvl);	//Define brightness level

void OLED_print_arrow(uint8_t row, uint8_t col); //Print an arrow in requested position
void OLED_clear_arrow(uint8_t row, uint8_t col); //Clear an arrow in requested position

void OLED_screen_Saver();	//Prints a complete screen saver

void OLED_draw_pixel(uint8_t bit, uint8_t x, uint8_t y);
void OLED_draw_rectangle(uint8_t x0, uint8_t xe, uint8_t y0, uint8_t ye);
void OLED_draw_circle(uint8_t bit, uint8_t x0, uint8_t y0, uint8_t r);

void OLED_paint();

void OLED_cursor();


//It opens a file to read/write. Necessary to use printf() (and similar functions) with the OLED.
//Otherwise one should write manually to OLED
static FILE oled_out = FDEV_SETUP_STREAM (OLED_print_char, NULL, _FDEV_SETUP_WRITE);
#define OLED_p (&oled_out)

#endif //OLED_H