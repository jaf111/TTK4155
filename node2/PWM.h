#ifndef PWM_H
#define PWM_H


void PWM_init(uint16_t prescaler, uint16_t frequency);	//PWM initialisation
void PWM_MaxLeft(void);
void PWM_Center(void);
void PWM_MaxRight(void);
void Modify_PWM(uint8_t width);


#endif // PWM_H