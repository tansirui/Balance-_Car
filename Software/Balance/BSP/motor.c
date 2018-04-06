#include "motor.h"

/**
	*	@brief		电机驱动左轮配置
	*	@param		none
	*	@retval		none
	*/
void	Motor_L_Config(void){
	
	GPIO_InitTypeDef					GPIO_InitStructure ;
	TIM_TimeBaseInitTypeDef		TIM_BaseInitStructure;
	TIM_OCInitTypeDef					TIM_OCInitStructure;
	
	/*使能GPIOA、GPIOB、AFIO、TIM1外设时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO | RCC_APB2Periph_TIM1, ENABLE);
	
	/*初始化PB.12端口为Out_PP模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*初始化PB.13端口为Out_PP模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*初始化PA.08端口(TIM1_CH1)为AF_PP模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*定时器基本配置*/
	TIM_BaseInitStructure.TIM_Prescaler = 0;													//时钟预分频数3,TIM1的计数时钟频率为24MHz
	TIM_BaseInitStructure.TIM_Period = 7199;													//自动重装载寄存器数值,PWM2频率为24MHz/1000=24KHz
	TIM_BaseInitStructure.TIM_ClockDivision = 0;												//采样分频
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;					//向上计数
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;										//重复寄存器
	TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;										//PWM1输出模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;				//使能该通道输出
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;						//输出极性
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);														//按指定参数初始化

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);										//使能TIM1在CCR1上的预装载寄存器
	TIM_ARRPreloadConfig(TIM1, ENABLE);																	//使能TIM1在ARR上的预装载寄存器
	
	TIM_Cmd(TIM1, ENABLE);																							//打开TIM1
	TIM_CtrlPWMOutputs(TIM1, ENABLE);																		//PWM输出使能
}

/**
	*	@brief		电机驱动右轮配置
	*	@param		none
	*	@retval		none
	*/
void	Motor_R_Config(void){

	GPIO_InitTypeDef					GPIO_InitStructure ;
	TIM_TimeBaseInitTypeDef		TIM_BaseInitStructure;
	TIM_OCInitTypeDef					TIM_OCInitStructure;

	/*使能GPIOA、GPIOB、AFIO、TIM1外设时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO | RCC_APB2Periph_TIM1, ENABLE);

	/*初始化PA.08端口为Out_PP模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*初始化PB.13端口为Out_PP模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*初始化PA.11端口(TIM1_CH4)为AF_PP模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*定时器基本配置*/
	TIM_BaseInitStructure.TIM_Prescaler = 0;													//时钟预分频数3,TIM1的计数时钟频率为24MHz
	TIM_BaseInitStructure.TIM_Period = 7199;													//自动重装载寄存器数值,PWM2频率为24MHz/1000=24KHz
	TIM_BaseInitStructure.TIM_ClockDivision = 0;												//采样分频
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;					//向上计数
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;										//重复寄存器
	TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;										//PWM1输出模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;				//使能该通道输出
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;						//输出极性
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);														//按指定参数初始化

	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);										//使能TIM1在CCR4上的预装载寄存器
	TIM_ARRPreloadConfig(TIM1, ENABLE);																	//使能TIM1在ARR上的预装载寄存器

	TIM_Cmd(TIM1, ENABLE);																							//打开TIM1
	TIM_CtrlPWMOutputs(TIM1, ENABLE);																		//PWM输出使能
}

/**
	*	@brief		左轮电机正转
	*	@param		none
	*	@retval		none
	*/
void	Motor_L_CW(void){
	
	MOTOR_L_IN1_LOW;
	MOTOR_L_IN2_HIGH;
}

/**
	*	@brief		左轮电机反转
	*	@param		none
	*	@retval		none
	*/
void	Motor_L_CCW(void){
	
	MOTOR_L_IN1_HIGH;
	MOTOR_L_IN2_LOW;
}

/**
	*	@brief		右轮电机正转
	*	@param		none
	*	@retval		none
	*/
void	Motor_R_CW(void){
	
	MOTOR_R_IN1_HIGH;
	MOTOR_R_IN2_LOW;
}

/**
	*	@brief		右轮电机反转
	*	@param		none
	*	@retval		none
	*/
void	Motor_R_CCW(void){
	
	MOTOR_R_IN1_LOW;
	MOTOR_R_IN2_HIGH;
}

/**
	*	@brief		电机驱动外设初始化
	*	@param		none
	*	@retval		none
	*/
void	MotorDriver_Init(void){
	
	Motor_L_Config();
	Motor_R_Config();
	
	Motor_L_CW();
	Motor_R_CW();
}
