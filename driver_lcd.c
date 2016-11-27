#include "driver_lcd.h"
#include <util/delay.h>
#include <avr/io.h>

void LCD12864BusyCheck(void)
{
    unsigned int uiTemp;
	uiTemp = 3000;
	
	DDRB = 0x00;             //PB����Ϊ����ڣ�׼����ȡ����
	PORTD &= ~(1 << RS);      //RS=0��������
	PORTD |= (1 << RW);    //RW=1����ָ��
	PORTD |= (1 << E);      //E=1��ʹ��
	
	while((0x80 & PINB) && (uiTemp--));   //���æ�źţ�ֱ��æ�ź�Ϊ0���ܶ�д
	
	PORTD &= ~(1 << E);   //E=0
	DDRB = 0xFF;          //PA����Ϊ����ڣ�׼����˿ڷ�������
}

void LCD12864WriteCommand(unsigned char ucCommand)
{
	LCD12864BusyCheck();
	
	PORTD &= ~(1 << RS);     //RS=0��д����
	PORTD &= ~(1 << RW);     //RW=0��дָ��
	PORTD |= (1 << E);       //E=1��д����
	_delay_ms(2);
	PORTB = ucCommand;         //ָ�������ݶ˿�
	PORTD &= ~(1 << E);     //E=0��ֹͣд����
    _delay_ms(5);
}


static void lcd_set_position(unsigned char add)	//�趨��Ҫ��ʾ�Ĺ��λ��
{
	LCD12864WriteCommand(add | 0x80);
}

void LCD12864WriteData(unsigned char ucData)
{
	LCD12864BusyCheck();

	PORTD |= (1 << RS);      //RS=1��д����
	PORTD &= ~(1 << RW);    //RW=0��дָ��
	PORTD |= (1 << E);      //E=1��д����
	_delay_ms(2);  
	PORTB = ucData;        // ���������ݶ˿�   
	PORTD &= ~(1 << E);    //E=0��ֹͣд��������������д��ô��
	_delay_ms(5);          // _delay_us(5)?
}


void LCD12864PortInit()
{      
	//LCD���ݶ˿�����
	PORTB = 0x00;         //
	DDRB = 0xFF;           //���ö˿�PBȫ��Ϊ�����
	
	PORTD = 0x00;
	DDRD |= (1 << RS) | (1 << RW) | (1 << E);
	_delay_ms(15);
}


void lcd_write_line(unsigned char line_start, unsigned char data[]) 	//��LCD��ʾ����д��һ���ַ�
{
	unsigned char i = 0;

	switch(line_start)
	{
		case LCD_LINE1_START:
		case LCD_LINE2_START:
		case LCD_LINE3_START:
		case LCD_LINE4_START:
			break;	//line_start������Ч
		default:
			return ;	//line_start������Ч
	}// end of switch

	LCD12864WriteCommand(0x30);	//function set  ʹ�û���ָ���8λ����������
	LCD12864WriteCommand(0x0c);	//�رչ����ʾ

	lcd_set_position( line_start );	//����LCD��ʾ����ʾ�е���ʼ��ַ
    i = 0;
	while(data[i])	//д�뽫Ҫ��ʾ������
	{
		LCD12864WriteData(data[i]);
		i++;
		if(i >= 16) return;
	}
}

void lcd_write_lines(unsigned char content[][16])	////��LCD��ʾ����д��4���ַ���
{
	//wdt_reset();	//ι��
	
	//cli();
	lcd_write_line(LCD_LINE1_START, content[0]);
	lcd_write_line(LCD_LINE2_START, content[1]);
	lcd_write_line(LCD_LINE3_START, content[2]);
	lcd_write_line(LCD_LINE4_START, content[3]);
	//sei();
}
unsigned char* lines[] = {"                ",
						  "                ",
						  "                ",
						  "                "};
void println(unsigned char* ucData){
	int i =0;
	for (i=0;i<3;i++){
		lines[i]=lines[i+1];
	}
	lines[3] = ucData;
		LCD12864WriteCommand(0x80+0x00);
		for(i = 0;i < 16;i++)
		{
			LCD12864WriteData(lines[0][i]);
		}
		LCD12864WriteCommand(0x90+0x00);
		for(i = 0;i < 16;i++)
		{
			LCD12864WriteData(lines[1][i]);
		}
	LCD12864WriteCommand(0x88+0x00);
		for(i = 0;i < 16;i++)
		{
			LCD12864WriteData(lines[2][i]);
		}
	LCD12864WriteCommand(0x98+0x00);
		for(i = 0;i < 16;i++)
		{
			LCD12864WriteData(lines[3][i]);
		}
}

