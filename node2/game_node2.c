#include <stdio.h>		
#include <avr/io.h> 	
#include <avr/interrupt.h>

#include "uart.h"		
#include "buttons.h"	
#include "IR.h"	
#include "can.h"		
#include "servo.h"		
#include "motor.h"	
#include "solenoid.h"
#include "PWM.h"
#include "pid.h"
#include "game_node2.h"

uint8_t time_score = 0;
int bool_game_play = 1;
int16_t motor_pos = 0;
uint8_t setpoint = 0;

//uint8_t shoot = 0;
joy_position_t joy_recieved_coords;
slider_position_t sliders_recieved;
buttons_value_t buttons_recieved;

packet send_score = {.id = CAN_SCORE_ID, .length = 0x01, .data = {0x00}};
packet CAN_recieved;

pidData_t pidData2;

ISR(TIMER5_COMPA_vect){
	time_score++;		// Increment time score once every seond
}

void game_node2_init() {
	time_score = 0;
	/*Servo_init();
	motor_init();
	solenoid_init();*/

	pid_Init(&pidData2, 500);//PID controller with frequency of 20Hz
	motor_calibr_encoder();
	
	PWM_PL3_init(256, 1);	//Interrupt of 1Hz (1s) to count the score time
}

uint8_t game_node2_over() {
	if (IR_triggered()) {
		fprintf(UART_p, "IR %4d \r\n", IR_triggered);
		return 1;
	}
	return 0;
}

void game_node2_play() {
	game_node2_init();
	bool_game_play = 1;
	while(bool_game_play){
		CAN_recieved = CAN_read();

		//fprintf(UART_p,"ID: %X 	Data: %d\r\n", CAN_recieved.id, CAN_recieved.data[2]);

		if (CAN_recieved.id == CAN_INPUT_ID) {				// Update coordinates if USB input is sent
			joy_recieved_coords.XX = CAN_recieved.data[0];
			joy_recieved_coords.YY = CAN_recieved.data[1];
			sliders_recieved.left = CAN_recieved.data[2];
			sliders_recieved.right = CAN_recieved.data[3];
			buttons_recieved.left = CAN_recieved.data[4];
			buttons_recieved.right = CAN_recieved.data[5];
			fprintf(UART_p, "Joystick:%d \r\n", CAN_recieved.data[0]);
		}

		motor_pos = -motor_read_encoder();
		setpoint = sliders_recieved.right;
		motor_move(pid_Controller(&pidData2, setpoint, motor_pos));
		Move_Servo(joy_recieved_coords.XX);
		if(buttons_recieved.right != 0) {
			solenoid_ON();
		} 
		
		else {
			solenoid_OFF();
		}
		
		if (game_node2_over() || (CAN_recieved.id == CAN_END_GAME_ID)){		// End game if node 1 sends message telling node 2 to stop
			send_score.data[0] = time_score;  //time_score;
			CAN_send(&send_score);
			bool_game_play = 0;
		}
	}
}