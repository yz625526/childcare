#include "APP_MPU6050.h"

float pitch, roll, yaw; // 欧拉角
short aacx, aacy, aacz; // 加速度传感器原始数据

void MPU6050_TIM3_Init(void)
{
    // 使能定时器3的时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    // 设置定时器3的参数
    TIM_TimeBaseStructure.TIM_Period        = 10000 - 1; // 定时器周期，根据主频和分频系数计算
    TIM_TimeBaseStructure.TIM_Prescaler     = 72 - 1;    // 分频系数，根据主频和所需频率计算
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;

    // 初始化定时器3
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    // 使能定时器3的更新中断
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    // 使能定时器3
    TIM_Cmd(TIM3, ENABLE);

    // 配置定时器3的中断优先级
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void APP_6050_init()
{
    MPU_Init();

    while (mpu_dmp_init()) { printf("6050mpu orror"); }

    MPU6050_TIM3_Init();
}

void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        // MPU_Get_Accelerometer(&aacx, &aacy, &aacz); // 得到加速度传感器数据
        if (mpu_dmp_get_data(&pitch, &roll, &yaw) == 0) {
            OLED_ShowString(3, 1, "pitch:");
            OLED_ShowNum(3, 7, (int)(pitch), 3);
            OLED_ShowString(4, 1, "roll:");
            OLED_ShowNum(4, 6, (int)(roll), 3);
            OLED_ShowString(5, 1, "yaw:");
            OLED_ShowNum(5, 5, (int)(yaw), 3);
        }

        TIM_ClearITPendingBit(TIM3, TIM_IT_Update); // 清除中断标志位
    }
}