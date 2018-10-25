#ifndef ADC_H
#define ADC_H

#include "uart.h"	//USART initialization to do printf

void ADC_init(void);	//ADC initialization
uint16_t ADC_read();	//Reading of ADC

#endif //ADC_H