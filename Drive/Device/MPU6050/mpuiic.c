#include "mpuiic.h"
#include "Delay.h"

void MyI2C_W_SCL(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)BitValue);
    Delay_us(10);
}

void MyI2C_W_SDA(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)BitValue);
    Delay_us(10);
}

uint8_t MyI2C_R_SDA(void)
{
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    Delay_us(10);
    return BitValue;
}

// 初始化IIC
// SCL B8 SDA B9
void MPU_IIC_Init(void)
{
    // SCL--B10,SDA--B11
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
}

// 产生IIC起始信号
void MPU_IIC_Start(void)
{
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(0);
}
// 产生IIC停止信号
void MPU_IIC_Stop(void)
{
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);
}
// 等待应答信号到来
// 返回值：1，接收应答失败
//         0，接收应答成功
u8 MPU_IIC_Wait_Ack(void)
{
    uint8_t AckBit;
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);
    AckBit = MyI2C_R_SDA();
    MyI2C_W_SCL(0);
    return AckBit;
}

// 产生ACK应答
// void MPU_IIC_Ack(void)
// {
//     MPU_IIC_SCL = 0;
//     MPU_SDA_OUT();
//     MPU_IIC_SDA = 0;
//     MPU_IIC_Delay();
//     MPU_IIC_SCL = 1;
//     MPU_IIC_Delay();
//     MPU_IIC_SCL = 0;
// }
// // 不产生ACK应答
// void MPU_IIC_NAck(void)
// {
//     MPU_IIC_SCL = 0;
//     MPU_SDA_OUT();
//     MPU_IIC_SDA = 1;
//     MPU_IIC_Delay();
//     MPU_IIC_SCL = 1;
//     MPU_IIC_Delay();
//     MPU_IIC_SCL = 0;
// }

// IIC发送一个字节
// 返回从机有无应答
// 1，有应答
// 0，无应答
void MPU_IIC_Send_Byte(u8 txd)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        MyI2C_W_SDA(txd & (0x80 >> i));
        MyI2C_W_SCL(1);
        MyI2C_W_SCL(0);
    }
}
// 读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 MPU_IIC_Read_Byte()
{

    uint8_t i, Byte = 0x00;
    MyI2C_W_SDA(1);
    for (i = 0; i < 8; i++) {
        MyI2C_W_SCL(1);
        if (MyI2C_R_SDA() == 1) { Byte |= (0x80 >> i); }
        MyI2C_W_SCL(0);
    }
    return Byte;
}
