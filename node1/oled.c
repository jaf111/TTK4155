/*
#include <stdio.h>			//Standard constants and functions for C (printf..., scanf...) 
#include <avr/io.h> 		//Specific IO for AVR micro (all registers defined inside)
#include <avr/interrupt.h>	//Interruptions for AVR micro
#include <avr/pgmspace.h>	//Interfaces to access data stored in program space (flash memory) of AVR
#include "oled.h"			//Prototype functions
#include "fonts.h"			//All characters to print in the OLED (saved in FLASH)
#include "sram.h"			//Functions to directly write into the SRAM

#define MAX_COLUMNS 128		//Number of columns in OLED
#define MAX_PAGES 8			//Width of used fonts

#define FONTWIDTH 8			//Width of used fonts

//The difference in command and start addresses (bit 9) is created to manage D/C pin in OLED
volatile uint8_t *oled_cmd = (uint8_t *) 0x1000; 	//OLED Command start address
volatile uint8_t *oled_data = (uint8_t *) 0x1200; 	//OLED Data start address

void write_c(uint8_t cmd) {		//To write a (configuration) command into the OLED
	*oled_cmd = cmd;
}

void write_d(uint8_t cmd) {		//To print data into the OLED
	*oled_data = cmd;
}

void OLED_init(void) {	//OLED display initialization
	write_c(0xae);	//Display is switch OFF
	write_c(0xa1);	//Segment remap (A1=Aligned to the right / A0=Aligned to the left)
	write_c(0xda);	//Sets COM signals pin configuration to match OLED panel hardware layout
	write_c(0x12);		//Value. Alternative
	write_c(0xc8);	//Sets the scan direction of the COM output: COM63~COM0
	write_c(0xa8);	//Switches the default multiplex mode (63) to any multiplex ratio
	write_c(0x3f);  	//Value. From 0x10 (16) to 0x3f (63)
	write_c(0xd5);	//Display divide ratio/osc & freq. mode 
	write_c(0x80);		//Value. [7:4]-> Oscillator freq , [3:0]->Display clock
	write_c(0x81);	//Contrast control
	write_c(0x50);		//Value. From 00h (0%) to FFh (100%)
	write_c(0xd9);	//Set Pre-charge period
	write_c(0x21);		//Value. The interval is counted in number of DCLK, where RESET equals 2 DCLKs
	write_c(0x20);	//Set Memory Addressing Mode (AM)
	write_c(0x02);		//Value. 02h->Page AM, 01h->Vertical AM, 00h->Horizontal AM
	write_c(0xdb);	//COM signal deselected voltage level. Adjusts the VCOMH regulator output.
	write_c(0x30);		//Value. 00h->~0.65xVcc, 20h->~0.77xVcc(RESET), 30h->~0.83xVcc
	write_c(0xad);	//Select internal Iref or external Iref to supply the system
	write_c(0x00);		//Value. 00h->External Iref, 01h->Internal Iref
	write_c(0xa4);	//Display outputs according to the GDDRAM contents
	write_c(0xa6);	//A6h->Normal (data 1/0-> pixel ON/OFF), A7h->Inverse (data 1/0-> pixel OFF/ON)
	write_c(0xaf);	//Display is switch ON

	//kinda explained 9.1.3	
	write_c(0xB0);		//Set page Start Address for page Addressing Mode
	write_c(0x00);   	//Set Lower Column Start Address for page Addressing Mode
	write_c(0x10);		//Set Higher Column Start Address for page Addressing Mode (NEED TO ASK ABOUT THIS)
	
	OLED_clear_all();	//All screen is cleared
	OLED_home();		//Pointer goes to the home position
}

void OLED_print_char(char ch) {		//To print JUST one character
	for(int i = 0; i < FONTWIDTH; i++){
		//In ASCII, space or ' ' is 32. So taking the char and subtracting it with ' '
		//will give us the "correct" symbol from fonts.h 
		write_d(pgm_read_byte(&(font8[ch - ' '][i])));		//pgm_read_byte(&()) is required to take data from FLASH mem
	}
}

void OLED_print_all(char* word) {	//To print the whole word/sentence (pointer where char starts)
	int i = 0;
	while(word[i] != '\0') {		//If the received character is different from NULL (\0),
		OLED_print_char(word[i]);	//such character is printed on the OLED
		i++;
	}
}

void OLED_home(void) {	//It goes to position 0,0 in OLED
	OLED_pos(0, 0);
}

void OLED_goto_line(uint8_t line) {	//To go to a specific line in OLED
	//For page addressing mode, it needs to check if we are on a valid page
	//OLED_home();

	if (line < MAX_PAGES) {
		write_c(0xB0 + line);	//Set line/page 0-7 (requested format B0h to B7h)
		
		//We also go to the beginning of the column again
		write_c(0x00);	//Lower nibble of start column address (00h)	
		write_c(0x10);	//Upper nibble of start column address (10h)
	}
}

void OLED_goto_column(uint8_t column) {	//To go to a specific column in OLED
	if (column < MAX_COLUMNS) {			//Go to the requested column
		uint8_t lower_nibble = (0x0F & column); 	//Set first 4 bits of column address
		uint8_t upper_nibble = 0x10 + (0x0F & (column >> 4));	//Set last 4 bits of column address	

		write_c(lower_nibble); 	//Lower nibble of requested column (requested format 00h to 0Fh)
		write_c(upper_nibble);	//Upper nibble of requested column (requested format 10h to 1Fh)
	}
}

void OLED_pos(uint8_t line, uint8_t column) {	//Go to requested position
	OLED_goto_line(line);		//Go to the requested line/page
	OLED_goto_column(column);	//Go to the requested column
}

void OLED_clear_line(uint8_t line) {	//Clears an entire line/page
	OLED_goto_line(line);	//To be sure we are in the requested line/page

	for (uint8_t i=0; i<MAX_COLUMNS; i++) {		//There are a total of 128 columns	
		write_d(0x00);	//The existing 8 bits per column are set to 0
	}
}

void OLED_clear_all(void) {		//Clears the whole OLED
	for(int p=0; p<MAX_PAGES; p++) {	//There are a total of 8 lines/pages
		OLED_clear_line(p);		//In every line, it clears all columns
	}
}

void OLED_set_brightness(uint8_t lvl) {	//Define brightness level
	write_c(0x81);		//Set contrast level
	write_c(lvl);		//to the requested level (requested format from 00h to FFh)
}

void OLED_print_arrow(uint8_t row, uint8_t col) {
	OLED_pos(row, col);		//To print an arrow in the requested position
	write_d(0b00011000);
	write_d(0b00011000);
	write_d(0b01111110);
	write_d(0b00111100);
	write_d(0b00011000);
}

void OLED_clear_arrow(uint8_t row, uint8_t col){
	OLED_pos(row, col);		//To clear an arrow in the requested position
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
}

void OLED_screen_Saver() {	//Prints a complete screen saver
	OLED_clear_all();		//All display is cleared first
	for(int p=0; p<MAX_PAGES; p++) { //Printing from up and down, and left to right
		OLED_pos(p, 0);
		for(int c=0; c<MAX_COLUMNS; c++) {
			write_d(pgm_read_byte(&(screenSaver[p][c])));
		}
	}
}
*/


#include <stdio.h>			//Standard constants and functions for C (printf..., scanf...) 
#include <avr/io.h> 		//Specific IO for AVR micro (all registers defined inside)
#include <avr/interrupt.h>	//Interruptions for AVR micro
#include <avr/pgmspace.h>	//Interfaces to access data stored in program space (flash memory) of AVR
#include "oled.h"			//Prototype functions
#include <util/delay.h>	//Functions for busy-wait delay loops
#include "fonts.h"			//All characters to print in the OLED (saved in FLASH)
#include "sram.h"			//Functions to directly write into the SRAM

#define MAX_COLUMNS 128		//Number of columns in OLED
#define MAX_PAGES 8			//Width of used fonts

#define FONTWIDTH 8			//Width of used fonts

//The difference in command and start addresses (bit 9) is created to manage D/C pin in OLED
volatile uint8_t *oled_cmd = (uint8_t *) 0x1000; 	//OLED Command start address
volatile uint8_t *oled_data = (uint8_t *) 0x1200; 	//OLED Data start address

static uint8_t gen_page, gen_col = 0;

volatile uint8_t *frame_addr = (uint8_t*)0x1800;

#define frame ( (uint8_t(*)[128]) (frame_addr) )		// Two dimensional matrix representation of OLED screen in SRAM

void write_c(uint8_t cmd) {		//To write a (configuration) command into the OLED
	*oled_cmd = cmd;
}

void write_d(uint8_t cmd) {		//To print data into the OLED
	*oled_data = cmd;
}

void OLED_init(void) {	//OLED display initialization
	write_c(0xae);	//Display is switch OFF
	write_c(0xa1);	//Segment remap (A1=Aligned to the right / A0=Aligned to the left)
	write_c(0xda);	//Sets COM signals pin configuration to match OLED panel hardware layout
	write_c(0x12);		//Value. Alternative
	write_c(0xc8);	//Sets the scan direction of the COM output: COM63~COM0
	write_c(0xa8);	//Switches the default multiplex mode (63) to any multiplex ratio
	write_c(0x3f);  	//Value. From 0x10 (16) to 0x3f (63)
	write_c(0xd5);	//Display divide ratio/osc & freq. mode 
	write_c(0x80);		//Value. [7:4]-> Oscillator freq , [3:0]->Display clock
	write_c(0x81);	//Contrast control
	write_c(0x50);		//Value. From 00h (0%) to FFh (100%)
	write_c(0xd9);	//Set Pre-charge period
	write_c(0x21);		//Value. The interval is counted in number of DCLK, where RESET equals 2 DCLKs
	write_c(0x20);	//Set Memory Addressing Mode (AM)
	write_c(0x02);		//Value. 02h->Page AM, 01h->Vertical AM, 00h->Horizontal AM
	write_c(0xdb);	//COM signal deselected voltage level. Adjusts the VCOMH regulator output.
	write_c(0x30);		//Value. 00h->~0.65xVcc, 20h->~0.77xVcc(RESET), 30h->~0.83xVcc
	write_c(0xad);	//Select internal Iref or external Iref to supply the system
	write_c(0x00);		//Value. 00h->External Iref, 01h->Internal Iref
	write_c(0xa4);	//Display outputs according to the GDDRAM contents
	write_c(0xa6);	//A6h->Normal (data 1/0-> pixel ON/OFF), A7h->Inverse (data 1/0-> pixel OFF/ON)
	write_c(0xaf);	//Display is switch ON

	//kinda explained 9.1.3	
	write_c(0xB0);		//Set page Start Address for page Addressing Mode
	write_c(0x00);   	//Set Lower Column Start Address for page Addressing Mode
	write_c(0x10);		//Set Higher Column Start Address for page Addressing Mode (NEED TO ASK ABOUT THIS)
	
	OLED_clear_all();	//All screen is cleared
	OLED_home();		//Pointer goes to the home position
}

void OLED_print_char(char ch) {		//To print JUST one character
	for(int i = 0; i < FONTWIDTH; i++){
		//In ASCII, space or ' ' is 32. So taking the char and subtracting it with ' '
		//will give us the "correct" symbol from fonts.h 
		write_s(pgm_read_byte(&(font8[ch - ' '][i])));		//pgm_read_byte(&()) is required to take data from FLASH mem
	}
}

void OLED_print_all(char* word) {	//To print the whole word/sentence (pointer where char starts)
	int i = 0;
	while(word[i] != '\0') {		//If the received character is different from NULL (\0),
		OLED_print_char(word[i]);	//such character is printed on the OLED
		i++;
	}
}

void OLED_home(void) {	//Pointer goes to position 0,0 in OLED
	gen_page = 0;
	gen_col = 0;
	OLED_pos(0, 0);
}

void OLED_goto_line(uint8_t line) {	//To go to a specific line in OLED
	//For page addressing mode, it needs to check if we are on a valid page
	//OLED_home();
	gen_page = line;
	gen_col = 0;
	if (line < MAX_PAGES) {
		write_c(0xB0 + line);	//Set line/page 0-7 (requested format B0h to B7h)
		
		//We also go to the first column again
		write_c(0x00);	//Lower nibble of start column address (00h)	
		write_c(0x10);	//Upper nibble of start column address (10h)
	}
}

void OLED_goto_column(uint8_t column) {	//To go to a specific column in OLED
	gen_col = column;
	if (column < MAX_COLUMNS) {			//Go to the requested column
		uint8_t lower_nibble = (0x0F & column); 	//Set first 4 bits of column address
		uint8_t upper_nibble = 0x10 + (0x0F & (column >> 4));	//Set last 4 bits of column address	

		write_c(lower_nibble); 	//Lower nibble of requested column (requested format 00h to 0Fh)
		write_c(upper_nibble);	//Upper nibble of requested column (requested format 10h to 1Fh)
	}
}

void OLED_pos(uint8_t line, uint8_t column) {	//Go to requested position
	OLED_goto_line(line);		//Go to the requested line/page
	OLED_goto_column(column);	//Go to the requested column
}

void OLED_clear_line(uint8_t line) {	//Clears an entire line/page
	OLED_goto_line(line);	//To be sure we are in the requested line/page

	for (uint8_t i=0; i<MAX_COLUMNS; i++) {		//There are a total of 128 columns	
		write_s(0x00);	//The existing 8 bits per column are set to 0
	}
}

void OLED_clear_all(void) {		//Clears the whole OLED
	for(int p=0; p<MAX_PAGES; p++) {	//There are a total of 8 lines/pages
		OLED_clear_line(p);		//In every line, it clears all columns
	}
}

void OLED_set_brightness(uint8_t lvl) {	//Define brightness level
	write_c(0x81);		//Set contrast level
	write_c(lvl);		//to the requested level (requested format from 00h to FFh)
}

void OLED_print_arrow(uint8_t row, uint8_t col) {
	OLED_pos(row, col);		//To print an arrow in the requested position
	write_s(0b00011000);
	write_s(0b00011000);
	write_s(0b01111110);
	write_s(0b00111100);
	write_s(0b00011000);
}

void OLED_clear_arrow(uint8_t row, uint8_t col){
	OLED_pos(row, col);		//To clear an arrow in the requested position
	write_s(0b00000000);
	write_s(0b00000000);
	write_s(0b00000000);
	write_s(0b00000000);
	write_s(0b00000000);
}

void OLED_screen_Saver() {	//Prints a complete screen saver
	OLED_clear_all();		//All display is cleared first
	for(uint8_t p=0; p<MAX_PAGES; p++) { //Printing from up and down, and left to right
		//OLED_goto_line(p);
		gen_page = p;
		for(uint8_t c=0; c<MAX_COLUMNS; c++) {
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
	for (uint8_t r = 0; r < 8; r++){
		OLED_goto_line(r);
		for (uint8_t c = 0; c < 128; c++){
			write_d(frame[r][c]);
		}
	}
}

void OLED_frame_fill(uint8_t data){
	for (uint8_t r = 0; r < 8; r++){
		for (uint8_t c = 0; c < 128; c++){
			frame[r][c] = data;
		}
	}
}

void OLED_frame_char_fill(char c){
	//OLED_print_all("HELLOHELLOA");
	for (uint8_t r = 0; r < 8; r++){
		OLED_goto_line(r);
		OLED_print_all("HELLOOOOOOOJAJAES");
	}
	//OLED_goto_line(3);
	//fprintf(UART_p,"%d",gen_page);
}