#include "keep.h"

#define keep 1			//平衡时的角度


extern int balance_kp;
extern float balance_kd;

int PD_Balance(float roll,float gyro_x)
{
//Kp = 150, Kd = 0.95;       //具体的kp和kd的值，在实际应用中需要不断的调试
  
   float error,kp=650,kd=1;
	 int balance;
	 error = roll - keep;      
	 balance = kp*error + gyro_x*kd;  
	 return balance;
}
