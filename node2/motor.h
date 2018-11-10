#ifndef MOTOR_H
#define MOTOR_H
#include "buttons.h"	// needs this in order to take in direction from joystick (direction_t)

typedef enum motor_direction { 
	IDLE,
    RIGHT,
    LEFT
} motor_dir_t;

void motor_init(void);
void motor_reset_encoder(void);
int16_t motor_read_encoder(void);
void motor_set_direction(joy_direction_t direction);
void motor_move(int16_t speed);
void motor_set_speed(uint8_t speed);

#endif // MOTOR_H
