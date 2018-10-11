#ifndef ADC_H
#define ADC_H

#include "uart.h"	//USART initialization to do printf

void ADC_init(void);	//ADC initialization
uint8_t ADC_read(uint8_t channel);	//Reading of ADC channels

#endif //ADC_H