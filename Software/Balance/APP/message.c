#include "message.h"

extern float Pitch,Roll,Yaw;
extern int l_encoder,r_encoder; 

extern int balance_kp;
extern float balance_kd;

void Show_Info(void)
{
	OLED_ShowString(0,0,"TEST FOR BALANCE"); 
	OLED_ShowString(0,1,"DMP:"); 
//œ‘ æΩ«∂»
	if(Roll<0)
	{
		OLED_ShowString(32,1,"-");		
		OLED_ShowNum(40,1,-Roll,3,12);
	}
	else	
	{		
		OLED_ShowString(32,1,"+");			
		OLED_ShowNum(40,1,Roll,3,12);	
	}
//◊Û¬÷±‡¬Î∆˜÷µ	
	OLED_ShowString(0,2,"LE:");
	if( l_encoder<0)
	{		
		OLED_ShowString(24,2,"-");
		OLED_ShowNum(32,2,-l_encoder,4,12);
	}
	else 
	{		
		OLED_ShowString(24,2,"+");
		OLED_ShowNum(32,2, l_encoder,4,12);
	}
//”“¬÷±‡¬Î∆˜÷µ	
	OLED_ShowString(0,3,"RE:");
	if(r_encoder<0)		
	{
		OLED_ShowString(24,3,"-"),
		OLED_ShowNum(32,3,r_encoder,4,12);
	}
	else               		
	{
		OLED_ShowString(24,3,"+");
		OLED_ShowNum(32,3,r_encoder,4,12);	
	}
	
	OLED_ShowString(0,4,"KP:");
	OLED_ShowNum(24,4,balance_kp,4,12);	
	
	OLED_ShowString(0,5,"Kd:");
	OLED_ShowNum(24,5,balance_kd,4,12);	
	
	
//ADC≤…ºØ÷µ
//	OLED_ShowString(0,4,"V:");
//	OLED_ShowNumber(16,4,Voltage/100,2,12);
//	OLED_ShowNum(68,40,Voltage%100,2,12);	
	
//		OLED_ShowNum(30,2,ADC_ConvertedValueLocal[1],4,12);
//		OLED_ShowNum(30,4,ADC_ConvertedValueLocal[0],4,12);	
}

