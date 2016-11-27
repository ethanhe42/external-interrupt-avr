#include "driver_lcd.h"
#include <util/delay.h>
#include <avr/io.h>

void LCD12864BusyCheck(void)
{
    unsigned int uiTemp;
	uiTemp = 3000;
	
	DDRB = 0x00;             //PB口置为输入口，准备读取数据
	PORTD &= ~(1 << RS);      //RS=0，读命令
	PORTD |= (1 << RW);    //RW=1，读指令
	PORTD |= (1 << E);      //E=1，使能
	
	while((0x80 & PINB) && (uiTemp--));   //监测忙信号，直到忙信号为0才能读写
	
	PORTD &= ~(1 << E);   //E=0
	DDRB = 0xFF;          //PA口置为输出口，准备向端口发送数据
}

void LCD12864WriteCommand(unsigned char ucCommand)
{
	LCD12864BusyCheck();
	
	PORTD &= ~(1 << RS);     //RS=0，写命令
	PORTD &= ~(1 << RW);     //RW=0，写指令
	PORTD |= (1 << E);       //E=1，写操作
	_delay_ms(2);
	PORTB = ucCommand;         //指令送数据端口
	PORTD &= ~(1 << E);     //E=0，停止写操作
    _delay_ms(5);
}


static void lcd_set_position(unsigned char add)	//设定将要显示的光标位置
{
	LCD12864WriteCommand(add | 0x80);
}

void LCD12864WriteData(unsigned char ucData)
{
	LCD12864BusyCheck();

	PORTD |= (1 << RS);      //RS=1，写数据
	PORTD &= ~(1 << RW);    //RW=0，写指令
	PORTD |= (1 << E);      //E=1，写操作
	_delay_ms(2);  
	PORTB = ucData;        // 数据送数据端口   
	PORTD &= ~(1 << E);    //E=0，停止写操作；可以连续写入么？
	_delay_ms(5);          // _delay_us(5)?
}


void LCD12864PortInit()
{      
	//LCD数据端口设置
	PORTB = 0x00;         //
	DDRB = 0xFF;           //配置端口PB全部为输出口
	
	PORTD = 0x00;
	DDRD |= (1 << RS) | (1 << RW) | (1 << E);
	_delay_ms(15);
}


void lcd_write_line(unsigned char line_start, unsigned char data[]) 	//向LCD显示屏上写入一行字符
{
	unsigned char i = 0;

	switch(line_start)
	{
		case LCD_LINE1_START:
		case LCD_LINE2_START:
		case LCD_LINE3_START:
		case LCD_LINE4_START:
			break;	//line_start参数有效
		default:
			return ;	//line_start参数无效
	}// end of switch

	LCD12864WriteCommand(0x30);	//function set  使用基本指令集，8位并行数据线
	LCD12864WriteCommand(0x0c);	//关闭光标显示

	lcd_set_position( line_start );	//设置LCD显示屏显示行的起始地址
    i = 0;
	while(data[i])	//写入将要显示的内容
	{
		LCD12864WriteData(data[i]);
		i++;
		if(i >= 16) return;
	}
}

void lcd_write_lines(unsigned char content[][16])	////向LCD显示屏上写入4行字符串
{
	//wdt_reset();	//喂狗
	
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

