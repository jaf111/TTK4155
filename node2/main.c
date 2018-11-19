#ifndef F_CPU
#define F_CPU 16000000	//Clock Speed (oscillator)

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
#include "pid.h"		//Prototype functions of PID control 2
#include "solenoid.h"	//Prototype functions of solenoid
#include "IR.h"			//Prototype functions of IR sensor
#include "game_node2.h"

int main() {
	cli();

	USART_init(MYUBRR);
	//USART_transmit(USART_receive());	//To make printf() working in USART if not working check usart_Receive() ->while loop
	fprintf(UART_p, "INIT_N2\n\r", 0);
	//buzzer_init();

	//Stand-by joystick positions read (for the offset)
	//JoyX_init = JoyCoord_init(ADC_read(JOY_LR));
	//JoyY_init = JoyCoord_init(ADC_read(JOY_DU));

	SPI_init();
	CAN_init();
	//TWCR |= (1<<TWIE)|(1<<TWINT); // Enable specific interupt
	TWI_master_init();
	servo_init();	//(connected in PB5)
	ADC_init();
	motor_init();
	solenoid_init();
	IR_init();

	//PID initialization
	/*pidData_t pidData;
	pid_init(&pidData, 20);	*/	//PID controller with frequency of 1000Hz

	packet can_joystick = {.id=0x12, .length=0x02, .data={0x01,0x02}};

	sei();			// Enable all interrupts
	while(1) {
		packet CAN_recieved = CAN_read();
		fprintf(UART_p, "%d\r\n", CAN_recieved.id);
		_delay_ms(100);
		if (CAN_recieved.id == CAN_START_GAME_ID) {		// Can also maybe be moved into an interrupt
			game_node2_play();
		}

		//----------------------------------------------------------------------------------
		//TEST FUNCTIONS UNDER
		
		//fprintf(UART_p, "%d\n\r", motor_encoder_max); 
		//_delay_ms(500);
		
		/*fprintf(UART_p, "TCNT0: %4d ", TCNT0);
		if (int_tim8 == 1) {
			int_tim8 = 0;
			fprintf(UART_p, "TIMER!!!!!!!! \r\n", 0);
		}
		_delay_ms(50);*/

		/*packet can_joystick = CAN_read();
		fprintf(UART_p, "JoyX: %4d ", can_joystick.data[0]);
		fprintf(UART_p, "JoyY: %4d \r\n", can_joystick.data[1]);
		fprintf(UART_p, "IR: %4d \r\n", ADC_read());
		move_servo(can_joystick.data[0]);	//Change Servo direction
		int16_t motor_pos = -motor_read_encoder();
		uint8_t setpoint = can_joystick.data[0];
		motor_move(pid_controller(&pidData, setpoint, motor_pos));*/
	}
	
	return 0;
}
#endif

/* 	dmesg --follow
	lsusb

	ttyACM0 = USB
*/