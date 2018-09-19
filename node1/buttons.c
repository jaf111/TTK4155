#include <avr/io.h>
#include "buttons.h"

//Using Port B, pin PB0 on ATmega162

void button_init(){
	DDRB |= (1 << DDB0);
	DDRB |= (1 << DDB1);

}
