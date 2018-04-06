#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"
#include "include.h"
#include "delay.h"

#define Led_1 PCout(13)

//#define Led_R PBout(8)
//#define Led_G PBout(9)
//#define Led_B PAout(2)
//#define Led_2 PAout(3)



void Led_Init(void);
void Led_Flash(void);
//void Led_RGB();

#endif
