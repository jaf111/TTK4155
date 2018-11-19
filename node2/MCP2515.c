#define F_CPU 16000000	//Clock Speed (Oscillator)

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

#include "spi.h"		//To communicate through SPI protocol
#include "uart.h"		//To use the fprintf command through serial comm
#include "can.h"
#include "MCP2515.h"	//Prototypes of functions here defined

// CAN-controller communicates with ATmega162 through SPI communication

uint8_t MCP2515_init() {
	uint8_t value;
	SPI_init(); 			//SPI init (just in case it was not before)
	MCP2515_reset(); 		//CAN-controller reset (registers initialization)
	
	// Self-test to confirm CAN-controller is config mode after reset
	value = MCP2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		fprintf(UART_p, "MCP2515 NOT in config mode after reset\r\n",0);
		return 1;
	}
	return 0;
}

void MCP2515_reset() {
	SPI_select(); 			//Select CAN-controller (~CS=0)
	SPI_write(MCP_RESET); 	//Re-initialize all internal registers
	SPI_deselect(); 		//Deselect CAN-controller (~CS=1)
	_delay_ms(10);     		//Delay for synchronization between ATmega 2560 and 162 (the first one is far faster)
}

uint8_t MCP2515_read_status() {
	uint8_t result;
	SPI_select();
	SPI_write(MCP_READ_STATUS);	//Request to read the status
	result = SPI_read();
	SPI_deselect();

	return result;
}

uint8_t MCP2515_read(uint8_t address) {
	uint8_t result;
	SPI_select();
	SPI_write(MCP_READ); 	//Send read instruction to CAN-controller
	SPI_write(address);
	result = SPI_read();
	SPI_deselect();
	
	return result;
}

void MCP2515_write(uint8_t CANdata, uint8_t address) {
	SPI_select();
	SPI_write(MCP_WRITE);	//Send instruction to write
	SPI_write(address);
	SPI_write(CANdata);
	SPI_deselect();
}

void MCP2515_request_to_send(uint8_t buffer) {
	SPI_select();
	SPI_write(buffer);	//MCP_RTS_TX0, MCP_RTS_TX1, MCP_RTS_TX2, MCP_RTS_ALL
	SPI_deselect();
}

void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	SPI_select();
	SPI_write(MCP_BITMOD);	// Petition to modify a register
	SPI_write(address);		// Define the address of the register
	SPI_write(mask);		// Mask defines which bits are allowed to modify (1=YES, 0=NO)
	SPI_write(data);		// The whole data is resent (only bits defined will be updated)
	SPI_deselect();
}

/* 	dmesg --follow
	lsusb
	ttyACM0 = USB
*/