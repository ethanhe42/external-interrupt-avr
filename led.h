#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include <util/delay.h>

struct Led_status{
	unsigned char status;		//用于设定8个LED灯的一种状态
	int delay;	//用于设定对应状态下LED灯的延时，单位是毫秒
};

//设定一个周期中LED灯的显示状态和延时
extern const struct Led_status led_status[] ;


void light_led(unsigned char status);	//按设定状态点亮LED灯

#endif

