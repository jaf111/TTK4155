#ifndef SERVO_H
#define SERVO_H

void servo_init(void);	//Servo initialization (connected in PB5)
void move_servo(uint8_t width);	//Change Servo direction
	
#endif // SERVO_H