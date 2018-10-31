#ifndef SERVO_H
#define SERVO_H

void Servo_init(void);	//Servo initialization (connected in PB5)
void Move_Servo(uint8_t width);	//Change Servo direction
	
#endif // SERVO_H