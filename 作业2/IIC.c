#include <REGX52.H>
#include <intrins.h>
#include "Delay.h"

sbit IIC_SCL = P2^1;
sbit IIC_SDA = P2^0;

void IIC_Start(void)	//开启I2C总线，SDA由高电平变为低电平
{
	IIC_SCL = 1;
	IIC_SDA = 1;
	Delay10us(1);
	IIC_SDA = 0;
	Delay10us(1);
	IIC_SCL = 0;
}

void IIC_Stop(void)		//关闭I2C总线，SDA由低电平变为高电平
{
	IIC_SCL = 1;
	IIC_SDA = 0;
	Delay10us(1);
	IIC_SDA = 1;
	Delay10us(1);
}

void IIC_Ack(void)		//主机和从机的响应函数
{
	IIC_SCL = 0;
	IIC_SDA = 0;
	Delay10us(1);
	IIC_SCL = 1;
	Delay10us(1);
	IIC_SCL = 0;
}

void IIC_NotAck(void)	//非响应函数
{
	IIC_SCL = 0;
	IIC_SDA = 1;
	Delay10us(1);
	IIC_SCL = 1;
	Delay10us(1);
	IIC_SCL = 0;
}

//SDA置1为非响应，置0为响应，且都将SCL先拉高后降低

unsigned char IIC_WaitAck(void)	//响应等待，判断主从机之间是否有响应
{
	unsigned char tim = 0;
	IIC_SCL = 1;
	Delay10us(1);
	while(IIC_SDA)
	{
		tim++;
		if(tim > 100)			//设定的超时时间
		{
			IIC_Stop();			//超时则停止I2C总线的占用
			return 1;
		}
	}
	IIC_SCL = 0;
	return 0;					//成功响应则跳出函数
}

void IIC_WriteByte(unsigned char dat)
{
	unsigned char i;
	
	IIC_SCL = 0;
	for(i = 0; i < 8; i++)		//逐位写入数据
	{
		if(dat &= 0x80) IIC_SDA = 1;
		else IIC_SDA = 0;
		dat <<= 1;				//左移调整录入位次
		IIC_SCL = 1;
		Delay10us(1);
		IIC_SCL = 0;			//延时捕获电平变化
		Delay10us(1);
	}
}

unsigned char IIC_ReadByte(unsigned char ack)
{
	unsigned char i;
	unsigned char receive = 0;
	
	for(i = 0; i < 8; i++)		//逐位读取数据
	{
		IIC_SCL = 0;
		Delay10us(1);
		IIC_SCL = 1;
		Delay10us(1);
		receive <<= 1;
		if(IIC_SDA) receive++;
	}
	
	if(!ack) IIC_NotAck();
	else IIC_Ack();
	
	return receive;				//返回eeprom中的数据
}
