#ifndef UART_H
#define UART_H

#include <stdio.h>

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD)-1

void USART_Init(unsigned int ubrr);

void USART_Transmit(unsigned char data);

unsigned char USART_Receive(void);

static FILE uart_out = FDEV_SETUP_STREAM (USART_Transmit, NULL, _FDEV_SETUP_WRITE);
static FILE uart_in = FDEV_SETUP_STREAM (NULL, USART_Receive, _FDEV_SETUP_READ);

#define UART_p (&uart_out)

#endif // UART_H