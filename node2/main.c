#ifndef F_CPU
#define F_CPU 16000000	//Clock Speed (Oscillator)

#include <util/delay.h>	//Functions for busy-wait delay loops
#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...) 
#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)

#include "uart.h"		//Prototype functions of USART unit
#include "adc.h"		//Prototype functions of ADC unit
#include "buttons.h"	//Prototype functions of buttons (USB board) unit
#include "spi.h"		//Prototype functions of SPI communication
#include "MCP2515.h"	//Prototype functions of CAN controller unit
#include "can.h"	//Prototype functions of CAN communication

#define JOY_LR 0x04		//ADC channel 1, where Left-Right Joystick is connected to
#define JOY_DU 0x05		//ADC channel 2, where Down-Up Joystick is connected to
#define SLIDER_R 0x06	//ADC channel 3, where Right Slider is connected to
#define SLIDER_L 0x07	//ADC channel 4, where Left Slider is connected to
//#define BUTTON_R PINB & (1<<PB0)	//If button Right is pushed (connected to pin PB0, PORTB)
//#define BUTTON_L PINB & (1<<PB1)	//If button Left is pushed (connected to pin PB0, PORTB)

int16_t JoyX = 0;		//X coordinate of Joystick
int16_t JoyY = 0;		//Y coordinate of Joystick
int16_t JoyX_init = 0;	//Initial X coordinate of Joystick
int16_t JoyY_init = 0;	//Initial Y coordinate of Joystick

void led_init() {
	DDRL |= (1 << DDL0);	//Enable pin 0 (bit DDL0) of Port L (register DDRL)
	PORTL |= (1 << PL0);	//Set pin 0 (bit PL0) in PORT L (register PORTL) to 1, leave other bits unchanged
}

void led_turn_off() {
	PORTL &= ~(1 << PL0);	//Clear pin 0 (bit PB0) in PORT B (register PORTB), leave other bits unchanged
}

void led_turn_on() {
	PORTL |= (1 << PL0);	//Set pin 0 (bit PB0) in PORT B (register PORTB) to 1, leave other bits unchanged
}

int main() {
	//USART initialization
	led_init();
	USART_Init(MYUBRR);
	USART_Transmit(USART_Receive());	//To make printf() working in USART
	//led_turn_on();
	//ADC initialization
	//ADC_init();

	//Buttons initialization
	//button_init();
	//Stand-by joystick positions read (for the offset)
	//JoyX_init = JoyCoord_init(ADC_read(JOY_LR));
	//JoyY_init = JoyCoord_init(ADC_read(JOY_DU));

	//SPI initialization
	//SPI_init();

	//CAN controller (MCP2515) initialization
	//CAN_init();

	/*packet can_message1 = {.id=0x13, .length=0x08, .data={0x07,0x02,0x03,0x04,0x05,0x06,0x07,0x09}};	//Struct initialization
	packet can_message2 = {.id=0x14, .length=0x07, .data={0x05,0x02,0x03,0x04,0x13,0x06,0x07}};
	packet can_message3 = {.id=0x15, .length=0x07, .data={0x01,0x02,0x03,0x04,0x13,0x06,0x07}};
	*/

	while(1) {		
		//fprintf(UART_p, "NODE 2 TEST \r\n", 0);
		printf("Hello\r\n");
		USART_Transmit(5);
		led_turn_on();
		_delay_ms(500);
		led_turn_off();
		_delay_ms(500);
	}
	return 0;
}
#endif