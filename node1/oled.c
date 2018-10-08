#include <stdio.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
//#include <util/delay.h>

#include "oled.h"
#include "fonts.h"
#include "sram.h"

#define FONTWIDTH 8 //change font

volatile uint8_t *oled_cmd = (uint8_t *) 0x1000; //OLED Command start address
volatile uint8_t *oled_data = (uint8_t *) 0x1200; //OLED Data start address

static uint8_t gen_page, gen_col = 0;

volatile uint8_t *frame_addr = (uint8_t*)0x1800;

#define frame ( (uint8_t(*)[128]) (frame_addr) )



void write_c(uint8_t cmd) {
	*oled_cmd = cmd;
}

void write_d(uint8_t cmd) {
	*oled_data = cmd;
}

void OLED_init(void) {

	write_c(0xae);	//Display is switch OFF  
	write_c(0xa1);	//Segment remap (A1=Alligned to the right / A0=Alligned to the left)
	write_c(0xda);        //common  pads  hardware:  alternative  
	write_c(0x12);  
	write_c(0xc8);        //common output scan direction:com63~com0 
	write_c(0xa8);        //multiplex  ration  mode:63  
	write_c(0x3f);  
	write_c(0xd5);	//Display divide ratio/osc & freq. mode 
	write_c(0x80);		//Value. [7:4]-> Oscillator freq , [3:0]->Display clock
	write_c(0x81);	//Contrast control
	write_c(0x50);		//Value. From 00h (0%) to FFh (100%)
	write_c(0xd9);	//Set Pre-charge period  
	write_c(0x21);		//Value
	write_c(0x20);	//Set Memory Addressing Mode (AM)
	write_c(0x02);		//Value. 02h->Page AM 01h->Vertical AM 00h->Horizontal AM
	write_c(0xdb);        //VCOM  deselect  level  mode  
	write_c(0x30);          
	write_c(0xad);        //master  configuration
	write_c(0x00);          
	write_c(0xa4);        //out  follows  RAM  content  
	write_c(0xa6);        //set  normal  display  
	write_c(0xaf);        //display  on

	//kinda explained 9.1.3	
	write_c(0xB0);		//Set page Start Address for page Addressing Mod
	write_c(0x00);   	//Set Lower Column Start Address for page Addressing
	write_c(0x10);		//Set Higher Column Start Address for page Addressing Mode
	
	OLED_clear_all();
	OLED_home();

} 

void OLED_print_char(char c){
	for(int i = 0; i < FONTWIDTH; i++){
		//In ASCII spac or ' ' is 32. So taking the char and subtracting it with ' '
		//will give us the "correct" symbol from fonts.h 
		write_s(pgm_read_byte(&(font8[c - ' '][i])));
	}
}

void OLED_print(char* word){	//To print a whole word
	int i = 0;
	while(word[i] != '\0'){
		OLED_print_char(word[i]);
		i++;
	}
}

void OLED_home(void) {
	gen_page = 0;
	gen_col = 0;
	OLED_pos(0, 0);
}

void OLED_goto_line(uint8_t line) {
	gen_page = line;
	gen_col = 0;
	if (line < 8){
		write_c(0xB0 + line);		//Set page 0-7 (B0h to B7h)
		write_c(0x00);				//Lower nibble of start column address (00h to 0Fh)	
		write_c(0x10);				//Upper nibble of start column address (10h to 1Fh)
	}
}

void OLED_goto_column(uint8_t column) {
	gen_col = column;
	if (column < 128){
		uint8_t lower_nibble = (0x0F & column); 
		uint8_t upper_nibble = (0x10 + (0x0F & (column >> 4)));

		write_c(lower_nibble);		//Set first 4 bits of column address
		write_c(upper_nibble);		//Set last 4 bits of column address
	}
}

void OLED_pos(uint8_t line, uint8_t column) {

	OLED_goto_line(line);
	OLED_goto_column(column);	
}

void OLED_clear_line(uint8_t line) {
	OLED_goto_line(line);
	for (uint8_t i = 0; i < 128; i++){
		write_s(0x00);	//Set bits to 0
	}
}

void OLED_clear_all(void) {
	for(int p = 0; p < 8; p++){ //p for page (clears all pages)
		OLED_clear_line(p);
	}
}

void OLED_set_brightness(uint8_t lvl){
	write_c(0x81);		//Set contrast level
	write_c(lvl);		//to the resquested level (It must be from 00h to FFh)
}

void OLED_print_arrow(uint8_t row, uint8_t col){
	OLED_pos(row, col);
	write_s(0b00011000);
	write_s(0b00011000);
	write_s(0b01111110);
	write_s(0b00111100);
	write_s(0b00011000);
}

void OLED_clear_arrow(uint8_t row, uint8_t col){
	OLED_pos(row, col);
	write_s(0b00000000);
	write_s(0b00000000);
	write_s(0b00000000);
	write_s(0b00000000);
	write_s(0b00000000);
}

void OLED_screen_Saver() {
	OLED_clear_all();
	for(int p=0; p<8; p++) {
		OLED_pos(p, 0);
		for(int c=0; c<128; c++) {
			write_s(pgm_read_byte(&(screenSaver[p][c])));
		}
	}
}


void write_s(uint8_t data){
	frame[gen_page][gen_col] = data;
	gen_col++;
	if(gen_col >= 128){
		gen_col = 0;			// Page addressing mode
	}
}

void OLED_update(){
	//_delay_ms_(1/0.060); 		// update frequency
	for (int r = 0; r < 8; r++){
		OLED_pos(r,0);
		for (int c = 0; c < 128; c++){
			write_d(frame[r][c]);
		}
	}
}

void OLED_frame_fill(){
	for (uint8_t r = 0; r < 8; r++){
		for (uint8_t c = 0; c < 128; c++){
			frame[r][c] = 11;
		}
	}
}
