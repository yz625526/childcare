#include "stm32f10x_conf.h"
#include "APP.h"
#include "Task.h"

// u8 Mode_state        = 0; // 模式切换，0是关闭，1是防盗模式，2是车灯
// u8 Alarm_init_switch = 0; // 启动防盗时的初始化。0未完成，1完成
// u8 Alarm_open        = 0; // 是否触发防盗，触发1未触发0

int main(void)
{
    float temperature; // temperature [°C]
    float humidity;    // relative humidity [%RH]

    // SYS_Init();
    // while (1)
    // {
    //     Task_Pro_Handler_Callback();
    // }

    // LED_Init();
    OLED_Init();
    // ATGM_StructInit();
    USART1_Init(115200);
    // USART2_Init(9600);
    SHT3X_Init(0x44);
    // MPU6050_Init();
    // Key_init();
    // OLED_ShowString(1, 1, "MODE:OFF");

    while (1) {
        Delay_ms(200);
        SHT3X_GetTempAndHumi(&temperature, &humidity, REPEATAB_HIGH, MODE_CLKSTRETCH, 50);
        // OLED_ShowString(1, 1, "temperature");
        OLED_ShowNum(10, 1, (int)temperature, 5);
        // OLED_ShowString(20, 1, "humidity");
        OLED_ShowNum(20, 1, (int)humidity, 5);
    }

    // while (1) {
    //     switch (Mode_state) {
    //         case 1:
    //             if (Alarm_init_switch == 0) {
    //                 Delay_s(1);
    //                 MPU6050_Alarm_init();
    //                 OLED_ShowString(10, 1, "Alarm...");
    //                 Alarm_init_switch = 1; // 初始化已经完成
    //             }
    //             Delay_ms(80);

    //             MPU6050_detect();
    //             if (Alarm_open) {
    //                 OLED_ShowString(10, 1, "Alarm open!");
    //                 // USART2_Printf("alarm open");
    //                 ParseGps();       // 解析接收
    //                 printGpsBuffer(); // 处理接收
    //             }
    //             break;
    //         case 2:
    //             LED_open();
    //             break;
    //         default:
    //             LED_close();
    //             break;
    //     }
    // }
}
