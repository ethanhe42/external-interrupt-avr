#ifndef DRIVER_LCD_H
#define DRIVER_LCD_H


//�˿�λ����
#define RS PD5           //����/������ƶ� 0���1����
#define RW PD6           //��/дѡ����ƶ� 0д��1��
#define E PD7            //ʹ�ܶ�          �½��ض����ߵ�ƽд

#define LCD_LINE1_START 0x00
#define LCD_LINE2_START 0x10
#define LCD_LINE3_START 0x08
#define LCD_LINE4_START 0x18

void LCD12864PortInit();
void lcd_write_line(unsigned char line_start, unsigned char data[]) ;
void lcd_write_lines(unsigned char content[][16]);

#endif
