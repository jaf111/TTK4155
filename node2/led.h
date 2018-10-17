#ifndef LED_H
#define LED_H

//@brief Initialize LED; necessary to call only once
void led_init();	//Using Port B, pin PB0 on ATmega162

//@brief Turn LED on
void led_turn_on();

//@brief Turn LED off
void led_turn_off();

#endif // LED_H