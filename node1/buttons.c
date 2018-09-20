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


enum JoyDir{NEUTRAL, RIGHT, UP, LEFT, DOWN} direction; 

position coord = {0, 0};


int16_t JoyCoord_init(int16_t XY){
	return XY;
}


position getJoyCoord(int16_t X_coord, int16_t Y_coord, int16_t JoyX_init, int16_t JoyY_init) {	
	X_coord -= JoyX_init;
	Y_coord -= JoyY_init;
	coord.XX = (X_coord*100/JoyX_init);
	coord.YY = (Y_coord*100/JoyY_init);

	printf("LEFT/RIGHT SIDE: %4d     ", coord.XX);
	printf("DOWN/UP SIDE: %4d     \n\r", coord.YY);

	return coord;
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


void sliders(/*int16_t SLIDER_R, int16_t SLIDER_L*/){
	printf("Slider LEFT: %4d  ", ADC_read(SLIDER_L));
	printf("Slider RIGHT: %4d \n\n\r ", ADC_read(SLIDER_R));

}