// LED  : PC13
//USART1: PA9  PA10
//USART3: PB10 PB11
//OLED  : PA12 PA15 PB3 PB4  ����JTAG
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
*	�� �� ��: PC_SendStatus
*	��ڲ���: Pitch\Roll\Yaw - ��Ӧ��ŷ��������
*	�� �� ֵ: ��
*	��������: ����������վ������̬����
*	˵    ��: ���ͨ��Э�������������վ�ϲ�ѯ��������ֻ����ŷ�������ݣ�����*100����
*				 ����û���õ������ݷ���0���ɡ�
******************************************************************************************/

void PC_SendStatus(float Pitch,float Roll,float Yaw)
{
	u8	 i = 0;	
	u8  Check = 0;			//У���
	u8	 SendBuffer[17];	//Ҫ���͵�����
	u16 SendVaule = 0;	//��ת����
	
	SendBuffer[0] = 0xAA;	//֡ͷ
	SendBuffer[1] = 0xAA;	//֡ͷ
	SendBuffer[2] = 0x01;	//�����֣�01������̬����
	SendBuffer[3] = 12;		//���ݳ��ȣ�������֡ͷ�������֡����Ⱥ�У��λ

	SendVaule = (int)(Roll*100);	//ŷ��������100������
	SendBuffer[4] = SendVaule>>8;	
	SendBuffer[5] =  SendVaule;	
	SendVaule = (int)(Pitch*100);	//ŷ��������100������
	SendBuffer[6] = SendVaule>>8;	
	SendBuffer[7] =  SendVaule;		
	SendVaule = (int)(Yaw*100);	//ŷ��������100������
	SendBuffer[8] = SendVaule>>8;	
	SendBuffer[9] =  SendVaule;	
	
	SendBuffer[10] = 0;		//δ�õ������ݸ�ֵΪ0
	SendBuffer[11] = 0;	
	SendBuffer[12] = 0;	
	SendBuffer[13] = 0;		
	SendBuffer[14] = 0;		
	SendBuffer[15] = 0;	
	
	for(i=0;i<16;i++)				//����У���
		Check += SendBuffer[i];	//��֡ͷ��ʼ�����һ�ֽ����ݵĺͣ�ֻ����8λ	
	SendBuffer[16] = Check;		//д�뷢����
	
	for(i=0;i<17;i++)
	{
		USART_SendData(USART1,SendBuffer[i]);		//ͨ������1��������
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET); 	//�ȴ��������
	}		
}

/*****************************************************************************************
*	�� �� ��: PC_SendSenser
*	��ڲ���: Accel\Gyro - MPU6050�Ĵ�����ԭʼ����
*	�� �� ֵ: ��
*	��������: ����������վ���ʹ�����ԭʼ����
*	˵    ��: ���ͨ��Э�������������վ�ϲ�ѯ��������ֻ���������Ǻͼ��ٶȴ����������ݣ�
*				 ����������ֱ�ӷ���0���ɡ�
******************************************************************************************/

void PC_SendSenser(int16_t * Accel,int16_t * Gyro)
{
	u8	 i = 0;
	u8  Check = 0;			//У���
	u8	 SendBuffer[23];	//Ҫ���͵�����
	
	SendBuffer[0] = 0xAA;  	//֡ͷ
	SendBuffer[1] = 0xAA;	//֡ͷ
	SendBuffer[2] = 0x02;	//�����֣�02��ʾ������ԭʼ����
	SendBuffer[3] = 18;		//���ݳ��ȣ�������֡ͷ�������֡����Ⱥ�У��λ
	
	SendBuffer[4]  = Accel[0]>>8;		//������ٶ�����
	SendBuffer[5]  = Accel[0];	
	SendBuffer[6]  = Accel[1]>>8;
	SendBuffer[7]  = Accel[1];	
	SendBuffer[8]  = Accel[2]>>8;
	SendBuffer[9]  = Accel[2];	
	SendBuffer[10] = Gyro[0]>>8;		//��������������
	SendBuffer[11] = Gyro[0];	
	SendBuffer[12] = Gyro[1]>>8;
	SendBuffer[13] = Gyro[1];		
	SendBuffer[14] = Gyro[2]>>8;	
	SendBuffer[15] = Gyro[2];	
	SendBuffer[16] = 0;		//����������ֱ��Ϊ0
	SendBuffer[17] = 0;
	SendBuffer[18] = 0;
	SendBuffer[19] = 0;	
	SendBuffer[20] = 0;	
	SendBuffer[21] = 0;	
	                 
	for(i=0;i<22;i++)				//����У���
		Check += SendBuffer[i];	//��֡ͷ��ʼ�����һ�ֽ����ݵĺͣ�ֻ����8λ	
	SendBuffer[22] = Check;		//д�뷢����
	
	for(i=0;i<23;i++)
	{
		USART_SendData(USART1,SendBuffer[i]);		//ͨ������1��������
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET); //�ȴ��������
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
	
//	OLED_Init();						//����JTAG ��ʼ��ʱ�ر�JTAG ʹ��SWD
	DMP_Config();	
		
	delay_ms(300);
	
	while(1)
	{
//		Led_1 = 0;
//		Led_Flash();

	
//		printf("\r\n ������ֵ = %d \r\n",l_encoder);								
//		printf("\r\n ������ֵ = %d \r\n",r_encoder);	

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
//			//pwm�޷�
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

	PC_SendStatus(Pitch,Roll,Yaw);	//����������վ������̬����
	PC_SendSenser((int16_t *)&accel,(int16_t *)&gyro);	 ////����������վ���ʹ�����ԭʼ����
	delay_ms(10);
//			printf("\r\n pitch = %f \r\n",Pitch);								
//			printf("\r\n roll= %f \r\n",Roll);
//			printf("\r\n yaw= %f \r\n",Yaw);

		
	}		
}

