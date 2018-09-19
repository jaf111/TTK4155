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

#define JOY_LR 0x04
#define JOY_DU 0x05
#define SLIDER_R 0x06
#define SLIDER_L 0x07
#define BUTTON_R PINB & (1<<PB0)
#define BUTTON_L PINB & (1<<PB1)

int16_t JoyX = 0;
int16_t JoyY = 0;

typedef struct {
	int16_t XX;
	int16_t YY;
} position;

enum JoyDir{NEUTRAL, RIGHT, UP, LEFT, DOWN} direction; 

position coord = {0, 0};

void getJoyCoord(int16_t X_coord, int16_t Y_coord) {
	if (X_coord < 127) {X_coord -= 127;}
	else {X_coord /= 2;}
	if (Y_coord < 127) {Y_coord -= 127;}
	else {Y_coord /= 2;}

	coord.XX = X_coord*100/127;
	coord.YY = Y_coord*100/127;

	printf("LEFT/RIGHT SIDE: %4d     ", coord.XX);
	printf("DOWN/UP SIDE: %4d     \n\r", coord.YY);
}

void getJoyDirection(int16_t X_coord, int16_t Y_coord) {

	if (X_coord>190) {
		if (Y_coord>190) {
			if (X_coord>Y_coord) {direction = RIGHT;}
			else {direction = UP;}
		} else if (Y_coord<64) {
			if (X_coord>2*Y_coord) {direction = RIGHT;}
			else {direction = DOWN;}
		} else {direction = RIGHT;}
	}
	else if (X_coord<64) {
		if (Y_coord>190) {
			if (2*X_coord>Y_coord) {direction = LEFT;}
			else {direction = UP;}
		} else if (Y_coord<64) {
			if (X_coord>Y_coord) {direction = LEFT;}
			else {direction = DOWN;}
		} else {direction = LEFT;}
	}
	else if (Y_coord>190) {
			direction = UP;
		} else if (Y_coord<64) {
			direction = DOWN;
		}
	else {direction = NEUTRAL;}

	printf("LEFT/RIGHT SIDE: %4d     ", X_coord);
	printf("DOWN/UP SIDE: %4d     ", Y_coord);
	printf("DIRECTION: %d \n\r", direction);
}

int main(){
	//led_init();

	//USART
	USART_Init(MYUBRR);
	USART_Transmit(USART_Receive());
	
	//SRAM
	SRAM_init();

	//ADC
	ADC_init();

	button_init();

	while(1){
		_delay_ms(1000);
		
		JoyX = ADC_read(JOY_LR);
		JoyY = ADC_read(JOY_DU);
		ADC_read(SLIDER_R);
		ADC_read(SLIDER_L);

		if (BUTTON_R) {printf("RIGHT BUTTON \n\r");}
		if (BUTTON_L) {printf("LEFT BUTTON \n\r");}

		//getJoyCoord(JoyX, JoyY);
		getJoyDirection(JoyX, JoyY);

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