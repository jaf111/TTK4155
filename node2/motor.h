#ifndef MOTOR_H
#define MOTOR_H
#include "buttons.h"

typedef enum motor_direction { 
	LEFT,
    RIGHT,
    IDLE
} motor_dir_t;

void motor_init(void);
void reset_encoder(void);
int16_t read_encoder(void);
void set_motor_direction(direction_t direction);
void motor_move(int16_t encoder_pos, uint8_t speed);
void set_motor_speed(uint8_t speed);

#endif // MOTOR_H
