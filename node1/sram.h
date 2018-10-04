#ifndef SRAM_H
#define SRAM_H

#include "uart.h"

#define sram_init_address 0x1800

void SRAM_init(void);

void SRAM_write(unsigned int data, unsigned int address);

unsigned int SRAM_read(unsigned int address);

void SRAM_test(void);

#endif //SRAM_H