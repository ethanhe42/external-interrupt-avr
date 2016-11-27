/**************************************************
** 文件名：test_external_interruput.c         
** 功能：外部中断功能测试程序，LCD显示功能菜单
** 说明：需要调用LCD显示程序
*****************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#ifndef F_CPU 		//定义时钟频率，该数值对于软件延时非常重要
#define F_CPU 8000000UL      
#endif 
#include "driver_lcd.h"

void system_init()		//系统初始化
{
	//关闭8个LED灯
	DDRB = 0xff;		//设置PB端口为输出
	DDRC |= _BV(PC5);	//设置PC5为输出
	PORTC |= _BV(PC5);	//置PC5为高电平，使能led锁存
	PORTB = 0xff;		//关闭8个led灯
	PORTC &= ~_BV(PC5);     //PC5置低，关闭led锁存器器

	//关闭数码管显示
	DDRG |= _BV(PG3);	//设置PG3为输出，PG3控制数码管的位选择锁存器；
	DDRG |= _BV(PG4);	//设置PG4为输出，PG4控制数码管的段码锁存器；
		
	PORTG |= _BV(PG3);	//使能数码管位选择锁存器
	PORTG &= ~_BV(PG4);	//关闭字型码锁存器
	DDRB = 0xff;		//设置端口PB为输出
	PORTB = 0x00; 		//送数码管位码

	PORTG &= ~_BV(PG3);	//关闭数码管位选择锁存器		
	PORTG |= _BV(PG4);	//使能段码锁存器
	PORTB = 0xff;		//送段码
	PORTG &= ~_BV(PG4);	//关闭段码锁存器

	//关闭蜂鸣器
	DDRE |= _BV(PE3);	
	PORTE |= _BV(PE3);	//喇叭电路断开，喇叭停止鸣响
}

int main()
{
	system_init();		//系统初始化
	LCD12864PortInit();		    //LCD设备上电初始化

	lcd_write_line(LCD_LINE1_START, "  西安交通大学  ");
	lcd_write_line(LCD_LINE2_START, "ATmega128 单片机");
	lcd_write_line(LCD_LINE3_START, "  外部中断演示  ");
	lcd_write_line(LCD_LINE4_START, "   2011-06-01   ");
		
	SFIOR &= 0xfc;		//使能全局上拉电阻
	DDRE &= 0x0f;		//PE4-PE7配置为输入
	PORTE |= 0xf0;		//PE4-PE7使能上拉电阻

	while(1) {
// INT4--INT7外部中断初始化
	    //EICRB = 0b10101010;	
		EICRB = 0b11111111;
	    //EICRB = 0x00;	    //设置INT4--INT7为低电平触发
	    EIFR = 0xff;	    //清除外部中断标志
	    EIMSK |= 0xf0;	    //开启INT4--INT7外部中断
		sei();		        //全局开中断
	}
	
	return 0;
}

