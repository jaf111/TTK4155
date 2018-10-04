#include <util/delay.h>
#include <avr/io.h> 
#include <stdio.h> 

#include"spi.h"


void SPI_Masterinit(void){
	// Set MISO output, all others input
	DDRB = (1<<DDB5) | (1<<DDB7);			// DDB6 = MOSI, DDB7 = SCK
	// Enable SPI
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

char SPI_MasterTransmit(char cData){

	// Start transmission
	SPDR = cData;
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)));
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