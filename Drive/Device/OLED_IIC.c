#include "OLED_IIC.h"
#include "delay.h"
#include "Delay.h"

void MYIIC_Start() // IIC Start
{
    // SDA: H  _______
    //		  L			    \____
    // SCL: H	 ____________
    //		  L
    SDA_OUT(); // 将SDA线配置为输出
    // SCL保持高电平，SDA由高到低转变，为起始信号
    IIC_SDA = 1;
    IIC_SCL = 1;
    //	Delay_us(4);
    IIC_SDA = 0;
    // 钳住I2C总线，准备发送或接收数据
    //	Delay_us(4);
    IIC_SCL = 0;
}
void MYIIC_Stop(void) // IIC Stop
{
    // SDA: H  				_____
    //		  L	 ______/
    // SCL: H	     ________
    //		  L	 ___/
    SDA_OUT(); // sda线输出
    IIC_SCL = 0;
    IIC_SDA = 0;
    // 	Delay_us(4);
    // SCL保持高电平，SDA由低到高转变，为停止信号
    IIC_SCL = 1;
    IIC_SDA = 1;
    //	Delay_us(4);
}

u8 MYIIC_Wait_Ack(void)
{
    // 应答信号:SDA每发送（接收）八位数据，就要在第九位发送（接收）低电平的应答信号
    //  SDA: H  				______						  ______
    //		  L	 ______/第一位\____.....___/第八位\___________
    //  SCL: H	     		 ____								 ____			 ____
    //		  L	 _______/	1  \______.....___/	8  \____/	9  \__

    u8 ucErrTime = 0;
    SDA_IN(); // SDA设置为输入
    IIC_SDA = 1;
    Delay_us(1);
    IIC_SCL = 1;
    Delay_us(1);
    while (READ_SDA) {
        ucErrTime++;
        if (ucErrTime > 250) // 避免一直收不到应答信号而导致程序卡死
        {
            MYIIC_Stop();
            return 1;
        }
    }
    IIC_SCL = 0; // 时钟输出0
    return 0;

    //	IIC_SCL = 1;
    //	IIC_SCL = 0;
    //	return 0;
}
void MYIIC_Write_Byte(u8 IIC_Byte) // IIC Write byte
{
    // 传输的数据:					1						0
    //  SDA: H  				 ______
    //		  L	 _______/		   \______________
    //  SCL: H	     			____				 ____
    //		  L	 ________/		\_______/		 \__
    u8 t;
    SDA_OUT();
    IIC_SCL = 0; // 拉低时钟开始数据传输
    for (t = 0; t < 8; t++) {
        // 发送信号要保证SDA发送的每一位数据持续时间比SCL高电平时钟信号持续时间长，并且期间必须保持稳定
        if (IIC_Byte >= 0x80)
            IIC_SDA = 1;
        else
            IIC_SDA = 0;
        IIC_Byte <<= 1;
        //		Delay_us(2);
        IIC_SCL = 1;
        //		Delay_us(2);
        IIC_SCL = 0;
        //		Delay_us(2);
        // 一个周期，完成发送1bit数据，2/3高电位，1/3低电位为1, 1/3高电位， 2/3低电位为0
    }
}
u8 MYIIC_Read_Byte(u8 ack)
{
    u8 i, receive = 0;
    SDA_IN(); // SDA设置为输入
    for (i = 0; i < 8; i++) {
        IIC_SCL = 0;
        Delay_us(2);
        IIC_SCL = 1;
        receive <<= 1;
        if (READ_SDA) receive++;
        Delay_us(1);
    }
    if (!ack)
        MYIIC_NAck(); // 发送nACK
    else
        MYIIC_Ack(); // 发送ACK
    return receive;
}

// 产生ACK应答
void MYIIC_Ack(void)
{
    // SDA: H
    //		  L	__________
    // SCL: H		 ____
    //		  L	__/	   \__
    IIC_SCL = 0;
    SDA_OUT();
    IIC_SDA = 0;
    //	Delay_us(2);
    IIC_SCL = 1;
    //	Delay_us(2);
    IIC_SCL = 0;
}

// 不产生ACK应答
void MYIIC_NAck(void)
{
    // SDA: H		________
    //		  L	_/
    // SCL: H		 ____
    //		  L	__/	   \__
    IIC_SCL = 0;
    SDA_OUT();
    IIC_SDA = 1;
    //	Delay_us(2);
    IIC_SCL = 1;
    //	Delay_us(2);
    IIC_SCL = 0;
}

void MYIIC_InitGPIO(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(MYIIC_SCL_GPIO_RCC | MYIIC_SDA_GPIO_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = MYIIC_SCL_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MYIIC_SCL_GPIO, &GPIO_InitStructure);
    GPIO_SetBits(MYIIC_SCL_GPIO, MYIIC_SCL_GPIO_PIN);

    GPIO_InitStructure.GPIO_Pin   = MYIIC_SDA_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MYIIC_SDA_GPIO, &GPIO_InitStructure);
    GPIO_SetBits(MYIIC_SDA_GPIO, MYIIC_SDA_GPIO_PIN);
}