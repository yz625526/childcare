#include "APP.h"
#include "Task_use_TIM.h"

// 调度初始化
void SYS_Init(void)
{
    APP_OLED_init();
    APP_LED_init();
    APP_SHT30_init();
    APP_Uart_send_init();
    APP_6050_init();
    GPS_APP_init();
    APP_TIM_init();

    // Tim_task_init(); // 启动调度
}
