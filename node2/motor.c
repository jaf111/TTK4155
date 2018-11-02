#define F_CPU 16000000	//Clock Speed (Oscillator)

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>	//Functions for busy-wait delay loops

#include "motor.h"
#include "TWI_Master.h"
#include "uart.h"
#include "buttons.h"

// Digital-analog converter address
#define DAC 0x28

// Sample TWI transmission commands
#define TWI_CMD_MASTER_WRITE 0b0
 
motor_dir_t dir = RIGHT;
uint8_t message_buffer[3];	//


void motor_init(){
	DDRH |= (1 << PH4); 	//Enable EN pin
	PORTH |= (1 << PH4);	//Set EN pin high to enable motor

	DDRH |= (1 << PH1); 	///Enable DIR pin (direction) 


	DDRH |= (1 << PH5); 	//Enable !OE to output of encoder
	DDRH |= (1 << PH3); 	//Enable SEL to output
	

}


void reset_encoder(){
	PORTH &= ~(0 << PINH4);	//Clear RST pin
	_delay_ms(20);
	PORTH |= (1 << PINH4);	//Set RST pin to high
}


int16_t read_encoder(){

//Normal procedure of reading the encoder:

   PORTH &= ~(1 << PH5);		  	// Set !OE low to enable output of encoder
   PORTH &= ~(1 << PH3);		   	// Lower SEL to get high byte
   _delay_ms(20);			  	  	// Wait about 20 microseconds
   uint8_t MSB = PINK;				// Read MSB
   PORTH |= (1 << PH3);			  	// Set SEL high to get low byte
   _delay_ms(20);			   		// Wait about 20 microseconds
   uint8_t LSB = PINK;			   	// Read LSB
   PORTH &= ~(1 << PH4);		   	// Toggle !RST to reset encoder
   PORTH |= (1 << PH5);             // Set !OE high to disable output of encoder
   int16_t encoder_pos = (MSB << 8) + LSB; //Process received data.... 

   return encoder_pos;

}

void set_motor_direction(direction_t direction){	// Take in direction from joystick and set motor direction
	switch(direction){
		case LEFT:
			PORTH &= ~(1 << PH1); //Set direction left  
			fprintf(UART_p, "LEFT\r\n", 0);
			dir = LEFT;
			break;
		
		case RIGHT:
			PORTH |= (1 << PH1); //Set direction right
			dir = RIGHT;
			break;
	}
	fprintf(UART_p, " motor dir = %d \r \n",dir);
}


void motor_move(int16_t encoder_pos, uint8_t speed){
	if(encoder_pos > 100){
		dir = LEFT;
		set_motor_direction(dir);
		set_motor_speed(speed);
	}
	else{
		dir = RIGHT;
		set_motor_direction(dir);
		set_motor_speed(speed);
	}
	//dir = IDLE;
}


void set_motor_speed(uint8_t speed){
	uint8_t adr = 0x50;
	uint8_t cmd = 0x00;
	message_buffer[0] = adr;	// First call consists of TWI slave address
	message_buffer[1] = cmd;		// First byte is write command
	message_buffer[2] = speed;						// Send desired motor speed to DAC
	_delay_ms(50);
	TWI_Start_Transceiver_With_Data(message_buffer, 3);	// start transmission
}

