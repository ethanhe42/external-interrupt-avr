/**********************************************
** �ļ�����interrupt.c
** ���ܣ��ⲿ�жϷ������INT4--INT7�ֱ�ִ����
**       �����ܳ���
** ˵������Ҫ�����ĸ����ܳ���
***********************************************/
#include "led.h"
#include "driver_beep.h"
#include "driver_digitron.h"
#include "driver_lcd.h"
#include <avr/interrupt.h>
#include <util/delay.h>

ISR (INT4_vect )  //�ⲿ�ж�  INT4            
{ 
	unsigned char i = 0;
	unsigned char status = 32;
	unsigned char string41[] = "    INT4����    ";
	unsigned char string42[] = "   2011-06-01   ";
	const struct Led_status led_status[] = {
		{0x00, 100},{0x01, 300},{0x02, 100},{0x03, 100},
		{0x04, 100},{0x05, 100},{0x06, 100},{0x07, 100},
		{0x08, 100},{0x09, 100},{0x0A, 100},{0x0B, 300},
		{0x0C, 100},{0x0D, 100},{0x0E, 100},{0x0F, 100},
		{0x0F, 100},{0x00, 100},{0x10, 300},{0x20, 100},
		{0x30, 100},{0x40, 100},{0x50, 100},{0x60, 100},
		{0x70, 100},{0x80, 100},{0x90, 100},{0xA0, 100},
		{0xB0, 300},{0xC0, 100},{0xD0, 100},{0xE0, 100},
		{0xF0, 100},{0xF0, 100},
	};
	lcd_write_line(LCD_LINE4_START, string41);
	for(i = 0; i < status; ++i)
	{
		light_led(led_status[i].status); //��Ԥ��״̬����LED��
	
		#ifndef DEBUG_LED
		_delay_ms(led_status[i].delay);	//��ÿ��״̬��Ԥ��ʱ�������ӳ�
		#endif
	}

	light_led(0xff);	//Ϩ��8��LED��
	lcd_write_line(LCD_LINE4_START, string42);
}

ISR (INT5_vect )	 //�ⲿ�ж�  INT5
{ 
	unsigned char string41[] = "    INT5����";
	unsigned char string42[] = "   2011-06-01   ";
	unsigned char i = 0;

	lcd_write_line(LCD_LINE4_START, string41);

	for (i=0;i<50;i++){
			int j;
			for (j=0;j<20;j++){
				print(i, 10,1);
				_delay_ms(1);
				//ledshow(i);
				_delay_ms(1);
			
			}
		}

	lcd_write_line(LCD_LINE4_START, string42);
} 

ISR (INT6_vect ) //�ⲿ�ж�  INT6
{ 
	unsigned char string41[] = "    INT6����    ";
	unsigned char string42[] = "   2011-06-01   ";
	unsigned char i = 0;

unsigned char* strs[] = {"adadw           ",
						 "LCD12864Һ������",
						 "    �����      ",
						 "  ��ѧ�뼼��ϵ  ",
						 "  hahhahhhhhhh  ",
						 "  hahhaaaahhhh  ",
						 "  ffffffffffff  ",
						 "  dddddddddddd  ",};

	for(int j=0;j<5;j++)
	{	
	println(strs[j]);
		if (j==8) j=0;
		_delay_ms(1000);
	}


	lcd_write_line(LCD_LINE4_START, string42);
} 

ISR (INT7_vect ) //�ⲿ�ж�  INT7
{ 
	unsigned char i = 0;
	unsigned char string41[] = "    INT7����    ";
	unsigned char string42[] = "   2011-06-01   ";

	lcd_write_line(LCD_LINE4_START, string41);
	for(i = 0; i < 10; ++i)	//��������������
	{
		beep_on();
		#ifndef DEBUG_LED
		_delay_ms(40);	//��ÿ��״̬��Ԥ��ʱ�������ӳ�
		#endif
		beep_off();
		#ifndef DEBUG_LED
		_delay_ms(100);	//��ÿ��״̬��Ԥ��ʱ�������ӳ�
		#endif
	}

	beep_on(); //����������
	#ifndef DEBUG_LED
	_delay_ms(1000);	//��ÿ��״̬��Ԥ��ʱ�������ӳ�
	#endif
	beep_off();
	lcd_write_line(LCD_LINE4_START, string42);
}
