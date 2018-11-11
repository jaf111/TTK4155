#include <stdio.h>		
#include <avr/io.h> 	
#include <avr/interrupt.h>

#include "uart.h"		
#include "buttons.h"	
#include "can.h"		

uint8_t game_node1_play(){
	packet score;
		while(1){
			fprintf(UART_p,"Playing \r\n",0);
			buttons_send_CAN_message();				
			if (BUTTON_L || CAN_message_recieved()){	// Can message => Score recieved and game is over
				score = CAN_read();
				fprintf(UART_p,"score: %d \r\n",score.data[0]);
				return score.data[0];				
			}
		}
}