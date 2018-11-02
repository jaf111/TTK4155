#ifndef PWM_H
#define PWM_H

uint8_t PWM_setPrescaler(uint16_t presc_value);		//Sets the prescaler in any PWM output
void PWM_PB5_init(uint16_t prescaler, uint16_t frequency);	//Init PWM in timer 1, channel A (PB5)
void PWM_PE3_init(uint16_t prescaler, uint16_t frequency);	//Init PWM in timer 3, channel A (PE3)
void Timer_PB7_init(uint16_t prescaler, uint16_t frequency);	//(internal) Timer of 8 bits, in PB7
void Set_PWMwidth(char* ch_PWM, uint8_t PWM_width);	//Modify pulse width of any PWM

#endif // PWM_H