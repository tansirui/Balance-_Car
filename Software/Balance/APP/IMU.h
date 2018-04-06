#ifndef _IMU_H
#define _IMU_H

#include "inv_mpu.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "inv_mpu_dmp_motion_driver.h"

#include <math.h>
#include "IOI2C.h"
#include "usart1.h"

//��������ٶ�
#define DEFAULT_MPU_HZ  (200)

//q30��ʽ,longתfloatʱ�ĳ���.
#define q30  1073741824.0f

//�����Ƿ�������
static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};

void DMP_Config(void);
void Read_DMP(void);

#endif

