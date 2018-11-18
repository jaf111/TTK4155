#ifndef F_CPU
#define F_CPU 4915200	//Clock Speed (Oscillator)

#include <stdio.h>		
#include <avr/io.h> 	
#include <avr/interrupt.h>
#include <util/delay.h>	

#include "uart.h"		
#include "buttons.h"	
#include "can.h"
#include "game_node1.h"
#include "highscore.h"
#include "play_song.h"

packet start_game = {.id=CAN_START_GAME_ID, .length=0x01, .data={0x06}};
packet end_game = {.id=CAN_END_GAME_ID, .length=0x00, .data={}};
packet shoot_ball = {.id=CAN_SHOOT_ID, .length=0x00, .data={}};
packet score;

int player_want_to_play = 1;
int player_option = 1;

uint8_t game_node1_play() {
	OLED_clear_all();
	OLED_update(); 
	OLED_pos(1,25);
	OLED_print_all("GO");
	OLED_pos(1,50);
	OLED_print_all(highscore_get_player_name());
	OLED_pos(5,20);
	OLED_print_all("LEFT=QUIT");
	CAN_send(&start_game);
	fprintf(UART_p, "ID: %X\r\n", start_game.id);
	int player_want_to_play = 1;
	int player_option = 1;
	
	game_start_song();
	
	//OLED_update(); 
	while(player_want_to_play) {
		//fprintf(UART_p, "Playing\r\n", 0);
		buttons_send_CAN_message();	
		OLED_update();
		player_option = 1;
		/*if (BUTTON_R) {
			fprintf(UART_p, "SHOOT \r\n", 0);
			CAN_send(&shoot_ball);		
		}*/

		if (BUTTON_L || CAN_message_recieved()) {	// Can message recieved => game over
			CAN_send(&end_game);					// Tell node 2 to stop game
			score = CAN_read();						// Retrieve score
			highscore_save_sram(highscore_get_player_name(), score.data[0]);
			OLED_clear_all();

			game_finish_song();

			while(player_option){
				OLED_update();
				OLED_pos(0,25);
				OLED_print_all("GAME OVER");
				OLED_pos(2,25);
				OLED_print_all("SCORE");
				OLED_pos(2,75);
				OLED_print_number(score.data[0]);
				OLED_pos(5,20);
				OLED_print_all("RIGHT=RETRY");
				OLED_pos(6,20);
				OLED_print_all("LEFT=QUIT");
				_delay_ms(500);

				if(BUTTON_R){
					OLED_clear_all();
					OLED_update(); 
					OLED_pos(1,25);
					OLED_print_all("GO");
					OLED_pos(1,50);
					OLED_print_all(highscore_get_player_name());
					OLED_pos(5,20);
					OLED_print_all("LEFT=QUIT");
					CAN_send(&start_game);
					CAN_send(&start_game);
					CAN_send(&start_game);
					player_option = 0;
					game_start_song();
				}

				if(BUTTON_L){
					player_want_to_play = 0;
					player_option = 0;
				}	
			}		
		}
	}
	return 1;
}
#endif //F_CPU