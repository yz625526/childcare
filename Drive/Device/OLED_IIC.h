#ifndef _OLED_IIC_H_
#define _OLED_IIC_H_

#include 
//-----------------IIC端口定义----------------
//定义SCL
//PA5
#define MYIIC_SCL_GPIO_RCC	RCC_APB2Periph_GPIOA
#define MYIIC_SCL_GPIO_PIN	GPIO_Pin_5
#define MYIIC_SCL_GPIO			GPIOA
//定义SDA
//PA7
#define MYIIC_SDA_GPIO_RCC	RCC_APB2Periph_GPIOA
#define MYIIC_SDA_GPIO_PIN	GPIO_Pin_7
#define MYIIC_SDA_GPIO			GPIOA


//传输的数据:  开始                  1            0                停止
// SDA: H  _______             ______                            ______
//		  L       \___________/      \__________________________/
// SCL: H	 ____________         ____         ____	          ___________
//		  L	             \_______/    \_______/    \_________/


//IO方向设置
/*CRL{0}表示低位八个IO，CRH{8}表示高位八个IO，每个IO占四位(0xF)，CRL&=0X0FFFFFFF表示将低位第[7]位({0}+[7]=7)IO配置清零，CRL|=0X80000000表示配置低位第[7]位作为输入，0X30000000配置为输出。*/
#define SDA_IN()  {MYIIC_SDA_GPIO->CRL&=0X0FFFFFFF;MYIIC_SDA_GPIO->CRL|=0X80000000;}
#define SDA_OUT() {MYIIC_SDA_GPIO->CRL&=0X0FFFFFFF;MYIIC_SDA_GPIO->CRL|=0X30000000;}

//IO操作函数
// #define IIC_SCL    PAout(5) //SCL
// #define IIC_SDA    PAout(7) //SDA
// #define READ_SDA   PAin(7)  //输入SDA
#define IIC_SCL GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define IIC_SDA    PAout(7) //SDA

//应答
#define ACK		1
#define NACK	0

//MYIIC指令
#define MYIIC_CMD  0	//写命令
#define MYIIC_DATA 1	//写数据


//IIC驱动函数
void MYIIC_Start(void);
void MYIIC_Stop(void);
void MYIIC_Write_Byte(u8 IIC_Byte);
u8 	 MYIIC_Read_Byte(u8 ack);
u8 	 MYIIC_Wait_Ack(void);
void MYIIC_Ack(void);
void MYIIC_NAck(void);
void MYIIC_InitGPIO(void);


#endif
