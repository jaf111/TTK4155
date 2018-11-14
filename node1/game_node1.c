#include <stdio.h>		
#include <avr/io.h> 	
#include <avr/interrupt.h>

#include "uart.h"		
#include "buttons.h"	
#include "can.h"		

packet start_game = {.id=0x03, .length=0x01, .data={0x06}};
packet end_game = {.id=CAN_END_GAME_ID, .length=0x00, .data={}};
packet score;

uint8_t game_node1_play(){
	CAN_send(&start_game);
		while(1){
			fprintf(UART_p,"Playing \r\n",0);
			buttons_send_CAN_message();	

			if (BUTTON_L || CAN_message_recieved()){	// Can message recieved => game over
				//CAN_send(&end_game);					// Tell node 2 to stop game
				score = CAN_read();						// Retrieve score
				fprintf(UART_p,"score: %d \r\n",score.data[0]);
				
				return score.data[0];			
			}
		}
}