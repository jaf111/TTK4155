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
	USART_Init (MYUBRR);
	USART_Transmit(USART_Receive());

	SRAM_test();

	while(1){
		//SRAM_test();
		//simple led test PC0 in
		//led_turn_on();  
		//delay_ms(100);
		//led_turn_off();
		//UART test
		//printf("Hello world\n"); //scanner() works to
		
		_delay_ms(1000);

		

		//SRAM_write(123, 0x1805);
		//test = SRAM_read(0x1805);

		if (test == 123) led_turn_off();
		else led_turn_on();
	}

	return 0;
}

#endif