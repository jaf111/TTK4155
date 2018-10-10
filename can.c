#include <util/delay.h>
#include <avr/io.h> 
#include <stdio.h> 

#include "uart.h"		//Added to use fprintf function

#include "spi.h"
#include "can.h"
#include "MCP2515.h"

#define MAX_CAN_DATA 8


void CAN_init() {
	MCP2515_init();
	//2 element (mask) defines which numbers are allowed to change
	MCP2515_bit_modify(MCP_CANCTRL, 0b11100000, MODE_LOOPBACK);	// Set in loopback mode
}

void CAN_send(packet* message) {	//Everything is done only through Buffer 0
	uint8_t CAN_id = 0;
	uint8_t length = 0;
	uint8_t CANdata[8];

	CAN_id = message->id;
	length = message->length;
	CAN_id = 0xB6;
	length = 0x06;
	CANdata[0] = 0x00;
	CANdata[1] = 0x11;
	CANdata[2] = 0x22;
	CANdata[3] = 0x33;
	CANdata[4] = 0x44;
	CANdata[5] = 0x55;
	CANdata[6] = 0x66;
	CANdata[7] = 0x77;

	while (MCP_TXB0CTRL & (1<<TXREQ));	//Waits until last transmission finishes

	MCP2515_bit_modify(MCP_TXB0SIDH, 0b00011111, CAN_id>>3);
	MCP2515_bit_modify(MCP_TXB0SIDL, 0b11100000, CAN_id<<5);
	MCP2515_bit_modify(MCP_TXB0DLC, 0x0F, length);
	//fprintf(UART_p, "TXB0SIDH: %4x, TXB0SIDL: %4x: \r\n", MCP2515_read(MCP_TXB0SIDH), MCP2515_read(MCP_TXB0SIDL));

	for (uint8_t i=0; i<MAX_CAN_DATA; i++) {
		//CANdata = message->data[i];
		if (i>=length) {CANdata[i] = 0x00;}		//If message shorter than maximum, rest is cleared
		MCP2515_bit_modify(MCP_TXB0D0+i, 0xFF, CANdata[i]);
		fprintf(UART_p, "MCP_TXB0D %4x: %4x \r\n", i, MCP2515_read(MCP_TXB0D0+i));
	}
	MCP2515_request_to_send(MCP_RTS_TX0);

	/*_delay_ms(10);
	if (MCP_TXB0CTRL & (1<<TXERR)) {	//If there is an error in the transmission
		fprintf(UART_p, "ERRORRRRRRRRRR %4x \r\n", MCP2515_read(MCP_TXB0CTRL));
	}*/
}

void CAN_read() {
	//fprintf(UART_p, "RXB0SIDH: %4x, RXB0SIDL: %4x: \r\n", MCP2515_read(MCP_RXB0SIDH), MCP2515_read(MCP_RXB0SIDL));

	for (uint8_t i=0; i<MAX_CAN_DATA; i++) {
		fprintf(UART_p, "MCP_RXB0D %4x: %4x \r\n", i, MCP2515_read(MCP_RXB0D0+i));
	}
	//fprintf(UART_p, "RXB0CTRL: %4x \r\n", MCP2515_read(MCP_RXB0CTRL));
}