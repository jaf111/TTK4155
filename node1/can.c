#include <util/delay.h>
#include <avr/io.h> 
#include <stdio.h> 

#include "spi.h"
#include "can.h"
#include "MCP2515.h"


#define LOOPBACK 0b01000000 

typedef struct can_message{
	unsigned int id;
	uint8_t length;	
	uint8_t data[8];
}packet;



void CAN_init(){
	MCP2515_init();
	MCP2515_bit_modify(MCP_CANCTRL, 0b11100000, LOOPBACK);	// Enable loopback mode

}


void CAN_send(packet* message){
	for (uint8_t i = 0; i< message->length; i++){
		;
	}

}

/*
Initialization of the CAN controller. Use the loop-back mode for now.
 Send a message with a given ID and data (for instance, by passing a struct containing
the ID, length and data to a send function)
 Receive a message.

*/

