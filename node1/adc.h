#ifndef ADC_H
#define ADC_H

#include "uart.h"

void ADC_init(void);
uint8_t ADC_read(uint8_t channel);

#endif //ADC_H