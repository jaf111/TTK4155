#ifndef PID_H
#define PID_H

void pid_init(uint8_t pid_type, uint16_t frequency);	//PID initializaton & constants calculation
uint8_t pid_controller(uint8_t setpoint);	//Calculate the corrected output

#endif //PID_H