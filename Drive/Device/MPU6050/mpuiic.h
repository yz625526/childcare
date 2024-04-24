#ifndef __MPUIIC_H
#define __MPUIIC_H

#include "stm32f10x.h"

// IO方向设置
// #define MPU_SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
// #define MPU_SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

// 临时移植位带操作需要的宏定义
#define GPIOB_ODR_Addr         (GPIOB_BASE + 12) // 0x40010C0C
#define GPIOB_IDR_Addr         (GPIOB_BASE + 8)  // 0x40010C08

#define BITBAND(addr, bitnum)  ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr)         *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))

#define PBout(n)               BIT_ADDR(GPIOB_ODR_Addr, n) // 输出
#define PBin(n)                BIT_ADDR(GPIOB_IDR_Addr, n) // 输入

// IO操作函数
#define MPU_IIC_SCL  PBout(8) // SCL
#define MPU_IIC_SDA  PBout(9) // SDA
#define MPU_READ_SDA PBin(9)  // 输入SDA

void MPU_SDA_IN(void);
void MPU_SDA_OUT(void);

// IIC所有操作函数
void MPU_IIC_Delay(void);                // MPU IIC延时函数
void MPU_IIC_Init(void);                 // 初始化IIC的IO口
void MPU_IIC_Start(void);                // 发送IIC开始信号
void MPU_IIC_Stop(void);                 // 发送IIC停止信号
void MPU_IIC_Send_Byte(u8 txd);          // IIC发送一个字节
u8 MPU_IIC_Read_Byte(); // IIC读取一个字节
u8 MPU_IIC_Wait_Ack(void);               // IIC等待ACK信号
void MPU_IIC_Ack(void);                  // IIC发送ACK信号
void MPU_IIC_NAck(void);                 // IIC不发送ACK信号

void IMPU_IC_Write_One_Byte(u8 daddr, u8 addr, u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr, u8 addr);

#endif
