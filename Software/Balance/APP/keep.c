#include "keep.h"

#define keep 1			//ƽ��ʱ�ĽǶ�


extern int balance_kp;
extern float balance_kd;

int PD_Balance(float roll,float gyro_x)
{
//Kp = 150, Kd = 0.95;       //�����kp��kd��ֵ����ʵ��Ӧ������Ҫ���ϵĵ���
  
   float error,kp=650,kd=1;
	 int balance;
	 error = roll - keep;      
	 balance = kp*error + gyro_x*kd;  
	 return balance;
}
