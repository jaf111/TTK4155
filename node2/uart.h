#ifndef UART_H
#define UART_H

#define FOSC 16000000				//Clock Speed (Oscillator)
#define BAUD 9600					//USART blaudrate speed
#define MYUBRR (FOSC/16/BAUD)-1		//Speed configuration for USART0

void USART_init(unsigned int ubrr);		//USART initialization

void USART_transmit(unsigned char data);	//USART transmit of data

unsigned char USART_receive(void);			//USART receive of data

//It opens a file to read/write. Necessary to use printf() (and similar functions) with the USART.
//Otherwise one should write to the USART manually byte-by-byte via the UDRx register
static FILE uart_out = FDEV_SETUP_STREAM (USART_transmit, NULL, _FDEV_SETUP_WRITE);
static FILE uart_in = FDEV_SETUP_STREAM (NULL, USART_receive, _FDEV_SETUP_READ);
#define UART_p (&uart_out)

#endif // UART_H