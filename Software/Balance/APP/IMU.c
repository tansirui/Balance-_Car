#include "IMU.h"

float Pitch,Roll,Yaw;


short gyro[3], accel[3], sensors;
																					 																					 
//方向转换																					 
static  unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;     
    return b;
}
//陀螺仪方向控制
static  unsigned short inv_orientation_matrix_to_scalar(
    const signed char *mtx)
{
    unsigned short scalar;
    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;

    return scalar;
}
//自检
static void run_self_test(void)
{
    int result;
    long gyro[3], accel[3];

    result = mpu_run_self_test(gyro, accel);
    if (result == 0x7) 
		{
        /* Test passed. We can trust the gyro data here, so let's push it down
         * to the DMP.
         */
			float sens;
      unsigned short accel_sens;
      mpu_get_gyro_sens(&sens);
      gyro[0] = (long)(gyro[0] * sens);
      gyro[1] = (long)(gyro[1] * sens);
      gyro[2] = (long)(gyro[2] * sens);
      dmp_set_gyro_bias(gyro);
      mpu_get_accel_sens(&accel_sens);
      accel[0] *= accel_sens;
      accel[1] *= accel_sens;
      accel[2] *= accel_sens;
      dmp_set_accel_bias(accel);
			printf("setting bias succesfully ......\r\n");
    }
}

void DMP_Config(void)
{ 
//	u8 temp[1]={0};
//	IICreadBytes(0xd0,0x75,1,temp);
//	if(temp[0]!=0x68)
//	printf("connection wrong ......\r\n");	
//	else
//	printf("connection right ......\r\n");		
	if(!mpu_init())
  {		
		//设置所需要的传感器
	  if(!mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL))
	  printf("mpu_set_sensor complete ......\r\n");
		//设置FIFO
	  if(!mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL))
	  printf("mpu_configure_fifo complete ......\r\n");
		//设置采样率
	  if(!mpu_set_sample_rate(DEFAULT_MPU_HZ))
	  printf("mpu_set_sample_rate complete ......\r\n");
		//加载dmp固件
	  if(!dmp_load_motion_driver_firmware())
	  printf("dmp_load_motion_driver_firmware complete ......\r\n");
		//设置陀螺仪方向
	  if(!dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)))
	  printf("dmp_set_orientation complete ......\r\n");
		//设置dmp功能
	  if(!dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
	        DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
	        DMP_FEATURE_GYRO_CAL))
		printf("dmp_enable_feature complete ......\r\n");
		//设置DMP输出速率(最大不超过200Hz)
	  if(!dmp_set_fifo_rate(DEFAULT_MPU_HZ))
	  printf("dmp_set_fifo_rate complete ......\r\n");
		//自检
	  run_self_test();
		//使能DMP
	  if(!mpu_set_dmp_state(1))
	  printf("mpu_set_dmp_state complete ......\r\n");
  }
}

void Read_DMP(void)
{	
	unsigned long sensor_timestamp;
	unsigned char more;
	long quat[4];

	float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;																					 

	
	dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more);		
	if (sensors & INV_WXYZ_QUAT )
	{    
		q0=quat[0] / q30;
		q1=quat[1] / q30;
		q2=quat[2] / q30;
		q3=quat[3] / q30;
		
		Pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; 	
		Roll  = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3;
		Yaw   = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;	
	}
}
