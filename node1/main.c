#ifndef F_CPU
#define F_CPU 4915200	//Clock Speed (Oscillator)

#include <util/delay.h>	//Functions for busy-wait delay loops
#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...) 
#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <avr/interrupt.h>

#include "led.h"		
#include "uart.h"		
#include "sram.h"		
#include "adc.h"		
#include "buttons.h"	
#include "oled.h"		
#include "menu.h"
#include "play_song.h"
#include "spi.h"		
#include "MCP2515.h"	
#include "can.h"		
#include "highscore.h"

#define MENU1 0			//Position of parent menu 1
#define MENU2 4			//Position of parent menu 2
#define MENU3 10		//Position of parent menu 3

int main() {
	//GPIO initialization
	//led_init();		//LED initialization
	//buzzer_init();		//Buzzer initialization

	cli();

	USART_Init(MYUBRR);
	SRAM_init();
	ADC_init();
	buttons_init();
	OLED_init();
	//menu_init();
	SPI_init();
	//highscore_init();
	CAN_init();
	fprintf(UART_p, "init\n\r", 0);

	//packet can_joystick = {.id = CAN_INPUT_ID, .length = 0x02, .data = {0x01,0x02}};
	//packet score2 = {.id=CAN_SCORE_ID, .length=0x02, .data={0x02,0x03}};

	//play_countdown();	//DO NOT FORGET THAT DELAYS MUST BE REMOVED TO PLAY THE SONG PROPERLY!

	sei();

	while(1) {
		
		//cursor_move();
		
		//all code to make highscore work (some problems with memory and buttons?)
		/*
		highscore_t highscore;
		create_name(&highscore);
		
		uint8_t* a;
		a = 10; 
		*/
		//insert_score(highscore.name, a); 
		//print_highscore();
		//fprintf(UART_p, "%s\r\n", "hello");*/
		


		
		/*
		joy_position_t joy_coord = buttons_get_joy_coord();	// (use struct from buttons.h to get coordinates (joy_coord.XX etc))
		slider_position_t slider_pos = buttons_get_slider_positions();
		can_joystick.data[0] = joy_coord.XX;
		can_joystick.data[1] = joy_coord.YY;
		//fprintf(UART_p, "JoyX: %4d ", can_joystick.data[0]);
		//fprintf(UART_p, "JoyY: %4d \r\n", can_joystick.data[1]);
		CAN_send(&can_joystick);*/	


		//packet score2 = CAN_read();
		//fprintf(UART_p, "score: %d \r\n", score2.data[0]);

		/*MCP2515_bit_modify(MCP_CANCTRL, 0b11100000, MODE_LOOPBACK);	//Set loopback mode
		_delay_ms(500);
		fprintf(UART_p, "CANSTAT: %4x, CANCTRL: %4x: \r\n", MCP2515_read(MCP_CANSTAT), MCP2515_read(MCP_CANCTRL));
		MCP2515_bit_modify(MCP_CANCTRL, 0b11100000, MODE_NORMAL);	//Set normal mode
		_delay_ms(500);
		fprintf(UART_p, "CANSTAT: %4x, CANCTRL: %4x: \r\n", MCP2515_read(MCP_CANSTAT), MCP2515_read(MCP_CANCTRL));
		*/

		//Some registers can only be modified in CONFIG MODE (p59 datasheet)
		/*MCP2515_bit_modify(MCP_CANCTRL, 0b11100000, MODE_CONFIG);
		MCP2515_bit_modify(MCP_CNF3, 0xFF, 0b10101010);
		fprintf(UART_p, "CNF30: %4x \r\n", MCP2515_read(MCP_CNF3));
		_delay_ms(500);
		MCP2515_bit_modify(MCP_CNF3, 0xFF, 0b00110011);
		fprintf(UART_p, "CNF31: %4x \r\n", MCP2515_read(MCP_CNF3));
		_delay_ms(500);*/
		//fprintf(UART_p, "Interrupt: %d \r\n", MCP2515_read(MCP_CANINTF));

		/*CAN_send(&can_message1);
		_delay_ms(500);
		packet new_message1 = CAN_read();
		CAN_send(&can_message2);
		_delay_ms(500);
		packet new_message2 = CAN_read();
		CAN_send(&can_message3);
		_delay_ms(500);
		packet new_message3 = CAN_read();*/

		//fprintf(UART_p, "JoyX CAN: %4d   JOYX; %4d \r\n", MCP2515_read(MCP_TXB0D0+0),JoyX);
		//fprintf(UART_p, "JoyY CAN: %4d   JOYY; %4d \r\n", MCP2515_read(MCP_TXB0D0+1),JoyY);
		
		OLED_update(); 

		//fprintf(UART_p, "Message data: %4x \r\n", new_message.length);
		/*for (uint8_t i=0; i < 8; i++) {
			fprintf(UART_p, "DATA %2x: %4x \r\n", i, new_message2.data[i]);
		}*/
		//fprintf(UART_p, "Interrupt: %d \r\n", MCP2515_read(MCP_CANINTF));

		//_delay_ms(100);
		//fprintf(UART_p, "CANCTRL: %4d \r\n", MCP2515_read(MCP_CANCTRL));
	}
	return 0;
}
#endif