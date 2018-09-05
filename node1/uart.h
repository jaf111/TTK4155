#ifndef UART_H
#define UART_H

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD)-1

//typedef struct __file FILE;

void USART_Init(unsigned int ubrr);

void USART_Transmit(unsigned char data);

unsigned char USART_Receive(void);

//FILE* fdevopen (int(*USART_Transmit)(char, FILE *), int(*USART_Receive)(FILE *));

#endif // UART_H