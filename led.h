#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include <util/delay.h>

struct Led_status{
	unsigned char status;		//�����趨8��LED�Ƶ�һ��״̬
	int delay;	//�����趨��Ӧ״̬��LED�Ƶ���ʱ����λ�Ǻ���
};

//�趨һ��������LED�Ƶ���ʾ״̬����ʱ
extern const struct Led_status led_status[] ;


void light_led(unsigned char status);	//���趨״̬����LED��

#endif

