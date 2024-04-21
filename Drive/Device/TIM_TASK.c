#include "TIM_TASK.h"
#include "Task.h"

void Tim_task_init()
{
    SysTick_Config(SystemCoreClock / 1000); // 打开定时器，SystemCoreClock为系统时钟频率

    NVIC_SetPriority(SysTick_IRQn, 0); // 设置中断优先级0(默认分组情况下，优先级最高)
    NVIC_EnableIRQ(SysTick_IRQn);      // 开启SysTick定时器中断
}

void SysTick_Handler(void)
{
    Task_Marks_Handler_Callback();
}