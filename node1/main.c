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
#include "menu.h"

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
	menu main_menu;
	menu_init();
	menu* new_menu = init_menu1(main_menu);
	
	//struct menu* menu = create_menu("Main menu", NULL, NULL, NULL, &option, 3);

	
	OLED_screen_Saver();

	while(1){

		//SRAM_test();
		//fprintf(OLED_p, main_menu.name);
		//_delay_ms(100);
		//insert_menu(menu, menu_matrix[0][1], 1, 0, NULL); 
		
		fprintf(UART_p, "Hello\r\n",0);
		//print_sub_menu(MENU1);
		//cursor_move();
		//fprintf(OLED_p, "%d", (main_menu.select));
		//fprintf(OLED_p, "A");
		//fprintf(UART_p, "B\n");''
		//OLED_screen_Saver();
		
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


		/*led_turn_on();
		_delay_ms(100);
		led_turn_off();
		_delay_ms(100);*/
	}

	return 0;
}

#endif