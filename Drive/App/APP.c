#include "APP.h"
#include "Task_use_TIM.h"

// 调度初始化
void SYS_Init(void)
{
    GPS_APP_init();

    Tim_task_init(); // 启动调度
}
