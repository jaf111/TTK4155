#include <stdio.h>		
#include <avr/io.h> 	
#include <avr/interrupt.h>

#include "uart.h"		
#include "buttons.h"	
#include "IR.h"	
#include "can.h"		
#include "servo.h"		
#include "motor.h"      
#include "pid_contr.h"	
#include "solenoid.h"	

uint8_t time_score = 0;
uint8_t game_over = 0;
uint8_t setpoint;
int16_t motor_pos;
int bool_game_play;
joy_position_t joy_coords;

ISR(TIMER5_COMPA_vect){
	time_score++;		// Increment time score once every seond
}

void game_init(){
	time_score = 0;
	/*
	Servo_init();
	motor_init();
	solenoid_init();
	pid_init(2, 50);	//Type 2 (PI) and frequency of 1000Hz
	*/

	PWM_PL3_init(256, 1)	// Generate interrupt once every second in order to count score (time)

	// Calibrate motor position etc . . . . . .

}

uint8_t game_over(){
	if (IR_triggered()){
		return 1;
	}
	return 0;
} 

void game_play(){
	game_init();

	while(bool_game_play){
		if (game_over()){
			bool_game_play = 0;
			//break;
		}
		
		packet can_joystick = CAN_read();
		joy_coords.XX = can_joystick.data[0];
		joy_coords.YY = can_joystick.data[1];

		Move_Servo(joy_coords.XX);	

		motor_move(pid_controller(joy_coords.XX, motor_get_encoder_max()));

		if(BUTTON_R){
			solenoid_push();
		}
	}
	packet send_score = {.id = 0x15, .length = 0x01, .data = {0x09}};			// .data = {time_score}
	CAN_send(score);

}