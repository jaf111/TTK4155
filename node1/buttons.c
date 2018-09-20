#include <avr/io.h>
#include "buttons.h"

#define JOY_LR 0x04
#define JOY_DU 0x05
#define SLIDER_R 0x06
#define SLIDER_L 0x07


//Using Port B, pin PB0 & PB1 on ATmega162
void button_init(void){
	DDRB |= (1 << DDB0);
	DDRB |= (1 << DDB1);

}


typedef struct {
	int16_t XX;
	int16_t YY;
} position;

enum JoyDir{NEUTRAL, RIGHT, UP, LEFT, DOWN} direction; 

position coord = {0, 0};


int16_t JoyCoord_init(int16_t X_coord, int16_t Y_coord){
	return X_coord, Y_coord;
}


void getJoyCoord(int16_t X_coord, int16_t Y_coord) {
	if (X_coord < 127) {X_coord -= 127;}
	else {X_coord /= 2;}
	if (Y_coord < 127) {Y_coord -= 127;}
	else {Y_coord /= 2;}

	coord.XX = X_coord*100/127;
	coord.YY = Y_coord*100/127;

	printf("LEFT/RIGHT SIDE: %4d     ", coord.XX);
	printf("DOWN/UP SIDE: %4d     \n\r", coord.YY);
}


void getJoyCoord2(int16_t X_coord, int16_t Y_coord, int16_t JoyX_init, JoyY_init) {



	coord.XX = X_coord*100/128 -100;
	coord.YY = Y_coord*100/128 -100;

	if (Y_coord == 255){
		coord.YY = 100;
	}

	if (X_coord == 255){
		coord.XX = 100;	
	}
	//if (X_coord < 127) {coord.XX = -coord.XX;}
	//else {X_coord /= 2;}
	//if (Y_coord < 127) {coord.YY = -coord.YY;}
	//else {Y_coord /= 2;}


	printf("LEFT/RIGHT SIDE: %4d     ", coord.XX);
	printf("DOWN/UP SIDE: %4d     \n\r", coord.YY);
}





void getJoyDirection(int16_t X_coord, int16_t Y_coord) {

	if (X_coord>190) {
		if (Y_coord>190) {
			if (X_coord>Y_coord) {direction = RIGHT;}
			else {direction = UP;}
		} else if (Y_coord<64) {
			if (X_coord>2*Y_coord) {direction = RIGHT;}
			else {direction = DOWN;}
		} else {direction = RIGHT;}
	}
	else if (X_coord<64) {
		if (Y_coord>190) {
			if (2*X_coord>Y_coord) {direction = LEFT;}
			else {direction = UP;}
		} else if (Y_coord<64) {
			if (X_coord>Y_coord) {direction = LEFT;}
			else {direction = DOWN;}
		} else {direction = LEFT;}
	}
	else if (Y_coord>190) {
			direction = UP;
		} else if (Y_coord<64) {
			direction = DOWN;
		}
	else {direction = NEUTRAL;}

	//printf("LEFT/RIGHT SIDE: %4d     ", X_coord);
	//printf("DOWN/UP SIDE: %4d     ", Y_coord);
	printf("DIRECTION: %d \n\r", direction);
}
