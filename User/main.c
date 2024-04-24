#include "stm32f10x_conf.h"

int main(void)
{
    float temperature; // temperature [°„C]
    float humidity;    // relative humidity [%RH]

    LED_Init();
    OLED_Init();
    ATGM_StructInit();
    USART1_Init(115200);
    USART2_Init(9600);
    SHT3X_Init(0x44);
    // // MPU6050_Init();
    // // Key_init();
    // // OLED_ShowString(1, 1, "MODE:OFF");

    while (1) {
        Delay_ms(100);
        //     // OLED_Clear();
        SHT3X_GetTempAndHumi(&temperature, &humidity, REPEATAB_HIGH, MODE_CLKSTRETCH, 50);
        // OLED_ShowString(1, 1, "temperature");
        OLED_ShowNum(1, 1, (int)temperature, 5);
        // OLED_ShowString(20, 1, "humidity");
        OLED_ShowNum(2, 1, (int)humidity, 5);
    }
}
