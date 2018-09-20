#ifndef F_CPU
#define F_CPU 4915200

#include <util/delay.h>
#include <avr/io.h> 
#include <stdio.h> 

#include "led.h"
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "buttons.h"
//#include "oled.h"

#define JOY_LR 0x04
#define JOY_DU 0x05
#define SLIDER_R 0x06
#define SLIDER_L 0x07
#define BUTTON_R PINB & (1<<PB0)
#define BUTTON_L PINB & (1<<PB1)

int16_t JoyX = 0;
int16_t JoyY = 0;
int16_t JoyX_init = 0;
int16_t JoyY_init = 0;


int main(){
	//led_init();

	//USART
	USART_Init(MYUBRR);
	USART_Transmit(USART_Receive());
	
	//SRAM
	SRAM_init();

	//ADC
	ADC_init();

	//Button init
	button_init();
	JoyX_init = JoyCoord_init(ADC_read(JOY_LR));
	JoyY_init = JoyCoord_init(ADC_read(JOY_DU));

	//OLED init
	//OLED_init();


	while(1){
		_delay_ms(600);
		
		JoyX = ADC_read(JOY_LR);
		JoyY = ADC_read(JOY_DU);
		
		if (BUTTON_R) {printf("RIGHT BUTTON \n\r");}
		if (BUTTON_L) {printf("LEFT BUTTON \n\r");}

		//getJoyCoord2(JoyX, JoyY, JoyX_init, JoyY_init);
		getJoyCoord(JoyX, JoyY, JoyX_init, JoyY_init);
		getJoyDirection(JoyX, JoyY);

		sliders();

		//OLED_pos(0xB0, 0x00);
		//OLED_write_data(0x8);

		/*SRAM_write(120, 0x1800);
		_delay_ms(100);
		SRAM_read(0x1800);
		_delay_ms(100);*/

		//SRAM_test();

		/*led_turn_on();
		_delay_ms(100);
		led_turn_off();
		_delay_ms(100);*/
	}

	return 0;
}

#endif