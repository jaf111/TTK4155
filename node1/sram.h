#ifndef SRAM_H
#define SRAM_H

#include "uart.h"		//Prototype functions (only to allow printf() function!)

void SRAM_init(void);		//External SRAM enabled
void SRAM_write(unsigned int data, unsigned int address);	//Write to external SRAM
unsigned int SRAM_read(unsigned int address);	//Read from external RAM
void SRAM_test(void);		//(Write/read) test for external SRAM

#endif //SRAM_H