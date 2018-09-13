#include <stdio.h>
#include <avr/io.h> 

#define adc_init_address 0x1400

void ADC_init(void){
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);

	//Interrupt enable
	//DDRD |= (1 << DDD0);
}

void ADC_read(uint8_t channel){
	volatile char *ext_ram = (char *) sram_init_address;
}