#include <util/delay.h>
#include <avr/io.h> 
#include <stdio.h> 

#include "spi.h"


void SPI_init(void) {
	// Set SS & MOSI as outputs, all others inputs
	DDRB = (1<<DDB4) | (1<<DDB5) | (0<<DDB6) | (1<<DDB7);	// DDB4 = SS, DDB5 = MISO, DDB6 = MOSI, DDB7 = SCK
	// Enable SPI
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_write(char cData) {
	// Start transmission
	SPDR = cData;
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)));
}

char SPI_read(void) {			
	
	SPDR = 0x00;
	// Wait for reception complete
	while(!(SPSR & (1<<SPIF)));
	// Return data registers
	return SPDR;
}

/*
void SPI_SlaveInit(void){
	// Set MISO output, all others input
	DDR_SPI = (1<<DD_MISO);
	// Enable SPI
	SPCR = (1<<SPE);
}

char SPI_slaveRecieve(void){			
	// Wait for reception complete
	while(!(SPSR & (1<<SPIF)));
	// Return data registers
	return SPDR;
}*/