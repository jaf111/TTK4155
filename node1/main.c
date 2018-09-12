#ifndef F_CPU
#define F_CPU 4915200

#include <util/delay.h>
#include "led.h"
#include "uart.h"
#include "sram.h"

unsigned int test = 0;

int main(){
	led_init();

	//USART
	USART_Init(MYUBRR);
	USART_Transmit(USART_Receive());
	SRAM_init();

	while(1){
		SRAM_write(131, 0x1800);
		_delay_ms(100);
		SRAM_read(0x1800);

		
		_delay_ms(200);

		//SRAM_test();

		/*led_turn_on();
		_delay_ms(100);
		led_turn_off();
		_delay_ms(100);*/
	}

	return 0;
}

#endif