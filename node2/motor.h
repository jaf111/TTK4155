#ifndef MOTOR_H
#define MOTOR_H
#include "buttons.h"	// needs this in order to take in direction from joystick (direction_t)

typedef enum motor_direction { 
	IDLE,
    RIGHT,
    LEFT
} motor_dir_t;

/****************************************************************************
Motor initialization
****************************************************************************/
void motor_init(void);

/****************************************************************************
Encoder calibration ("absolute" calibration)
****************************************************************************/
void motor_calibr_encoder(void);

/****************************************************************************
Encoder position reset
****************************************************************************/
void motor_reset_encoder(void);

/****************************************************************************
Read the current position from encoder
****************************************************************************/
int16_t motor_read_encoder(void);

/****************************************************************************
Get the maximum encoder position (needs calibration)
****************************************************************************/
uint16_t motor_get_encoder_max();

/****************************************************************************
Defines the direction of the motor
****************************************************************************/
void motor_set_direction(joy_direction_t direction);

/****************************************************************************
Moves the motor at fixed speed
****************************************************************************/
void motor_move(int16_t speed);

/****************************************************************************
Fixes the motor speed (sent through TWI)
****************************************************************************/
void motor_set_speed(uint8_t speed);

#endif // MOTOR_H
