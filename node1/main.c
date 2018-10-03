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

#define MENU1 0
#define MENU2 4
#define MENU3 10

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
	uint8_t i = 23;

	//Menu init
	menu_init();
	
	while(1){

		menu* menu = MENU_create_menu(menu_matrix[0][0], 3);
		insert_menu(menu, menu_matrix[0][1], 0, fprintf(OLED_p));
		//fprintf(OLED_p, "Hello");
		fprintf(UART_p, "Hello: %d \r\n");
		//print_sub_menu(MENU3);
		//cursor_move();
		//fprintf(OLED_p, "A");
		//fprintf(UART_p, "B\n");''
		
		
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
		
		/*OLED_pos(0, 0);
		OLED_print("Hello");
		_delay_ms(100);*/

		/*print_sub_menu(1, 3);
		_delay_ms(2000);
		OLED_clear_all();
		print_sub_menu(2, 4);
		_delay_ms(2000);
		OLED_clear_all();
		print_sub_menu(3, 5);
		_delay_ms(2000);
		OLED_clear_all();

		
		//font_byte = pgm_read_byte(&(font4[1][1]));	//To take data saved in Flash (PROGMEM)
		//OLED_pos(line, 2);		//To print font4 (4 columns per character)
		

		
		/*JoyX = ADC_read(JOY_LR);
		JoyY = ADC_read(JOY_DU);
		
		if (BUTTON_R) {printf("RIGHT BUTTON \n\r");}
		if (BUTTON_L) {printf("LEFT BUTTON \n\r");}

		getJoyCoord(JoyX, JoyY, JoyX_init, JoyY_init);
		getJoyDirection(JoyX, JoyY);

		sliders();*/

		/*SRAM_write(120, 0x1800);
		_delay_ms(100);
		SRAM_read(0x1800);
		_delay_ms(100);

		SRAM_test();*/

		/*led_turn_on();
		_delay_ms(100);
		led_turn_off();
		_delay_ms(100);*/
	}

	return 0;
}

#endif