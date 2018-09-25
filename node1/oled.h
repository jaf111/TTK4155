#ifndef OLED_H
#define OLED_H


void write_c(uint8_t cmd);

void write_d(uint8_t cmd);

void OLED_init(void);

void OLED_print_char(char c);

void OLED_print(char* word);

void OLED_home(void);

void OLED_goto_line(uint8_t page);

void OLED_pos(uint8_t page, uint8_t column);

void OLED_clear_line(uint8_t line);

void OLED_clear(void);

void OLED_set_brightness(uint8_t lvl);



#endif //OLED_H