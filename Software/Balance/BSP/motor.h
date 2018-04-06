#ifndef _MOTOR_H
#define _MOTOR_H
/*
TIM	TIM1	TIM2	TIM3	TIM4	TIM5	TIM8
CH1	PA8		PA0		PA6		PB6		PA0		PC6
CH2	PA9		PA1		PA7		PB7		PA1		PC7
CH3 PA10	PA2		PB0		PB8		PA2		PC8
CH4	PA11	PA3		PB1		PB9		PA3		PC9
*/
#include "stm32f10x.h"

#define	MOTOR_L_IN1_LOW			(GPIO_ResetBits(GPIOB, GPIO_Pin_12))
#define	MOTOR_L_IN1_HIGH		(GPIO_SetBits(GPIOB, GPIO_Pin_12))
#define	MOTOR_L_IN2_LOW			(GPIO_ResetBits(GPIOB, GPIO_Pin_13))
#define	MOTOR_L_IN2_HIGH		(GPIO_SetBits(GPIOB, GPIO_Pin_13))

#define	MOTOR_R_IN1_LOW			(GPIO_ResetBits(GPIOB, GPIO_Pin_15))
#define	MOTOR_R_IN1_HIGH		(GPIO_SetBits(GPIOB, GPIO_Pin_15))
#define	MOTOR_R_IN2_LOW			(GPIO_ResetBits(GPIOB, GPIO_Pin_14))
#define	MOTOR_R_IN2_HIGH		(GPIO_SetBits(GPIOB, GPIO_Pin_14))

void	Motor_L_CW(void);			//左轮电机正转
void	Motor_L_CCW(void);		//左轮电机反转
void	Motor_R_CW(void);			//右轮电机正转
void	Motor_R_CCW(void);		//右轮电机反转
void	MotorDriver_Init(void);					//电机驱动外设初始化

#endif
