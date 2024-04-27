#include "APP_MPU6050.h"

void APP_6050_init()
{
    MPU_Init();

    while (mpu_dmp_init()) { printf("6050mpu orror"); }
}