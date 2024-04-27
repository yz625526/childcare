#ifndef __APP_MPU6050_H_
#define __APP_MPU6050_H_

#include "stm32f10x_conf.h"

extern float pitch, roll, yaw; // 欧拉角
extern short aacx, aacy, aacz; // 加速度传感器原始数据

void APP_6050_init();
// void APP_OLED_refresh();

#endif
