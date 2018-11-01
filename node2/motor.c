#define F_CPU 16000000	//Clock Speed (Oscillator)

#include <avr/io.h>
#include <util/delay.h>

#include "motor.h"

typedef enum motor_direction { 
    IDLE = -1,
    LEFT = 0,    
    RIGHT = 1
} motor_dir_t;

motor_dir_t dir = IDLE; 


void motor_init(){
	DDRH |= (1 << PH4); ///Enable EN pin
	PORTH |= (1 << PINH4);	//Set EN pin high to enable motor

	DDRH |= (1 << PH1); ///Enable DIR pin (direction) 


	DDRH |= (1 << PH5); //Set !OE low to enable output of encoder
	DDRH |= (1 << PH3); //Set SEL low to get high byte
	_delay_ms(20) //Wait about 20 microseconds


}




void reset_encoder(){
	PORTH &= ~(0 << PINH4);	//Clear RST pin
	_delay_ms(20) 
	PORTH |= (1 << PINH4);	//Set RST pin to high
}


int16_t read_encoder(){
Normal procedure of reading the encoder:
• Set !OE low to enable output of encoder //done in init
• Set SEL low to get high byte //done in init
• Wait about 20 microseconds //done in init
• Read MSB
• Set SEL high to get low byte
• Wait about 20 microseconds
• Read LSB
• Toggle !RST to reset encoder
• Set !OE high to disable output of encoder
• Process received data....

	int16_t encoder_pos = 
	return encoder_pos;
}




void set_motor_direction(){
	switch(dir){
		case LEFT:
			PORTH |= (0 << PH1); //Set direction left  
			break;
		
		case RIGHT:
			PORTH |= (1 << PH1); //Set direction right 
			break;
	}
}

void motor_move(int16_t encoder_pos, int16_t speed){
	if(encoder_pos > 100){
		dir = LEFT;
		set_motor_direction();
		set_motor_speed(speed);
	}
	else{
		dir = RIGHT;
		set_motor_direction();
		set_motor_speed(speed);
	}
	//dir = IDLE;
}

void set_motor_speed(int16_t speed){

}





