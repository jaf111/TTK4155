#ifndef OLED_H
#define OLED_H

void write_c(uint8_t cmd);
void write_d(uint8_t cmd);
void write_s(uint8_t data);
void OLED_update();

void OLED_init(void);

void OLED_print_char(char c);
void OLED_print(char* word);

void OLED_home(void);

void OLED_goto_line(uint8_t page);
void OLED_goto_column(uint8_t column);

void OLED_pos(uint8_t page, uint8_t column);

void OLED_clear_line(uint8_t line);
void OLED_clear_all(void);

void OLED_set_brightness(uint8_t lvl);

void OLED_print_arrow(uint8_t row, uint8_t col);
void OLED_clear_arrow(uint8_t row, uint8_t col);

void OLED_screen_Saver();

static FILE oled_out = FDEV_SETUP_STREAM (OLED_print_char, NULL, _FDEV_SETUP_WRITE);

#define OLED_p (&oled_out)



#endif //OLED_H