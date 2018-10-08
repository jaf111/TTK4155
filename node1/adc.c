#include <stdio.h>			//Standard constants and functions for C (printf..., scanf...)
#include <avr/io.h> 		//Specific IO for AVR micro (all registers defined inside)
#include <avr/interrupt.h>	//Interruptions for AVR micro
#include <util/delay.h>		//Functions for busy-wait delay loops

#include "adc.h"			//Prototypes of functions here defined

#define adc_init_address 0x1400		//ADC address (just to inform the GAL to update Chip Select [CS])

void ADC_init(void){
	//Happens in sram init too
	MCUCR |= (1 << SRE);	//SRE: External SRAM/XMEM Enable (bit 7 of register MCUCR). Rest unchanged
	SFIOR |= (1 << XMM2);	//XMM2: External Memory High Mask [PC7 - PC4] (bit 5 of register SFIOR)
	
	// Button input
	DDRE &= ~(1<<PE0);		//Enabled pin 0 (PE0) of port E (register DDRE)

	// Disable global interrupts
	//cli();
	
	// Configuration: Interrupt on rising edge PE0 (minimum pulse of 50ns). Rest unchanged
	EMCUCR |= (1<<ISC2);	//ISC2: Interrupt Sense Control 2 (bit 0 of EMCUCR).

	// Enable interrupt on PE0
	GICR |= (1<<INT2);		//INT2: External Interrupt Request 2 (bit 5 of GICR).

	// Enable global interrupts
	//sei();

	// Set sleep mode to power save
	//set_sleep_mode(SLEEP_MODE_PWR_SAVE);
}

uint8_t ADC_read(uint8_t channel) {
	volatile uint8_t *adc = (uint8_t *) adc_init_address;	//A new variable is created, located in the defined position/address 
	_delay_us(1);		//Courtesy time to ensure ADC does not get stuck

	adc[channel] = channel;
	
	//While status of PINE0 (bit 0, managed by PE0) is 0, nothing is done.
	while (PINE & (1<<PE0));	//We wait until ADC conversion process finishes (supposedly 40us according to datasheet)
	
	_delay_us(60);	 //Delay between ADC lectures (at least 600ns according to datasheet)
	
	return *adc;
}