#ifndef SOLENOID_H
#define SOLENOID_H

void solenoid_init(void);	//Solenoid (PB6 [D12 Arduino]) initialization
void solenoid_ON(void);		//Solenoid activation
void solenoid_OFF(void);	//Solenoid deactivation
void solenoid_push(void);	//Solenoid push

#endif // SOLENOID_H