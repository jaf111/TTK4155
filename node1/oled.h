#ifndef OLED_H
#define OLED_H

#include "uart.c"

void write_c(uint8_t cmd);

void OLED_init();

void OLED_write_char(char A);

void OLED_write_data(char A);

void OLED_home();

void OLED_goto_line(uint8_t page);

void OLED_pos(uint8_t page, uint8_t column);

void OLED_set_brightness(uint8_t lvl);



#endif //OLED_H