/*#include <util/delay.h>
#include <avr/io.h> 
#include <stdio.h> 

#include "uart.h"		//Added to use fprintf function
#include "spi.h"
#include "can.h"
#include "MCP2515.h"


void CAN_init() {
	MCP2515_init();
	
	//2nd element (mask) defines which numbers are allowed to change
	MCP2515_bit_modify(MCP_CANCTRL, 0b11100000, MODE_LOOPBACK);	//Set in loopback mode
	MCP2515_bit_modify(MCP_CANINTE, 0b00000001, 0xFF);	//Enabling receive buffer interrupt
	MCP2515_bit_modify(MCP_RXB0CTRL, 0b01100000, 0xFF);	//Disables all filters (security)
}

void CAN_send(packet* message) {	//Everything is done only through Buffer 0
	if (CAN_error()) {	//If there is an error in the transmission
		fprintf(UART_p, "ERRORRRRRRRRRR %4x \r\n", MCP2515_read(MCP_TXB0CTRL));
	}

	while (MCP_TXB0CTRL & (1<<TXREQ));	//Waits until last transmission finishes

	//Standard ID is saved in 2 registers: 5 MSB in TXB0SIDH and 3 LSB in TXB0SIDL
	MCP2515_bit_modify(MCP_TXB0SIDH, 0xFF, message->id>>3);	//-> to access one particular element of the struct
	MCP2515_bit_modify(MCP_TXB0SIDL, 0xE0, message->id<<5);	//Only bits defined in 2nd parameter can be changed
	MCP2515_bit_modify(MCP_TXB0DLC, 0x0F, message->length);
	//fprintf(UART_p, "SENDER ID: %4x \r\n", message->id);
	
	for (uint8_t i=0; i<message->length; i++) {
		MCP2515_bit_modify(MCP_TXB0D0 + i, 0xFF, message->data[i]);
		//fprintf(UART_p, "MCP_TXB0D %4x: %4x \r\n", i, MCP2515_read(MCP_TXB0D0+i));
	}
	MCP2515_request_to_send(MCP_RTS_TX0);
}

packet CAN_read() {
	packet message;
	message.id = ((MCP2515_read(MCP_RXB0SIDH)<<3) + (MCP2515_read(MCP_RXB0SIDL)>>5)); // Store message id
	message.length = 0x0F & (MCP2515_read(MCP_RXB0DLC)); // Length of the last received message is checked
	//fprintf(UART_p, "RECEIVE ID: %4x \r\n", message.id);
	
	for (uint8_t i=0; i<message.length; i++) {
		message.data[i]= MCP2515_read(MCP_RXB0D0+i); //Store message data
		//fprintf(UART_p, "MCP_RXB0D %4x: %4x \r\n", i, MCP2515_read(MCP_RXB0D0+i));
	}
	MCP2515_bit_modify(MCP_CANINTF, MCP_RX0IF, 0x00);
	//fprintf(UART_p, "\r\n \r\n", 0);
	
	return message;
}

int CAN_error() {
	
	return (MCP2515_read(MCP_TXB0CTRL) & (1 << TXERR) || (MCP2515_read(MCP_TXB0CTRL) & (1 << MLOA)));
}*/