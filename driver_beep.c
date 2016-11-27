#include "driver_beep.h"
#include <avr/io.h>


void beep_on( )
{
	DDRE |= _BV(BEEP);	
	PORTE &= ~_BV(BEEP);
}

void beep_off( )
{
	DDRE |= _BV(BEEP);	
	PORTE |= _BV(BEEP);	
}



