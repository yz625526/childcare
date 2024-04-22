#include "APP_UART_Send.h"

void APP_Uart_send_init()
{
    USART1_Init(115200);
    USART2_Init(9600);
    USART2_Printf("init done ");
}

void Uart_send_AIR780()
{
    // USART2_Printf("IndoorTemperature:%d", (int)temperature);
}