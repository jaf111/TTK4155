#ifndef PWM_H
#define PWM_H


void PWM_init(void);	//Initialisation
void PWM_Left(void);
void PWM_Center(void);
void PWM_Right(void);
uint8_t TIM16_ReadTCNT1(void);
void TIM16_WriteICR1(uint16_t i);
void TIM16_WriteOCR1A(uint16_t i);


#endif // PWM_H