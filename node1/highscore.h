#ifndef HIGHSCORE_H
#define HIGHSCORE_H

void highscore_save_sram(char* word, uint8_t score);
uint8_t highscore_check_sram(uint8_t score);
void highscore_display_sram();
char* highscore_get_player_name();

typedef struct {
	char namee[8];
	uint8_t score;
} highscore_t;

/**
  * @desc Initializing structs in the highscore driver and creating an empty
  * highscore table 
*/
void highscore_init(void);


/**
  * @desc Pretty print of the highscore table to oled 
*/
void print_highscore(void);


/**
  * @desc Creating name by selecting letters with right button and erase with left button  
  * @param highscore struct - with (NULL) name and (NULL) score
*/
void create_name();
//void create_name(highscore_t * foo);


/**
  * @desc Able to select letter with joystick. Starts on 'A'. Going down with joystick
  * you will selec 'B' then 'C' etc.  
  * @return char - representing letter
*/
char letter_select(void);


/**
  * @desc inserts score from game into struct highscore in correct position  
  * in highscore table.   
  * @param char and uint - variabels will be inserted into highscore struct
*/
void insert_score(char* name, uint8_t* score);


/**
  * @desc Moves highscores down on the highscoretable so you can insert a new highscore arbitrary
  * @param highscore structs - he message to be displayed
*/
void highscore_copy(highscore_t* highscore_current, highscore_t* highscore_next);


/**
  * @desc Checks if score to new player can be placed in highscoretable 
  * @param uint - score from game
  * @return bool - can be placed in highscoretable or not
*/
int check_score(uint8_t* score);


#endif //HIGHSCORE_H
