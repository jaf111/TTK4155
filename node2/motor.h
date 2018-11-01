#ifndef MOTOR_H
#define MOTOR_H


void motor_init(void);
void reset_encoder(void);
int16_t read_encoder(void);
void set_motor_direction(void);
void motor_move(int16_t encoder_pos, int16_t speed);
void set_motor_speed(int16_t speed);

#endif // MOTOR_H
