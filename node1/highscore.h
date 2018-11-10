#ifndef HIGHSCORE_H
#define HIGHSCORE_H

typedef struct {
	char name[8];
	uint8_t score;
} highscore;

void print_highscore(void);
void create_name();
char display_letter(char_selector);


#endif //HIGHSCORE_H