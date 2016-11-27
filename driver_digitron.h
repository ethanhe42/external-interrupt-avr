#ifndef DRIVER_DIGITRON_H
#define DRIVER_DIGITRON_H

#define DIG_CS1 PG3
#define DIG_CS2 PG4	
#define PB_MASK 0xFF
#define LED_CS PC5
unsigned char get_code(unsigned char c)	;
void digitron_on(unsigned char digit_code, unsigned char pos) ;	

#endif 

