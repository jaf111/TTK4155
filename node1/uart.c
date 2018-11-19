#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...) 
#include <stdint.h>		//Standard Integer Types (uint8_t, int16_t)

#include "uart.h"		//Prototype functions

void USART_init(unsigned int ubrr) {	//Atmel 162 has 2 USARTS -> USART 0 & USART1
	//MSB and LSB to establish the Blaudrate of USART0 (registers UBRR0H & UBRR0L)
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	//Receiver (bit RXEN0) and Transmitter (bit TXEN0) of USART0 enabled (register UCSR0B)
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	//Set frame format (URSEL0 = 1 to configure USART0): 8data bits (UCSZ00 & UCSZ01 = 1), 2stop bit (bit USBS = 1)
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);	//UCSZ00 is 3 to activate UCZ00 & UCSZ01 at a time

	//fdevopen(USART_transmit, USART_receive);		//NOT NECESSARY ANYMORE!! FUNCTION REDEFINED IN OLED!!
}

void USART_transmit(unsigned char data) {
	//Wait for empty transmit buffer in USART0 (bit UDRE0 of register UCSR0A)
	while (!(UCSR0A & (1<<UDRE0)));	
	
	//Put data into buffer, sends the data
	UDR0 = data;
}

unsigned char USART_receive(void) {
	/* Wait for data to be received*/
	//while(!(UCSR0A & (1<<RXC0)));

	/* Get and return received data from buffer*/
	return UDR0;
}