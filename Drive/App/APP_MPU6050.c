#include "APP_MPU6050.h"

float pitch, roll, yaw; // 欧拉角
short aacx, aacy, aacz; // 加速度传感器原始数据

void APP_6050_init()
{
    MPU_Init();

    while (mpu_dmp_init()) { printf("6050mpu orror"); }
}