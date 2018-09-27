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
#include "oled.h"

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
	OLED_init();
	uint8_t i = 0;
	
	while(1){
		
		/*OLED_pos(line, ADC_read(SLIDER_L)/2);
		write_d(0xFF);
		_delay_ms(100);
		OLED_clear_line(line);
		if (ADC_read(JOY_DU) > 230) {line++;}
		if (ADC_read(JOY_DU) < 25) {line--;}
		if (line > 7) {line = 0;}
		if (line < 0) {line = 7;}*/

		/*
		for (int i = 64; i > 0; i--){
			OLED_pos(4,i);
			write_d(0xFF);
		}*/

		//Why is this so hard to print?
		
		//OLED_print("HEllo");
		//_delay_ms(10);
		
		OLED_pos(0, i);
		OLED_print_char('1');
		_delay_ms(10);

		OLED_pos(1, i);
		OLED_print_char('2');
		_delay_ms(10);

		OLED_pos(2, i);
		OLED_print_char('3');
		_delay_ms(10);

		OLED_pos(3, i);
		OLED_print_char('4');
		_delay_ms(10);

		OLED_pos(4, i);
		OLED_print_char('5');
		_delay_ms(10);

		OLED_pos(5, i);
		OLED_print_char('6');
		_delay_ms(10);

		OLED_pos(6, i);
		OLED_print_char('7');
		_delay_ms(10);

		OLED_pos(7, i);
		OLED_print_char('8');
		_delay_ms(10);


		if (i < 128){
			i = i + 7;
		} else {
			i = 0;
			OLED_clear();
		}
		
		
		//font_byte = pgm_read_byte(&(font4[1][1]));	//To take data saved in Flash (PROGMEM)
		//OLED_pos(line, 2);		//To print font4 (4 columns per character)
		

		/*_delay_ms(1000);
		OLED_clear_line(6);

		_delay_ms(1000);
		OLED_home();
		write_d(0xFF);

		_delay_ms(1000);
		OLED_clear_line(0);*/

		
		/*JoyX = ADC_read(JOY_LR);
		JoyY = ADC_read(JOY_DU);
		
		if (BUTTON_R) {printf("RIGHT BUTTON \n\r");}
		if (BUTTON_L) {printf("LEFT BUTTON \n\r");}

		getJoyCoord(JoyX, JoyY, JoyX_init, JoyY_init);
		getJoyDirection(JoyX, JoyY);

		sliders();*/
		
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