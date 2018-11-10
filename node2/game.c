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

uint8_t time_score;
uint8_t game_over = 0;
uint8_t setpoint;
int16_t motor_pos;
int bool_game_play; 

ISR(TIMER2_OVF_vect){
	time_score++;		// Increment time score by a second
}

void game_init(){
	time_score = 0;
	Servo_init();
	motor_init();
	solenoid_init();
	pid_init(2, 50);	//Type 2 (PI) and frequency of 1000Hz


	/* //Timer2 Settings: Timer Prescaler /64,
 	TCCR2 |= (1<<CS22);    // turn on CS22 bit
 	TCCR2 &= ~((1<<CS21) | (1<<CS20));    // turn off CS21 and CS20 bits
 // Use normal mode
 	TCCR2 &= ~((1<<WGM21) | (1<<WGM20));   // turn off WGM21 and WGM20 bits
 	TCNT1 = 
 	TIMSK = (1 << TOIE1);
	*/

	// Calibrate motor position etc . . . . . .

}

int game_over(){
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
		}
		
		packet can_joystick = CAN_read();
		Move_Servo(can_joystick.data[0]);	
		motor_pos = motor_read_encoder();
		direction_t joy_dir = getJoyDirection(can_joystick.data[0], can_joystick.data[1]);
		setpoint = can_joystick.data[0];
		motor_move(pid_controller(setpoint));
		solenoid_push();

	}


}