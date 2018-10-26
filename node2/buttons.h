#ifndef BUTTONS_H
#define BUTTONS_H

typedef struct {	//Definition of variable "position", formed by 2 inte16_t
	int16_t XX;
	int16_t YY;
} position;

void button_init(void);		//Using Port B, pin PB0 & PB1 on ATmega162

int16_t JoyCoord_init(int16_t XY);	//Get standby joystick position (calibration)

//Get function to take the current joystick coordinates
position getJoyCoord(int16_t X_coord, int16_t Y_coord, int16_t JoyX_init, int16_t JoyY_init);

//Get function to take the current joystick direction
void getJoyDirection(int16_t X_coord, int16_t Y_coord);

void sliders();		//Status of both sliders analog values

#endif // BUTTON_H