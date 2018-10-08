#ifndef F_CPU
#define F_CPU 4915200	//Clock Speed (Oscillator)

#include <util/delay.h>	//Functions for busy-wait delay loops
#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...) 
#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)

#include "led.h"		//Prototype functions of LED unit
#include "uart.h"		//Prototype functions of USART unit
#include "sram.h"		//Prototype functions of SRAM unit
#include "adc.h"		//Prototype functions of ADC unit
#include "buttons.h"	//Prototype functions of buttons (USB board) unit
#include "oled.h"		//Prototype functions of OLED (USB board) unit
#include "menu.h"		//Prototype functions of the menu
#include "spi.h"		//Prototype functions of SPI communication
#include "MCP2515.h"	//Prototype functions of CAN controller unit
#include "can.h"		//Prototype functions of CAN communication

#define JOY_LR 0x04		//ADC channel 1, where Left-Right Joystick is connected to
#define JOY_DU 0x05		//ADC channel 2, where Down-Up Joystick is connected to
#define SLIDER_R 0x06	//ADC channel 3, where Right Slider is connected to
#define SLIDER_L 0x07	//ADC channel 4, where Left Slider is connected to
#define BUTTON_R PINB & (1<<PB0)	//If button Right is pushed (connected to pin PB0, PORTB)
#define BUTTON_L PINB & (1<<PB1)	//If button Left is pushed (connected to pin PB0, PORTB)

#define MENU1 0			//Position of parent menu 1
#define MENU2 4			//Position of parent menu 2
#define MENU3 10		//Position of parent menu 3

int16_t JoyX = 0;		//X coordinate of Joystick
int16_t JoyY = 0;		//Y coordinate of Joystick
int16_t JoyX_init = 0;	//Initial X coordinate of Joystick
int16_t JoyY_init = 0;	//Initial Y coordinate of Joystick

int main(){
	//LED initialization
	//led_init();

	//USART initialization
	USART_Init(MYUBRR);
	USART_Transmit(USART_Receive());	//To make printf() working in USART
	
	//SRAM initialization
	SRAM_init();

	//ADC initialization
	ADC_init();

	//Buttons initialization
	button_init();
	//Stand-by joystick positions read (for the offset)
	JoyX_init = JoyCoord_init(ADC_read(JOY_LR));
	JoyY_init = JoyCoord_init(ADC_read(JOY_DU));

	//OLED initialization
	OLED_init();

	//Menu initialization
	menu_init();
	//OLED_screen_Saver();

	//SPI initialization
	SPI_init();

	//CAN controller (MCP2515) initialization
	CAN_init();

	while(1){
		//cursor_move();

		//SRAM_test();
		//fprintf(OLED_p, main_menu.name);
		_delay_ms(100);
		//insert_menu(menu, menu_matrix[0][1], 1, 0, NULL); 
		
		
		//MCP2515_bit_modify(MCP_CANCTRL, 0b11111111, 0b00010100);	// Enable loopback mode
		//_delay_ms(100);
		//fprintf(UART_p, "READ: %4x \r\n", MCP2515_read(MCP_CANCTRL));
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