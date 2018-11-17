#include <stdio.h>		//Standard constants and functions for C (printf..., scanf...) 
#include <avr/io.h> 	//Specific IO for AVR micro (all registers defined inside)
#include "uart.h"		//Necessary to enable the new fprintf

#define sram_init_address 0x1800	//SRAM address (just to inform the GAL to update Chip Select [CS])

void SRAM_init(void) {		//External SRAM memory enabled for AT mega162
	//EMCUCR &= ~(1 << SRL2)|( 1<<SRL1 )|(1 << SRL0);	//They are initially 0, so no point setting them
	MCUCR |= (1 << SRE);	//SRE: External SRAM/XMEM Enable (bit 7 of register MCUCR). Rest unchanged
	SFIOR |= (1 << XMM2);	//XMM2: External Memory High Mask [PC7 - PC4] (bit 5 of register SFIOR)
}

void SRAM_write(uint8_t data, unsigned int address) {	//Address and value to be written in RAM
	volatile char *ext_ram = (char *) sram_init_address;	// Start address for the SRAM
	ext_ram[address] = data; 	//Value is assigned to the defined address

	fprintf(UART_p, "SNT data: %04u, addr: %04X \n\r", data, address);
}

uint8_t SRAM_read(unsigned int address) {	//Value read from the requested address
	volatile char *ext_ram = (char *) sram_init_address;	// Start address for the SRAM
	uint8_t data = ext_ram[address]; 		//- sram_init_address

	fprintf(UART_p, "RCV data: %04u, addr: %04X \n\r", data, address);
	
	return data;
}

void SRAM_test(void) {		//Test to write and read in every position of the external RAM memory
	volatile char *ext_ram = (char *) sram_init_address; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;		//The complete address size dedicated to external SRAM
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	fprintf(UART_p, "Start SRAM test:%d \n\r");
	//printf("Starting SRAM test...\n\r");

	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	
	for (uint16_t i = 0; i < ext_ram_size; i++) {	//A random value is written, read again
		uint8_t some_value = rand();				//and finally compared
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		
		if (retreived_value != some_value) {
			fprintf(UART_p, "Write error: ext_ram[%d]=%02X (should be %02X)\n\r", i, retreived_value, some_value);
			//printf("Write phase error: ext_ram[%d]=%02X (should be %02X)\n\r", i, retreived_value, some_value);
			write_errors++;
		}
	}

	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed); // reset the PRNG to the state it had before the write phase
	
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		
		if (retreived_value != some_value) {
			fprintf(UART_p, "Retriev error: ext_ram[%4d]=%02X (should be %02X)\n\r", i, retreived_value, some_value);
			//printf("Retriev error: ext_ram[%4d]=%02X (should be %02X)\n\r", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	fprintf(UART_p, "SRAM test done with\n\r%4d errors (WR phase) &\n\r%4d errors (RETR phase)\n\r", write_errors, retrieval_errors);
	//printf("SRAM test completed with\n\r%4d errors in write phase and\n\r%4d errors in retrieval phase \n \n\r", write_errors, retrieval_errors);
}