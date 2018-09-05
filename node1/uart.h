#ifndef UART_H
#define UART_H

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/(16*BAUD))-1

#define UCSRA 0x0B //(0x2B)
#define UDRE 5
#define RXC 7

#define UCSRB 0x0A //(0x2A)
#define TXEN 3
#define RXEN 4 
  

#define UCSRC 0x20 //(0x40)
#define UCSZ0 1
#define USBS 3
#define URSEL 7


void USART_Init(unsigned int ubrr);

void USART_Transmit(unsigned char data);

unsigned char USART_Receive(void);

#endif // UART_H