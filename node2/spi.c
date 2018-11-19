#include <avr/io.h>
#include <stdio.h>

#include "spi.h"		//Prototypes of functions	
#include "uart.h"

#define CAN_CS DDB7		//Chip Select pin

void SPI_init(void) {
	//Set data directions (1=output, 0=input) - inside DDRB register
	DDRB = (1<<DDB1)|(1<<DDB2)|(0<<DDB3)|(1<<CAN_CS)|(1<<DDB0);	//DDB7 = SS (out), DDB3 = MISO (in), DDB2 = MOSI (out), DDB1 = SCK (out)
	
	//Define SPI comm. SPE (bit 6), MSTR (bit 4), SPR1/SPR0 (bits 1 and 0), inside the register SPCR
	//SPE=1 to enable SPI comm, MSTR=1 to be Master (=0 Slave), SPR0/SPR1 to define clock rate (FOSC/16 chosen)
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_write(char cData) {
	SPDR = cData;	//SPDR register (to start transmission) updated. (wait transmission complete)
	
	while(!(SPSR & (1<<SPIF)));	//Bit SPIF=1 when transmission finishes (SPSR register)
}

char SPI_read(void) {
	//SPDR = 0x00;		//Set dummy byte in data register (to clean the buffer, necessary action)
	SPI_write(0x1);
	
	while(!(SPSR & (1<<SPIF)));	//Waits until current transmission finishes
	return SPDR;
}

void SPI_select(void){
	PORTB &= ~(1 << CAN_CS);
}

void SPI_deselect(void){
	PORTB |= (1 << CAN_CS);
}


/* 	dmesg --follow
	lsusb
	ttyACM0 = USB
*/