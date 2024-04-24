#include "APP_GPS.h"

// GPS调度初始化
void GPS_APP_init()
{
    ATGM_StructInit();

    USART2_Init(9600);
}

// GPS调度核心逻辑
void GPS_read()
{
    ParseGps();
    printGpsBuffer();
}
