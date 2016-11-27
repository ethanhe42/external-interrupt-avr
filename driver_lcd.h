#ifndef DRIVER_LCD_H
#define DRIVER_LCD_H


//端口位定义
#define RS PD5           //数据/命令控制端 0命令，1数据
#define RW PD6           //读/写选择控制端 0写，1读
#define E PD7            //使能端          下降沿读，高电平写

#define LCD_LINE1_START 0x00
#define LCD_LINE2_START 0x10
#define LCD_LINE3_START 0x08
#define LCD_LINE4_START 0x18

void LCD12864PortInit();
void lcd_write_line(unsigned char line_start, unsigned char data[]) ;
void lcd_write_lines(unsigned char content[][16]);

#endif
