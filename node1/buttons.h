#ifndef BUTTONS_H
#define BUTTONS_H

#define JOY_LR 0x04		//ADC channel 1, where Left-Right Joystick is connected to
#define JOY_DU 0x05		//ADC channel 2, where Down-Up Joystick is connected to
#define SLIDER_R 0x06	//ADC channel 3, where Right Slider is connected to
#define SLIDER_L 0x07	//ADC channel 4, where Right Slider is connected to
#define BUTTON_R PINB & (1<<PB0)	//If button Right is pushed (connected to pin PB0, PORTB)
#define BUTTON_L PINB & (1<<PB1)	//If button Left is pushed (connected to pin PB0, PORTB)


typedef struct {	//Definition of variable "position_t"
	uint8_t XX;
	uint8_t YY;
	uint8_t XX_init;
	uint8_t YY_init;
} joy_position_t;

typedef struct {
	uint8_t left;
	uint8_t right;
} slider_position_t;

typedef enum JoyDir{JOY_LEFT, JOY_RIGHT, JOY_UP, JOY_DOWN, JOY_NEUTRAL} joy_direction_t;	//Enum with all joystick directions

void buttons_init(void);		//Using Port B, pin PB0 & PB1 on ATmega162

//Get function to transform and return the current joystick coordinates
void buttons_update_joy_coord();

joy_position_t buttons_get_joy_coord();

//Get function to calculate and return the current joystick direction
joy_direction_t buttons_get_joy_direction(int16_t X_coord, int16_t Y_coord);

void buttons_update_slider_positions();

slider_position_t buttons_get_slider_positions();

void buttons_send_CAN_message();

#endif // BUTTON_H