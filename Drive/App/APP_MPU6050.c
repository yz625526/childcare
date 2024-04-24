#include "APP_MPU6050.h"

float pitch, roll, yaw; // 欧拉角

void APP_6050_init()
{
    u8 temp;
    // MPU_Init(); // 初始化MPU6050
    mpu_dmp_init();
}