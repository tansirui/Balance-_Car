#include "motor.h"

/**
	*	@brief		���������������
	*	@param		none
	*	@retval		none
	*/
void	Motor_L_Config(void){
	
	GPIO_InitTypeDef					GPIO_InitStructure ;
	TIM_TimeBaseInitTypeDef		TIM_BaseInitStructure;
	TIM_OCInitTypeDef					TIM_OCInitStructure;
	
	/*ʹ��GPIOA��GPIOB��AFIO��TIM1����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO | RCC_APB2Periph_TIM1, ENABLE);
	
	/*��ʼ��PB.12�˿�ΪOut_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*��ʼ��PB.13�˿�ΪOut_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*��ʼ��PA.08�˿�(TIM1_CH1)ΪAF_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*��ʱ����������*/
	TIM_BaseInitStructure.TIM_Prescaler = 0;													//ʱ��Ԥ��Ƶ��3,TIM1�ļ���ʱ��Ƶ��Ϊ24MHz
	TIM_BaseInitStructure.TIM_Period = 7199;													//�Զ���װ�ؼĴ�����ֵ,PWM2Ƶ��Ϊ24MHz/1000=24KHz
	TIM_BaseInitStructure.TIM_ClockDivision = 0;												//������Ƶ
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;					//���ϼ���
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;										//�ظ��Ĵ���
	TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;										//PWM1���ģʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;				//ʹ�ܸ�ͨ�����
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;						//�������
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);														//��ָ��������ʼ��

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);										//ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM1, ENABLE);																	//ʹ��TIM1��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1, ENABLE);																							//��TIM1
	TIM_CtrlPWMOutputs(TIM1, ENABLE);																		//PWM���ʹ��
}

/**
	*	@brief		���������������
	*	@param		none
	*	@retval		none
	*/
void	Motor_R_Config(void){

	GPIO_InitTypeDef					GPIO_InitStructure ;
	TIM_TimeBaseInitTypeDef		TIM_BaseInitStructure;
	TIM_OCInitTypeDef					TIM_OCInitStructure;

	/*ʹ��GPIOA��GPIOB��AFIO��TIM1����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO | RCC_APB2Periph_TIM1, ENABLE);

	/*��ʼ��PA.08�˿�ΪOut_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*��ʼ��PB.13�˿�ΪOut_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*��ʼ��PA.11�˿�(TIM1_CH4)ΪAF_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*��ʱ����������*/
	TIM_BaseInitStructure.TIM_Prescaler = 0;													//ʱ��Ԥ��Ƶ��3,TIM1�ļ���ʱ��Ƶ��Ϊ24MHz
	TIM_BaseInitStructure.TIM_Period = 7199;													//�Զ���װ�ؼĴ�����ֵ,PWM2Ƶ��Ϊ24MHz/1000=24KHz
	TIM_BaseInitStructure.TIM_ClockDivision = 0;												//������Ƶ
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;					//���ϼ���
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;										//�ظ��Ĵ���
	TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;										//PWM1���ģʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;				//ʹ�ܸ�ͨ�����
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;						//�������
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);														//��ָ��������ʼ��

	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);										//ʹ��TIM1��CCR4�ϵ�Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM1, ENABLE);																	//ʹ��TIM1��ARR�ϵ�Ԥװ�ؼĴ���

	TIM_Cmd(TIM1, ENABLE);																							//��TIM1
	TIM_CtrlPWMOutputs(TIM1, ENABLE);																		//PWM���ʹ��
}

/**
	*	@brief		���ֵ����ת
	*	@param		none
	*	@retval		none
	*/
void	Motor_L_CW(void){
	
	MOTOR_L_IN1_LOW;
	MOTOR_L_IN2_HIGH;
}

/**
	*	@brief		���ֵ����ת
	*	@param		none
	*	@retval		none
	*/
void	Motor_L_CCW(void){
	
	MOTOR_L_IN1_HIGH;
	MOTOR_L_IN2_LOW;
}

/**
	*	@brief		���ֵ����ת
	*	@param		none
	*	@retval		none
	*/
void	Motor_R_CW(void){
	
	MOTOR_R_IN1_HIGH;
	MOTOR_R_IN2_LOW;
}

/**
	*	@brief		���ֵ����ת
	*	@param		none
	*	@retval		none
	*/
void	Motor_R_CCW(void){
	
	MOTOR_R_IN1_LOW;
	MOTOR_R_IN2_HIGH;
}

/**
	*	@brief		������������ʼ��
	*	@param		none
	*	@retval		none
	*/
void	MotorDriver_Init(void){
	
	Motor_L_Config();
	Motor_R_Config();
	
	Motor_L_CW();
	Motor_R_CW();
}
