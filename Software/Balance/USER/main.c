// LED  : PC13
//USART1: PA9  PA10
//USART3: PB10 PB11
//OLED  : PA12 PA15 PB3 PB4  复用JTAG
//PWM (L R):PA8 PA11 (TIM1)
//MOTO(L R):(PB14 PB15) (PB12 PB13)
//SPI1:PA4 PA5 PA6 (CS)PA7
//ENCODER (TIM2 TIM4)
//TIM2:PA0 PA1 PA2 PA3
//TIM4:PB6 PB7 PB8 PB9
//ADC1 : PB0 PB1
//TIM3 FOR RECODE
//FREE : PB3 PB4 PB5 PC14 PC15
#include "config.h"

#define PwmMax 6900
#define PwmMin 0

extern u8 flag_5ms;
extern u8 flag_10ms;
extern u8 flag_15ms;
extern u8 flag_20ms;

extern float Pitch,Roll,Yaw;


extern	short gyro[3],accel[3];

int l_encoder,r_encoder; 

int balance_pwm;







/*****************************************************************************************
*	函 数 名: PC_SendStatus
*	入口参数: Pitch\Roll\Yaw - 相应的欧拉角数据
*	返 回 值: 无
*	函数功能: 向匿名地面站发送姿态数据
*	说    明: 相关通信协议可在匿名地面站上查询，在这里只发送欧拉角数据，数据*100后发送
*				 其它没有用到的数据发送0即可。
******************************************************************************************/

void PC_SendStatus(float Pitch,float Roll,float Yaw)
{
	u8	 i = 0;	
	u8  Check = 0;			//校验和
	u8	 SendBuffer[17];	//要发送的数据
	u16 SendVaule = 0;	//中转变量
	
	SendBuffer[0] = 0xAA;	//帧头
	SendBuffer[1] = 0xAA;	//帧头
	SendBuffer[2] = 0x01;	//功能字，01代表姿态数据
	SendBuffer[3] = 12;		//数据长度，不包括帧头、功能字、长度和校验位

	SendVaule = (int)(Roll*100);	//欧拉角扩大100倍后传输
	SendBuffer[4] = SendVaule>>8;	
	SendBuffer[5] =  SendVaule;	
	SendVaule = (int)(Pitch*100);	//欧拉角扩大100倍后传输
	SendBuffer[6] = SendVaule>>8;	
	SendBuffer[7] =  SendVaule;		
	SendVaule = (int)(Yaw*100);	//欧拉角扩大100倍后传输
	SendBuffer[8] = SendVaule>>8;	
	SendBuffer[9] =  SendVaule;	
	
	SendBuffer[10] = 0;		//未用到的数据赋值为0
	SendBuffer[11] = 0;	
	SendBuffer[12] = 0;	
	SendBuffer[13] = 0;		
	SendBuffer[14] = 0;		
	SendBuffer[15] = 0;	
	
	for(i=0;i<16;i++)				//计算校验和
		Check += SendBuffer[i];	//从帧头开始到最后一字节数据的和，只留低8位	
	SendBuffer[16] = Check;		//写入发送区
	
	for(i=0;i<17;i++)
	{
		USART_SendData(USART1,SendBuffer[i]);		//通过串口1发送数据
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET); 	//等待发送完毕
	}		
}

/*****************************************************************************************
*	函 数 名: PC_SendSenser
*	入口参数: Accel\Gyro - MPU6050的传感器原始数据
*	返 回 值: 无
*	函数功能: 向匿名地面站发送传感器原始数据
*	说    明: 相关通信协议可在匿名地面站上查询，在这里只发送陀螺仪和加速度传感器的数据，
*				 磁力计数据直接发送0即可。
******************************************************************************************/

void PC_SendSenser(int16_t * Accel,int16_t * Gyro)
{
	u8	 i = 0;
	u8  Check = 0;			//校验和
	u8	 SendBuffer[23];	//要发送的数据
	
	SendBuffer[0] = 0xAA;  	//帧头
	SendBuffer[1] = 0xAA;	//帧头
	SendBuffer[2] = 0x02;	//功能字，02表示传感器原始数据
	SendBuffer[3] = 18;		//数据长度，不包括帧头、功能字、长度和校验位
	
	SendBuffer[4]  = Accel[0]>>8;		//三轴加速度数据
	SendBuffer[5]  = Accel[0];	
	SendBuffer[6]  = Accel[1]>>8;
	SendBuffer[7]  = Accel[1];	
	SendBuffer[8]  = Accel[2]>>8;
	SendBuffer[9]  = Accel[2];	
	SendBuffer[10] = Gyro[0]>>8;		//三轴陀螺仪数据
	SendBuffer[11] = Gyro[0];	
	SendBuffer[12] = Gyro[1]>>8;
	SendBuffer[13] = Gyro[1];		
	SendBuffer[14] = Gyro[2]>>8;	
	SendBuffer[15] = Gyro[2];	
	SendBuffer[16] = 0;		//磁力计数据直接为0
	SendBuffer[17] = 0;
	SendBuffer[18] = 0;
	SendBuffer[19] = 0;	
	SendBuffer[20] = 0;	
	SendBuffer[21] = 0;	
	                 
	for(i=0;i<22;i++)				//计算校验和
		Check += SendBuffer[i];	//从帧头开始到最后一字节数据的和，只留低8位	
	SendBuffer[22] = Check;		//写入发送区
	
	for(i=0;i<23;i++)
	{
		USART_SendData(USART1,SendBuffer[i]);		//通过串口1发送数据
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET); //等待发送完毕
	}		
}






int main(void)
{	
	delay_init();			
	Led_Init();
	IIC_Init();
  USART1_Config(9600);
//	USART3_Config(9600);	
	TIM3_Init(5000,71);			//1/(72MHZ /72) * 5000 = 5ms
//	MotorDriver_Init();	
//	Encoder_Init_TIM2();
//	Encoder_Init_TIM4();
	
//	OLED_Init();						//复用JTAG 初始化时关闭JTAG 使能SWD
	DMP_Config();	
		
	delay_ms(300);
	
	while(1)
	{
//		Led_1 = 0;
//		Led_Flash();

	
//		printf("\r\n 左轮数值 = %d \r\n",l_encoder);								
//		printf("\r\n 右轮数值 = %d \r\n",r_encoder);	

		if(flag_5ms == 1)
		{
			flag_5ms = 0 ;		
			Read_DMP();
		}
//			
//			l_encoder=Read_Encoder(2);
//			r_encoder=Read_Encoder(4);	
//			
//			Show_Info();	
//			if(Roll>45||Roll<-45)
//			{
//				TIM1 ->CCR1 =0;
//				TIM1 ->CCR4 =0;	
//			}
//			else
//			{
//			balance_pwm = PD_Balance(Roll,gyro[0]);
//			//pwm限幅
//			if(balance_pwm >= PwmMax)
//				balance_pwm = PwmMax;
//			if(balance_pwm >0)
//			{
//				TIM1 ->CCR1 =balance_pwm;
//				TIM1 ->CCR4 =balance_pwm;		
//				Motor_L_CCW();
//				Motor_R_CCW();		
//			}
//			if(balance_pwm <0)
//			{
//				TIM1 ->CCR1 = -balance_pwm;
//				TIM1 ->CCR4 = -balance_pwm;	
//				Motor_L_CW();
//				Motor_R_CW();						
//	
//			}
//		}
//			
//			printf("\r\n pitch = %f \r\n",Pitch);								
//			printf("\r\n roll= %f \r\n",Roll);
//			printf("\r\n yaw= %f \r\n",Yaw);
//		}	

	PC_SendStatus(Pitch,Roll,Yaw);	//向匿名地面站发送姿态数据
	PC_SendSenser((int16_t *)&accel,(int16_t *)&gyro);	 ////向匿名地面站发送传感器原始数据
	delay_ms(10);
//			printf("\r\n pitch = %f \r\n",Pitch);								
//			printf("\r\n roll= %f \r\n",Roll);
//			printf("\r\n yaw= %f \r\n",Yaw);

		
	}		
}

