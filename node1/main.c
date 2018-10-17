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
	//menu_init();
	OLED_screen_Saver();

	//SPI initialization
	SPI_init();

	//CAN controller (MCP2515) initialization
	CAN_init();

	position joy_coord = {0, 0};

	packet can_message1 = {.id = 0x13, .length = 0x08, .data = {0x07,0x02,0x03,0x04,0x05,0x06,0x07,0x09}};	//Struct initialization
	packet can_message2 = {.id = 0x14, .length = 0x07, .data = {0x05,0x02,0x03,0x04,0x13,0x06,0x07}};
	packet can_message3 = {.id = 0x15, .length = 0x07, .data = {0x01,0x02,0x03,0x04,0x13,0x06,0x07}};

	packet can_joystick = {.id = 0x16, .length = 0x02, .data = {0x01,0x02}};

	while(1) {
		//cursor_move();
		//SRAM_test();
		//fprintf(OLED_p, main_menu.name);
		//_delay_ms(100);
		//insert_menu(menu, menu_matrix[0][1], 1, 0, NULL); 
		
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

		JoyX = ADC_read(JOY_LR);
		JoyY = ADC_read(JOY_DU);
		joy_coord = getJoyCoord(JoyX, JoyY, JoyX_init, JoyY_init);
		//fprintf(UART_p, "JoyX: %4d \r\n", joy_coord.XX);
		//fprintf(UART_p, "JoyY: %4d \r\n", joy_coord.YY);

		can_joystick.data[0] = JoyX;
		can_joystick.data[1] = JoyY;

		CAN_send(&can_joystick);
		//_delay_ms(500);
		//CAN_read();

		//fprintf(UART_p, "JoyX: %4d \r\n", MCP2515_read(MCP_RXB0D0+0));
		//fprintf(UART_p, "JoyY: %4d \r\n", MCP2515_read(MCP_RXB0D0+1));
		
	
		//fprintf(UART_p, "Message data: %4x \r\n", new_message.length);
		/*for (uint8_t i=0; i < 8; i++) {
			fprintf(UART_p, "DATA %2x: %4x \r\n", i, new_message2.data[i]);
		}*/
		//fprintf(UART_p, "Interrupt: %d \r\n", MCP2515_read(MCP_CANINTF));

		//_delay_ms(100);
		//fprintf(UART_p, "CANCTRL: %4d \r\n", MCP2515_read(MCP_CANCTRL));
		//print_sub_menu(MENU1);
		//cursor_move();


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