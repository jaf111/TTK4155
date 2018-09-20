#include <stdio.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>



volatile uint8_t *oled_cmd = (uint8_t *) 0x1000; //OLED Command start address
volatile uint8_t *oled_data = (uint8_t *) 0x1200; //OLED Data start address

unsigned page;
unsigned col;

void write_c(uint8_t cmd) {
	*oled_cmd = cmd;
}
void write_d(uint8_t cmd) {
	*oled_data = cmd;
}

void OLED_init() {
	write_c(0xae);        //display  off  
	write_c(0xa1);        //segment  remap  
	write_c(0xda);        //common  pads  hardware:  alternative  
	write_c(0x12);  
	write_c(0xc8);        //common output scan direction:com63~com0 
	write_c(0xa8);        //multiplex  ration  mode:63  
	write_c(0x3f);  
	write_c(0xd5);        //display divide ratio/osc. freq. mode 
	write_c(0x80);          
	write_c(0x81);        //contrast  control    
	write_c(0x50);          
	write_c(0xd9);        //set  pre-charge  period  
	write_c(0x21);          
	write_c(0x20);        //Set  Memory  Addressing  Mode  
	write_c(0x02);
	write_c(0xdb);        //VCOM  deselect  level  mode  
	write_c(0x30);          
	write_c(0xad);        //master  configuration    
	write_c(0x00);          
	write_c(0xa4);        //out  follows  RAM  content  
	write_c(0xa6);        //set  normal  display  
	write_c(0xaf);        //display  on

	/// The next ones must be confirmed!!!!!!!!!!
	/*write_c(0x00);   		//Set Lower Column Start Address for page Addressing
	write_c(0x10);		//Set Higher Column Start Address for page Addressing Mode
	write_c(0xB0);		//Set page Start Address for page Addressing Mod
	*/
} 

/*
void OLED_write_data(char A){
	write_d(A);
}



void OLED_home(){
	page = 0;
	col = 0;

	write_c(0x00); //
	write_c(0x10); //
	write_c(0x21); 
	write_c(0x22);
	write_c(0xB0);

	/*write_c(0x21);		//Set column address
	write_c(0xB0);		//to 0 (B0h)

	write_c(0x22);		//Set row address
	write_c(0x00);		//to 0 (00h)

}

//OLED_reset();

void OLED_goto_line(uint8_t page) {
	write_c(0x22);		//Set row address
	write_c(page);		//to the resquested page (It must be from 00h to 1Fh)
}

//OLED_clear_line(line);

void OLED_pos(uint8_t page, uint8_t column) {
	write_c(0x21);		//Set column address
	write_c(column);	//to the resquested column (It must be from B0h to B7h)

	write_c(0x22);		//Set page address
	write_c(page);		//to the resquested page (It must be from 00h to 1Fh)
}

OLED_write_data(char);

OLED_print(char*);

void OLED_set_brightness(uint8_t lvl) {
	write_c(0x81);		//Set contrast level
	write_c(lvl);		//to the resquested level (It must be from 00h to FFh)
}
*/