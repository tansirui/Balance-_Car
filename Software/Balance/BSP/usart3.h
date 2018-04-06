#ifndef __USART3_H
#define __USART3_H 

#include "stm32f10x.h"

void USART3_Config(u32 bound);

void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data);	
void UART_PutStr (USART_TypeDef* USARTx, uint8_t *str);  
		
#endif

