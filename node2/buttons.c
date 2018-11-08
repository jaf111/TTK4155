#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <stdio.h> 

#include "uart.h"		//Added to use fprintf function
#include "buttons.h"	//Function prototypes here defined

#define Mov23_Pos 190	//Joystick moved 2/3 in positive direction (up or right)
#define Mov23_Neg 64	//Joystick moved 2/3 in negative direction (down or left)

void button_init(void) {	//Using Port B, pin PB0 & PB1 on ATmega162
	DDRB |= (1 << DDB0);	//Enabled pin 0 (PB0) of port B (register DDRB)
	DDRB |= (1 << DDB1);	//Enabled pin 1 (PB1) of port B (register DDRB)
}

direction_t direction = JOY_NEUTRAL;

int16_t JoyCoord_init(int16_t XY) {		//Get standby joystick position (calibration)
	return XY;
}

position getJoyCoord(int16_t X_coord, int16_t Y_coord, int16_t JoyX_init, int16_t JoyY_init) {	
	position coord = {0, 0, 0, 0}; 	//Initialization of variable of type "position"

	/*X_coord -= JoyX_init;	//The current center point (offset) is subtracted for calibration
	Y_coord -= JoyY_init;
	coord.XX = X_coord*100/JoyX_init;		//Coordinates transformed into -100% to 100%
	coord.YY = Y_coord*100/JoyY_init;*/

	//Joystick is not complete centered in idle position, so not possible to fit -100%, 0%, 100% in just one operation
	if ((X_coord <= JoyX_init+2) && (X_coord >= JoyX_init-2)) {
		coord.XX = 0;
	} else {
		X_coord -= 127;
		coord.XX = X_coord*100/127;
	}
	if ((Y_coord <= JoyY_init+2) && (Y_coord >= JoyY_init-2)) {
		coord.YY = 0;
	} else {
		Y_coord -= 127;
		coord.YY = Y_coord*100/127;
	}

	//coord.slider_l_pos = ADC_read(SLIDER_L);
	//coord.slider_r_pos = ADC_read(SLIDER_R);

	return coord;
}

direction_t getJoyDirection(int16_t X_coord, int16_t Y_coord) {	//Current joystick direction
	if (X_coord>Mov23_Pos) {			//More than 2/3 right
		if (Y_coord>Mov23_Pos) {		//More than 2/3 up
			if (X_coord>Y_coord) {direction = JOY_RIGHT;}	//The biggest number determines final position
			else {direction = JOY_UP;}
		} else if (Y_coord<Mov23_Neg) {		//More than 2/3 down, it is considered is DOWN
			if (X_coord>2*Y_coord) {direction = JOY_RIGHT;}//Biggest number determines final position (2* corrects opposite direction)
			else {direction = JOY_DOWN;}
		} else {direction = JOY_RIGHT;}
	}
	else if (X_coord<Mov23_Neg) {
		if (Y_coord>Mov23_Pos) {
			if (2*X_coord>Y_coord) {direction = JOY_LEFT;}
			else {direction = JOY_UP;}
		} else if (Y_coord<Mov23_Neg) {
			if (X_coord>Y_coord) {direction = JOY_LEFT;}
			else {direction = JOY_DOWN;}
		} else {direction = JOY_LEFT;}
	}
	else if (Y_coord>Mov23_Pos) {
			direction = JOY_UP;
		} else if (Y_coord<Mov23_Neg) {
			direction = JOY_DOWN;
		}
	else {direction = JOY_NEUTRAL;}		//If nothing is pushed, then neutral position

	return direction;
}
