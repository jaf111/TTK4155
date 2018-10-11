#include <util/delay.h>	//Functions for busy-wait delay loops
#include <avr/io.h>		//Specific IO for AVR micro (all registers defined inside)
#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...) 

#include "spi.h"		//To communicate through SPI protocol
#include "uart.h"		//To use the fprintf command through serial comm
/*#include "can.h"		//
#include "MCP2515.h"	//Prototypes of functions here defined

#define CAN_CS DDB4		//Location of Chip Select (CS) pin of CAN controller (MCP2515)

// CAN-controller communicates with ATmega162 through SPI communication

uint8_t MCP2515_init() {	//CAN-controller initialization
	uint8_t value;
	SPI_init(); 			//SPI comm initialization (just in case it was not before)
	MCP2515_reset(); 		//CAN-controller reset (registers initialization)
	// Self-test to confirm CAN-controller is config mode after reset
	value = MCP2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		fprintf(UART_p, "MCP2515 is NOT in configuration mode after reset!\r\n",0);
		return 1;
	}
	return 0;
}

void MCP2515_reset() {			//CAN-controller reset (registers initialization)
	PORTB &= ~(1 << CAN_CS); 	//Select CAN-controller (~CS=0)
	SPI_write(MCP_RESET); 		//Re-initialize all internal registers
	PORTB |= (1 << CAN_CS); 	//Deselect CAN-controller (~CS=1)
}

uint8_t MCP2515_read_status() {	//Checks CAN-controller status
	uint8_t result;
	PORTB &= ~(1 << CAN_CS); 	//Select CAN-controller (~CS=0)
	SPI_write(MCP_READ_STATUS);	//Request to read the status
	result = SPI_read(); 		//Status of CAN-controller is read
	PORTB |= (1 << CAN_CS); 	//Deselect CAN-controller (~CS=1)

	return result;
}

uint8_t MCP2515_read(uint8_t address) {	//Reads data from CAN-controller
	PORTB &= ~(1 << CAN_CS); 	//Select CAN-controller (~CS=0)
	uint8_t result;
	SPI_write(MCP_READ); 		//Send read instruction to CAN-controller
	SPI_write(address); 		//Define which register read from
	result = SPI_read(); 		//Take the result from CAN-controller
	PORTB |= (1 << CAN_CS); 	//Deselect CAN-controller (~CS=1)	
	
	return result;
}

void MCP2515_write(uint8_t CANdata, uint8_t address) {	//Sends data to CAN-controller
	PORTB &= ~(1 << CAN_CS); 	//Select CAN-controller (~CS=0)
	SPI_write(MCP_WRITE);		//Send instruction to write
	SPI_write(address); 		//Define which register write into
	SPI_write(CANdata); 		//Send the value to the specified register
	PORTB |= (1 << CAN_CS); 	//Deselect CAN-controller (~CS=1)
}

void MCP2515_request_to_send(uint8_t buffer) {	//Sends a request to send data
	PORTB &= ~(1 << CAN_CS); 	//Select CAN-controller (~CS=0)
	SPI_write(buffer);			//MCP_RTS_TX0, MCP_RTS_TX1, MCP_RTS_TX2, MCP_RTS_ALL
	PORTB |= (1 << CAN_CS); 	//Deselect CAN-controller (~CS=1)
}

void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {	//Modifies one (or more) bits of a register
	PORTB &= ~(1 << CAN_CS); 	//Select CAN-controller (~CS=0)
	SPI_write(MCP_BITMOD);		// Petition to modify a register
	SPI_write(address);			// Define the addres of the register
	SPI_write(mask);			// A mask define which bits are allowed to be modified (1=YES, 0=NO)
	SPI_write(data);			// The whole data si resent (only bits previously defined will be updated)
	PORTB |= (1 << CAN_CS); 	//Deselect CAN-controller (~CS=1)
}*/