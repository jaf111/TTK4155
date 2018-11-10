#ifndef F_CPU
#define F_CPU 16000000	//Clock Speed (Oscillator)

#include <util/delay.h>	//Functions for busy-wait delay loops
#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...) 
#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <avr/interrupt.h>	//Functions to implement the interruptions

#include "led.h"		//Prototype functions of GPIO
#include "uart.h"		//Prototype functions of USART unit
#include "adc.h"		//Prototype functions of ADC unit
#include "buttons.h"	//Prototype functions of buttons (USB board) unit
#include "spi.h"		//Prototype functions of SPI communication
#include "MCP2515.h"	//Prototype functions of CAN controller unit
#include "can.h"		//Prototype functions of CAN communication
#include "PWM.h"		//Prototype functions of PWM output
#include "servo.h"		//Prototype functions of Servo motor
#include "TWI_Master.h" //Prototype functions of TWI controller
#include "motor.h"      //Prototype functions of motor
#include "pid_contr.h"	//Prototype functions of PID control
#include "solenoid.h"	//Prototype functions of solenoid


int main() {
	cli();

	//USART initialization
	USART_Init(MYUBRR);
	//USART_Transmit(USART_Receive());	//To make printf() working in USART if not working check usart_Receive() ->while loop
	
	fprintf(UART_p, "INIT \n\r", 0);

	//GPIO initialization
	//led_init();

	//Buttons initialization
	//buttons_init();

	//Stand-by joystick positions read (for the offset)
	//JoyX_init = JoyCoord_init(ADC_read(JOY_LR));
	//JoyY_init = JoyCoord_init(ADC_read(JOY_DU));

	//SPI initialization
	SPI_init();

	//CAN controller (MCP2515) initialization
	CAN_init();

	TWI_Master_Initialise();
	//Servo initialization
	Servo_init();	//Servo initialization (connected in PB5)

	//ADC initialization
	ADC_init();

	//TWCR |= (1<<TWIE)|(1<<TWINT); // Enable specific interupt
	
	//Motor initialization
	motor_init();

	//Solenoid initialization
	solenoid_init();

	//PID initialization
	pid_init(2, 50);	//Type 2 (PI) and frequency of 1000Hz

	/*packet can_message1 = {.id=0x13, .length=0x08, .data={0x07,0x02,0x03,0x04,0x05,0x06,0x07,0x09}};	//Struct initialization
	packet can_message2 = {.id=0x14, .length=0x07, .data={0x05,0x02,0x03,0x04,0x13,0x06,0x07}};
	packet can_message3 = {.id=0x15, .length=0x07, .data={0x01,0x02,0x03,0x04,0x13,0x06,0x07}};*/
	packet can_joystick = {.id=0x16, .length=0x02, .data={0x01,0x02}};
	
	//buzzer_init();
	//buzzer_on();
	//play_song(2);

	sei();							// Enable all interrupts

	motor_set_direction(LEFT);
	motor_set_speed(100);
	
	_delay_ms(1000);
	motor_reset_encoder();
	motor_set_speed(0);

	_delay_ms(10);
	motor_set_direction(RIGHT);
	motor_set_speed(100);
	_delay_ms(1000);
	int16_t motor_encoder_max = -motor_read_encoder();
	
	while(1) {
		

		//solenoid_push();
		
		//fprintf(UART_p, "%d\n\r", motor_encoder_max); 
		//_delay_ms(500);

		
		/*fprintf(UART_p, "TCNT0: %4d ", TCNT0);
		if (int_tim8 == 1) {
			int_tim8 = 0;
			fprintf(UART_p, "TIMER!!!!!!!! \r\n", 0);
		}
		_delay_ms(50);*/

		/*PWM_ON();
		fprintf(UART_p, "ON!!!!!!! \r\n", 0);
		_delay_ms(5000);
		PWM_OFF();
		fprintf(UART_p, "OFF!!!!!! \r\n", 0);
		_delay_ms(5000);*/

		//USART_Transmit(5);
		/*led_turn_on();
		_delay_ms(1000);
		led_turn_off();
		_delay_ms(1000);*/
		
		//SPI_write(0b01011100);

		/*CAN_send(&can_message1);
		_delay_ms(500);
		packet new_message1 = CAN_read();
		CAN_send(&can_message2);
		_delay_ms(500);
		packet new_message2 = CAN_read();
		CAN_send(&can_message3);
		_delay_ms(500);
		packet new_message3 = CAN_read();*/
		
		packet can_joystick = CAN_read();

		//_delay_ms(50);
		//fprintf(UART_p, "JoyX: %4d ", can_joystick.data[0]);
		//fprintf(UART_p, "JoyY: %4d ", can_joystick.data[1]);
		//fprintf(UART_p, "IR: %4d \r\n", ADC_read());
		Move_Servo(can_joystick.data[0]);	//Change Servo direction
		int16_t motor_pos = motor_read_encoder();
		uint8_t setpoint = can_joystick.data[0];
		motor_move(pid_controller(setpoint, motor_encoder_max)); //pid_controller(setpoint, 300)
	}
	return 0;
}
#endif

/* 	dmesg --follow
	lsusb

	ttyACM0 = USB
*/