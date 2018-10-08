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
#include "spi.h"
#include "can.h"
#include "MCP2515.h"

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
	
	//Menu init
	menu_init();
	//OLED_screen_Saver();

	//SPI init
	SPI_init();

	//CAN controller (MCP2515) init
	CAN_init();

	//OLED_frame_fill();

	OLED_update();
	
	while(1){

		
		
		_delay_ms(100);
		//OLED_update();
		/*
		SRAM_write(1900, 700);
		_delay_ms(100);
		SRAM_read(700);
		_delay_ms(100);
		*/


		//_delay_ms(100);
		/*
		fprintf(OLED_p, "A");
		OLED_update();
		write_d(0xFF);*/
		

		//cursor_move();


		//SRAM_test();
		//fprintf(OLED_p, main_menu.name);
		//_delay_ms(100);
		//insert_menu(menu, menu_matrix[0][1], 1, 0, NULL); 
		
		
		//MCP2515_bit_modify(MCP_CANCTRL, 0b11111111, 0b00010100);	// Enable loopback mode
		//_delay_ms(100);
		//fprintf(UART_p, "READ: %4x \r\n", MCP2515_read(MCP_CANCTRL));
		//print_sub_menu(MENU1);
		//cursor_move();
		//fprintf(OLED_p, "%d", (main_menu.select));
		//fprintf(OLED_p, "A");
		//fprintf(UART_p, "B\n");
		//OLED_screen_Saver();
		
		/*OLED_pos(line, ADC_read(SLIDER_L)/2);
		write_d(0xFF);
		_delay_ms(100);
		OLED_clear_line(line);
		if (ADC_read(JOY_DU) > 230) {line++;}
		if (ADC_read(JOY_DU) < 25) {line--;}
		if (line > 7) {line = 0;}
		if (line < 0) {line = 7;}*/
	
	
		
		/*JoyX = ADC_read(JOY_LR);
		JoyY = ADC_read(JOY_DU);
		
		if (BUTTON_R) {printf("RIGHT BUTTON \n\r");}
		if (BUTTON_L) {printf("LEFT BUTTON \n\r");}

		getJoyCoord(JoyX, JoyY, JoyX_init, JoyY_init);
		getJoyDirection(JoyX, JoyY);

		sliders();*/

	}

	return 0;
}

#endif