#include "APP_TIM_refresh.h"

void APP_TIM_init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period        = 9999; // 计数器周期为100ms
    TIM_TimeBaseStructure.TIM_Prescaler     = 7199; // 预分频为7200
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // 配置定时器2中断
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 使能定时器2更新事件中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // 启动定时器2
    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        // 处理定时器2中断事件
        // ...
        SHT3X_GetTempAndHumi(&temperature, &humidity, REPEATAB_HIGH, MODE_CLKSTRETCH, 50); // 读取sht30值
        USART1_Printf("IndoorTemperature:%d", (int)temperature);
        OLED_ShowNum(1, 1, temperature, 2);
        OLED_ShowNum(2, 1, humidity, 2);
        
        OLED_ShowString(4, 1, "AX:");
        // OLED_ShowNum(4, 4, AX, 6);
        OLED_ShowString(5, 1, "AY:");
        // OLED_ShowNum(5, 4, AY, 6);
        OLED_ShowString(6, 1, "AZ:");
        // OLED_ShowNum(6, 4, AZ, 6);
        // USART1_SendNumber(GX);
        // APP_LED_blink();

        // 清除中断标志位
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}