#ifndef F_CPU
#define F_CPU 4915200



#include <util/delay.h>
#include "led.h"
#include "uart.h"



int main(){
	led_init();

	//USART
	USART_Init (MYUBRR);

	unsigned char data = 'F';

	while(1){
		led_turn_on();
		_delay_ms(100);

		led_turn_off();
		USART_Transmit(USART_Receive());
		printf("Hello wolrd\n");
		//USART_Transmit(printf(data));
		//USART_Transmit(data);
		_delay_ms(100);

	}

	return 0;
}

#endif