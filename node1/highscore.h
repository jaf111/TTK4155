#ifndef HIGHSCORE_H
#define HIGHSCORE_H

typedef struct {
	char* name;
	uint8_t* score;
	struct highscore_t* next;
} highscore_t;

void highscore_init(void);
void print_highscore(void);
void create_name(void);
char letter_select(void);

void insert_score(char* name, uint8_t score);
void highscore_copy(int place);
void check_score(uint8_t score);


#endif //HIGHSCORE_H