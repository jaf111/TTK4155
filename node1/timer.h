#ifndef TIMER_H
#define TIMER_H

uint8_t timer_set_prescaler(uint16_t presc_value);
void timer1_init(uint16_t prescaler, uint16_t frequency);

#endif // TIMER_H