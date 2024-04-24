#ifndef __MPUIIC_H
#define __MPUIIC_H

#include "stm32f10x.h"

// IO��������
// #define MPU_SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
// #define MPU_SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

// ��ʱ��ֲλ��������Ҫ�ĺ궨��
#define GPIOB_ODR_Addr         (GPIOB_BASE + 12) // 0x40010C0C
#define GPIOB_IDR_Addr         (GPIOB_BASE + 8)  // 0x40010C08

#define BITBAND(addr, bitnum)  ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr)         *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))

#define PBout(n)               BIT_ADDR(GPIOB_ODR_Addr, n) // ���
#define PBin(n)                BIT_ADDR(GPIOB_IDR_Addr, n) // ����

// IO��������
#define MPU_IIC_SCL  PBout(8) // SCL
#define MPU_IIC_SDA  PBout(9) // SDA
#define MPU_READ_SDA PBin(9)  // ����SDA

void MPU_SDA_IN(void);
void MPU_SDA_OUT(void);

// IIC���в�������
void MPU_IIC_Delay(void);                // MPU IIC��ʱ����
void MPU_IIC_Init(void);                 // ��ʼ��IIC��IO��
void MPU_IIC_Start(void);                // ����IIC��ʼ�ź�
void MPU_IIC_Stop(void);                 // ����IICֹͣ�ź�
void MPU_IIC_Send_Byte(u8 txd);          // IIC����һ���ֽ�
u8 MPU_IIC_Read_Byte(); // IIC��ȡһ���ֽ�
u8 MPU_IIC_Wait_Ack(void);               // IIC�ȴ�ACK�ź�
void MPU_IIC_Ack(void);                  // IIC����ACK�ź�
void MPU_IIC_NAck(void);                 // IIC������ACK�ź�

void IMPU_IC_Write_One_Byte(u8 daddr, u8 addr, u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr, u8 addr);

#endif
