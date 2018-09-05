#ifndef F_CPU
#define F_CPU 1000000



#include <util/delay.h>
#include "led.h"
#include "uart.h"

int main(){
	/*led_init();

	while(1){
		led_turn_on();
		_delay_ms(1000);

		led_turn_off();
		_delay_ms(1000);
	}*/


	//USART
	USART_Init (MYUBRR);


	unsigned char data = 0;

	while(1){
		USART_Transmit(data++);
		_delay_ms(1000);
	}

	return 0;
}

#endif