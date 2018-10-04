#include <util/delay.h>
#include <avr/io.h> 
#include <stdio.h> 

#include "uart.h"
#include "spi.h"
#include "can.h"
#include "MCP2515.h"

#define CAN_CS DDB4

uint8_t MCP2515_init() {
	uint8_t value;
	SPI_init(); 		// Initialize SPI
	MCP2515_reset(); 	// Send reset-command
	// Self-test
	value = MCP2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		fprintf(UART_p, "MCP2515 is NOT in configuration mode after reset!\r\n",0);
		return 1;
	}
	// More initialization
	return 0;
}


void MCP2515_reset() {
	PORTB &= ~(1 << CAN_CS); 	// Select CAN-controller
	SPI_write(MCP_RESET); 		// Re-initialize all internal registers
	PORTB |= (1 << CAN_CS); 	// Deselect CAN-controller
}

uint8_t MCP2515_read_status() {
	uint8_t result;
	PORTB &= ~(1 << CAN_CS); 	// Select CAN-controller
	SPI_write(MCP_READ_STATUS);	// Request to read the status
	result = SPI_read(); 		// Read status of CAN communication
	PORTB |= (1 << CAN_CS); 	// Deselect CAN-controller

	return result;
}

uint8_t MCP2515_read(uint8_t address) {
	PORTB &= ~(1 << CAN_CS); 	// Select CAN-controller
	uint8_t result;
	SPI_write(MCP_READ); 		// Send read instruction
	SPI_write(address); 		// Define which register read from
	result = SPI_read(); 		// Take the result from CAN contr
	PORTB |= (1 << CAN_CS); 	// Deselect CAN-controller	
	return result;
}

void MCP2515_write(uint8_t CANdata, uint8_t address) {
	PORTB &= ~(1 << CAN_CS); 	// Select CAN-controller
	SPI_write(MCP_WRITE);		// Send write instruction
	SPI_write(address); 		// Define which register write to
	SPI_write(CANdata); 		// Apply value to specified register
	PORTB |= (1 << CAN_CS); 	// Deselect CAN-controller
}

void MCP2515_request_to_send(uint8_t buffer) {
	PORTB &= ~(1 << CAN_CS); 	// Select CAN-controller
	SPI_write(buffer);			// MCP_RTS_TX0, MCP_RTS_TX1, MCP_RTS_TX2, MCP_RTS_ALL
	PORTB |= (1 << CAN_CS); 	// Deselect CAN-controller
}

void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {	//It modifies one (or more) bit of a register
	PORTB &= ~(1 << CAN_CS); 	// Select CAN-controller
	SPI_write(MCP_BITMOD);		// Petition to modify a register
	SPI_write(address);			// Define the addres of the register
	SPI_write(mask);			// A mask define which bits are allowed to be modified (1=YES, 0=NO)
	SPI_write(data);			// The whole data si resent (only bits previously defined will be updated)
	PORTB |= (1 << CAN_CS); 	// Deselect CAN-controller
}