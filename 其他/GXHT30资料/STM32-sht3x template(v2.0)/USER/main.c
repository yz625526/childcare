/*
 * �ļ����ƣ�main
 * ��    �ߣ�Anyint
 * ��    ����v1.0
 * ˵    ��������ģ��
 * �޸ļ�¼��2019/07/19 ����ģ��
*/

#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "sht3x.h"
#include "system.h"

/*
 * �������ƣ�mian
 * �������ܣ���������������ں���
 * ��ڲ�����void
 * ���ڲ�����int
 * ��    ע��
*/
int main(void)
{
    ft	temperature;        // temperature [��C]
    ft	humidity;	        // relative humidity [%RH]
    etError   error;        // error code
    delay_init();
    uart_init(9600);
    SHT3X_Init(0x44);
    delay_ms(50);
    
    while(1)
    {
        SHT3X_GetTempAndHumi(&temperature, &humidity, REPEATAB_HIGH, MODE_CLKSTRETCH, 50);
        printf("temperature=%.1f��\thumidity=%.1f%%RH\terror=%d\r\n",(float)temperature,(float)humidity,(u8)error);
    }
}
