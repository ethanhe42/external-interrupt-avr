#include "driver_digitron.h"
#include <avr/io.h>
#include <util/delay.h>

unsigned char get_code(unsigned char c)
{
	switch(c)
	{
		case '0':return 0xc0;
		case '1':return 0xf9;
		case '2':return 0xa4;
		case '3':return 0xb0;
		case '4':return 0x99;
		case '5':return 0x92;
		case '6':return 0x82;
		case '7':return 0xf8;
		case '8':return 0x80;
		case '9':return 0x90;
		default: return 0xff;
	}
}
uint8_t code[16] = { 0xC0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e };
void DIG_Init() {
    PORTB = ~PB_MASK;
    DDRB = PB_MASK;
    PORTG &= 0x00;
    DDRG |= _BV(DIG_CS1) | _BV(DIG_CS2);
}

void showchar(int pos, int c, int time){
DIG_Init();
	PORTG |= _BV(DIG_CS2);
	PORTG &= ~_BV(DIG_CS1);
    PORTB = code[c];

	PORTG |= _BV(DIG_CS1);
	PORTG &= ~_BV(DIG_CS2);
    PORTB = 1<<(7-pos);

	PORTG &= ~_BV(DIG_CS1);
	PORTG &= ~_BV(DIG_CS2);
    _delay_ms(time);
}

void print(int num, int mode, int time) {
	int c[7];
	int i,rest,tmp, s;
	tmp = num;
	int wait = 0;
	for (i=0; i <7; i++){
		if (wait == 1) {
			_delay_ms(time);
			continue;}
		rest = tmp % mode;
		showchar(i, rest, time);
		s = tmp / mode;
		if ( s == 0) {
			wait = 1;
		}
		tmp = s;
	}
}

void digitron_on(unsigned char digit_code, unsigned char pos)
{
	DDRG |= _BV(DIG_CS1);
	DDRG |= _BV(DIG_CS2);
		
	PORTG |= _BV(DIG_CS1);
	PORTG &= ~_BV(DIG_CS2);	
	DDRB = 0xff;
	PORTB = _BV(pos - 1); 

	PORTG &= ~_BV(DIG_CS1);	
	PORTG |= _BV(DIG_CS2);	
	PORTB = digit_code;	
	PORTG &= ~_BV(DIG_CS2);	
}

