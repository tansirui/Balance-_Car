#include "led.h"

//test B8 B9 A2 A3 

void Led_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
  GPIO_Init(GPIOC, &GPIO_InitStructure);	
//	//初始化定时器4的三四通道
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);	
//	//初始化定时器2的三四通道
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);	
//	
//	GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3);
//	
//	GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);
	
  GPIO_SetBits(GPIOC,GPIO_Pin_13);	
	
}

void Led_Flash()
{
	Led_1=0;
	delay_ms(300);
	Led_1=1;
	delay_ms(300);	
}

//void Led_RGB()
//{
//	Led_R = 0;	
//	Led_G = 0;
//	Led_B = 0;
//	
//}
