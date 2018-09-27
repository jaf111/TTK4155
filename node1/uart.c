#include "uart.h"
#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

//#define  UART = FDEV_SETUP_STREAM (USART_Transmit, ,USART_Receive) 

void USART_Init(unsigned int ubrr){

	/* Set baud rate*/
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* 	Set frame format: 8data, 2stop bit*/
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00); // 3 beacuse activating UCZ00 && UCSZ01

	fdevopen(USART_Transmit, USART_Receive);
}


void USART_Transmit(unsigned char data){
	
	/* Wait for empty transmit buffer*/
	while (!( UCSR0A & (1<<UDRE0)));
	
	/* Put data into buffer, sends the data */
	UDR0 = data;

}

unsigned char UDR0_old = 0;

unsigned char USART_Receive(void){
	
	/* Wait for data to be received*/
	//while(!(UCSR0A & (1<<RXC0)));
	
	if (UDR0_old != UDR0);
	UDR0_old = UDR0;

	/* Get and return received data from buffer*/
	

	return UDR0;

}


