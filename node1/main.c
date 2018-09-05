#ifndef F_CPU
#define F_CPU 1000000



#include <util/delay.h>
#include "led.h"
#include "uart.h"

int main(){
	led_init();

	//USART
	USART_Init (MYUBRR);


	unsigned char data = 45;

	while(1){
		led_turn_on();
		_delay_ms(2000);

		led_turn_off();
		USART_Transmit(data);
		_delay_ms(2000);

	}

	return 0;
}

#endif