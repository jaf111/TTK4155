#include <util/delay.h>	//Functions for busy-wait delay loops
#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include <stdio.h> 		//Standard constants and functions for C (printf..., scanf...)

#include "spi.h"		//Prototypes of functions here defined		

void SPI_init(void) {	//SPI initialization (as a Master)
	//Set data directions (1=output, 0=input) - inside DDRB register
	DDRB = (1<<DDB4)|(1<<DDB5)|(0<<DDB6)|(1<<DDB7);	//DDB4 = SS (out), DDB5 = MISO (out), DDB6 = MOSI (in), DDB7 = SCK (out)
	//Define SPI comm. SPE (bit 6), MSTR (bit 4), SPR1/SPR0 (bits 1 and 0), inside the register SPCR
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); //SPE=1 to enable SPI comm, MSTR=1 to be Master (=0 Slave), SPR0/SPR1 to define clock rate (FOSC/16 chosen)
}

void SPI_write(char cData) {	//Sends a message to the slave through SPI comm
	SPDR = cData;				//SPDR register (to start transmission) is updated
	//Wait for transmission complete
	while(!(SPSR & (1<<SPIF)));	//Bit SPIF=1 when transmission finishes (inside SPSR register - Status Register)
}

char SPI_read(void) {	//Reads a message from the slave through SPI comm
	SPDR = 0x00;		//Set dummy byte in data register (to clean the buffer, necessary action)
	//Wait for transmission complete
	while(!(SPSR & (1<<SPIF)));	//Waits until the current transmission finishes
	return SPDR;		//Returns the new value of data registers (SPDR)
}