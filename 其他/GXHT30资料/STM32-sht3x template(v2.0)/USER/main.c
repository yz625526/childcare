/*
 * 文件名称：main
 * 作    者：Anyint
 * 版    本：v1.0
 * 说    明：工程模板
 * 修改记录：2019/07/19 建立模板
*/

#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "sht3x.h"
#include "system.h"

/*
 * 函数名称：mian
 * 函数功能：主函数，程序入口函数
 * 入口参数：void
 * 出口参数：int
 * 备    注：
*/
int main(void)
{
    ft	temperature;        // temperature [°C]
    ft	humidity;	        // relative humidity [%RH]
    etError   error;        // error code
    delay_init();
    uart_init(9600);
    SHT3X_Init(0x44);
    delay_ms(50);
    
    while(1)
    {
        SHT3X_GetTempAndHumi(&temperature, &humidity, REPEATAB_HIGH, MODE_CLKSTRETCH, 50);
        printf("temperature=%.1f℃\thumidity=%.1f%%RH\terror=%d\r\n",(float)temperature,(float)humidity,(u8)error);
    }
}
