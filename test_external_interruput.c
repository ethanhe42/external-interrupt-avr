/**************************************************
** �ļ�����test_external_interruput.c         
** ���ܣ��ⲿ�жϹ��ܲ��Գ���LCD��ʾ���ܲ˵�
** ˵������Ҫ����LCD��ʾ����
*****************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#ifndef F_CPU 		//����ʱ��Ƶ�ʣ�����ֵ���������ʱ�ǳ���Ҫ
#define F_CPU 8000000UL      
#endif 
#include "driver_lcd.h"

void system_init()		//ϵͳ��ʼ��
{
	//�ر�8��LED��
	DDRB = 0xff;		//����PB�˿�Ϊ���
	DDRC |= _BV(PC5);	//����PC5Ϊ���
	PORTC |= _BV(PC5);	//��PC5Ϊ�ߵ�ƽ��ʹ��led����
	PORTB = 0xff;		//�ر�8��led��
	PORTC &= ~_BV(PC5);     //PC5�õͣ��ر�led��������

	//�ر��������ʾ
	DDRG |= _BV(PG3);	//����PG3Ϊ�����PG3��������ܵ�λѡ����������
	DDRG |= _BV(PG4);	//����PG4Ϊ�����PG4��������ܵĶ�����������
		
	PORTG |= _BV(PG3);	//ʹ�������λѡ��������
	PORTG &= ~_BV(PG4);	//�ر�������������
	DDRB = 0xff;		//���ö˿�PBΪ���
	PORTB = 0x00; 		//�������λ��

	PORTG &= ~_BV(PG3);	//�ر������λѡ��������		
	PORTG |= _BV(PG4);	//ʹ�ܶ���������
	PORTB = 0xff;		//�Ͷ���
	PORTG &= ~_BV(PG4);	//�رն���������

	//�رշ�����
	DDRE |= _BV(PE3);	
	PORTE |= _BV(PE3);	//���ȵ�·�Ͽ�������ֹͣ����
}

int main()
{
	system_init();		//ϵͳ��ʼ��
	LCD12864PortInit();		    //LCD�豸�ϵ��ʼ��

	lcd_write_line(LCD_LINE1_START, "  ������ͨ��ѧ  ");
	lcd_write_line(LCD_LINE2_START, "ATmega128 ��Ƭ��");
	lcd_write_line(LCD_LINE3_START, "  �ⲿ�ж���ʾ  ");
	lcd_write_line(LCD_LINE4_START, "   2011-06-01   ");
		
	SFIOR &= 0xfc;		//ʹ��ȫ����������
	DDRE &= 0x0f;		//PE4-PE7����Ϊ����
	PORTE |= 0xf0;		//PE4-PE7ʹ����������

	while(1) {
// INT4--INT7�ⲿ�жϳ�ʼ��
	    //EICRB = 0b10101010;	
		EICRB = 0b11111111;
	    //EICRB = 0x00;	    //����INT4--INT7Ϊ�͵�ƽ����
	    EIFR = 0xff;	    //����ⲿ�жϱ�־
	    EIMSK |= 0xf0;	    //����INT4--INT7�ⲿ�ж�
		sei();		        //ȫ�ֿ��ж�
	}
	
	return 0;
}

