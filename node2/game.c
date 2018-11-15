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
#include "PWM.h"

uint8_t time_score = 0;
int bool_game_play = 1;
//uint8_t shoot = 0;
joy_position_t joy_recieved_coords;
slider_position_t sliders_recieved;

packet send_score = {.id = CAN_SCORE_ID, .length = 0x01, .data = {0x00}};


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

	PWM_PL3_init(256, 1);	// Generate interrupt once every second in order to count score (time)

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
	bool_game_play = 1;
	while(bool_game_play){
		fprintf(UART_p,"   Playing\r\n",0);
		packet CAN_recieved = CAN_read();

		//fprintf(UART_p,"ID: %X 	Data: %d\r\n", CAN_recieved.id, CAN_recieved.data[2]);

		if (CAN_recieved.id == CAN_INPUT_ID){							// Update coordinates if USB input is sent
			joy_recieved_coords.XX = CAN_recieved.data[0];
			joy_recieved_coords.YY = CAN_recieved.data[1];
			sliders_recieved.left = CAN_recieved.data[2];
		}

		Move_Servo(joy_recieved_coords.XX);	

		//motor_move(pid_controller(joy_recieved_coords.XX, motor_get_encoder_max()));

		if(CAN_recieved.id == CAN_SHOOT_ID){
			solenoid_push();
			//shoot = 0;
		}

		if (game_over() || (CAN_recieved.id == CAN_END_GAME_ID)){		// End game if node 1 sends message telling node 2 to stop
			send_score.data[0] = 6;  //time_score;
			fprintf(UART_p, "Score sent!",0);
			CAN_send(&send_score);
			bool_game_play = 0;
		}
	}
}