#include "stm32f10x_conf.h"
#include "APP.h"
#include "Task.h"

// u8 Mode_state        = 0; // ģʽ�л���0�ǹرգ�1�Ƿ���ģʽ��2�ǳ���
// u8 Alarm_init_switch = 0; // ��������ʱ�ĳ�ʼ����0δ��ɣ�1���
// u8 Alarm_open        = 0; // �Ƿ񴥷�����������1δ����0

int main(void)
{
    float temperature; // temperature [��C]
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
    //                 Alarm_init_switch = 1; // ��ʼ���Ѿ����
    //             }
    //             Delay_ms(80);

    //             MPU6050_detect();
    //             if (Alarm_open) {
    //                 OLED_ShowString(10, 1, "Alarm open!");
    //                 // USART2_Printf("alarm open");
    //                 ParseGps();       // ��������
    //                 printGpsBuffer(); // �������
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
