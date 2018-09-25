#include <stdio.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>

#define adc_init_address 0x1400

void ADC_init(void){
	//Happens in sram init too
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
	
	// Button input
	DDRE &= ~(1<<PE0);

	// Disable global interrupts
	//cli();
	
	// Interrupt on risingedge PE0 
	EMCUCR |= (1<<ISC2);

	// Enable interrupt on PE0
	GICR |= (1<<INT2);

	// Enable global interrupts
	//sei();

	// Set sleep mode to power save
	//set_sleep_mode(SLEEP_MODE_PWR_SAVE);


}


uint8_t ADC_read(uint8_t channel){
	volatile uint8_t *adc = (uint8_t *) adc_init_address;
	_delay_us(1);		//Courtesy time to ensure ADC doesnt get stuck

	adc[channel] = channel;
	
	while (PINE & (1<<PE0)); //We wait until ADC conversion process finishes (supposedly 40us)
	
	/*
	channel 1 = 0100 0x4
	channel 2 = 0101 0x5
	channel 3 = 0110 0x6
	channel 4 = 0111 0x7
	*/
	
	_delay_us(60);
		
	return *adc;
}