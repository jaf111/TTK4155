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
//#include "notes_songs.h" //Prototype functions for playing a song

#define MENU1 0			//Position of parent menu 1
#define MENU2 4			//Position of parent menu 2
#define MENU3 10		//Position of parent menu 3


int main() {
	//GPIO initialization
	//led_init();		//LED initialization
	//buzzer_init();		//Buzzer initialization

	USART_Init(MYUBRR);

	SRAM_init();

	ADC_init();

	buttons_init();

	OLED_init();

	menu_init();

	SPI_init();

	CAN_init();
	fprintf(UART_p, "init done \n\r", 0);

	/*
	packet can_message1 = {.id = 0x13, .length = 0x08, .data = {0x07,0x02,0x03,0x04,0x05,0x06,0x07,0x09}};	//Struct initialization
	packet can_message2 = {.id = 0x14, .length = 0x07, .data = {0x05,0x02,0x03,0x04,0x13,0x06,0x07}};
	packet can_message3 = {.id = 0x15, .length = 0x07, .data = {0x01,0x02,0x03,0x04,0x13,0x06,0x07}};*/

	packet can_joystick = {.id = 0x16, .length = 0x02, .data = {0x01,0x02}};

	//buzzer_on();
	

	while(1) {
		joy_position_t joy_coord = buttons_get_joy_coord();	// (use struct from buttons.h to get coordinates (joy_coord.XX etc))
		slider_position_t slider_pos = buttons_get_slider_positions();
		can_joystick.data[0] = joy_coord.XX;
		can_joystick.data[1] = joy_coord.YY;
		fprintf(UART_p, "JoyX: %4d ", can_joystick.data[0]);
		fprintf(UART_p, "JoyY: %4d \r\n", can_joystick.data[1]);
		CAN_send(&can_joystick);
		//play_song();

		//fprintf(UART_p, "slider, R = %d   ADC read = %d  \r\n", slider_pos.right, ADC_read(SLIDER_R));
		//cursor_move();

		
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
		
		//OLED_draw_circle((JoyX/2), 60 - (JoyY/5), 6 + (joy_coord.slider_l_pos/10));
		//OLED_draw_rectangle((joy_coord.XX/2), 60 - (joy_coord.YY/5), (slider_pos.left/2), (slider_pos.right/5)); 
		//OLED_draw_rectangle((joy_coord.XX/2), 60 - (joy_coord.YY/5), (slider_pos.left/3), (slider_pos.right/8));
		//OLED_draw_rectangle((joy_coord.XX/2), 60 - (joy_coord.YY/5), (slider_pos.left/4), (slider_pos.right/15));
		//OLED_draw_circle( 40 + (JoyX/5), 50 - (JoyY/8), 6);
		//OLED_draw_circle( 40 + (JoyX/5), 50 - (JoyY/8), 2);
		OLED_paint();
		OLED_update();
		//OLED_clear_all();
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