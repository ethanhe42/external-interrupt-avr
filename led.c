#include "led.h"
#include <avr/io.h>



void light_led(unsigned char status)
{
	unsigned char i;

	DDRC |= _BV(PC5);	
    PORTC |= _BV(PC5);

	DDRB = 0xff;
	PORTB = status;	
    
	#ifndef DEBUG_LED
	for(i = 0 ; i < 5; i++ );
	#endif

	PORTC &= ~_BV(PC5);
}
