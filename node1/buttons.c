#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <stdio.h> 

#include "uart.h"		//Added to use fprintf function
#include "buttons.h"	//Function prototypes

#define Mov23_Pos 190	//Joystick moved 2/3 in positive direction (up or right)
#define Mov23_Neg 64	//Joystick moved 2/3 in negative direction (down or left)

void button_init(void) {	//Using Port B, pin PB0 & PB1 on ATmega162
	DDRB |= (1 << DDB0);	//Enabled pin 0 (PB0) of port B (register DDRB)
	DDRB |= (1 << DDB1);	//Enabled pin 1 (PB1) of port B (register DDRB)
}

enum JoyDir{NEUTRAL, RIGHT, UP, LEFT, DOWN} direction;	//Enum with all joystick directions

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

	coord.slider_l_pos = ADC_read(SLIDER_L);
	coord.slider_r_pos = ADC_read(SLIDER_R);

	//fprintf(UART_p, "LEFT/RIGHT SIDE: %4d     ", coord.XX);
	//fprintf(UART_p, "DOWN/UP SIDE: %4d     \n\r", coord.YY);

	return coord;
}

uint8_t getJoyDirection(int16_t X_coord, int16_t Y_coord) {	//Current joystick direction
	if (X_coord>Mov23_Pos) {			//More than 2/3 right
		if (Y_coord>Mov23_Pos) {		//More than 2/3 up
			if (X_coord>Y_coord) {direction = RIGHT;}	//The biggest number determines final position
			else {direction = UP;}
		} else if (Y_coord<Mov23_Neg) {		//More than 2/3 down, it is considered is DOWN
			if (X_coord>2*Y_coord) {direction = RIGHT;}//Biggest number determines final position (2* corrects opposite direction)
			else {direction = DOWN;}
		} else {direction = RIGHT;}
	}
	else if (X_coord<Mov23_Neg) {
		if (Y_coord>Mov23_Pos) {
			if (2*X_coord>Y_coord) {direction = LEFT;}
			else {direction = UP;}
		} else if (Y_coord<Mov23_Neg) {
			if (X_coord>Y_coord) {direction = LEFT;}
			else {direction = DOWN;}
		} else {direction = LEFT;}
	}
	else if (Y_coord>Mov23_Pos) {
			direction = UP;
		} else if (Y_coord<Mov23_Neg) {
			direction = DOWN;
		}
	else {direction = NEUTRAL;}		//If nothing is pushed, then neutral position

	fprintf(UART_p, "DIRECTION: %d \n\r", direction);
	return direction;
}

void sliders() {		//Analog lecture of both slider positions
	fprintf(UART_p, "Slider LEFT: %4d  ", ADC_read(SLIDER_L));
	fprintf(UART_p, "Slider RIGHT: %4d \n\n\r", ADC_read(SLIDER_R));
}