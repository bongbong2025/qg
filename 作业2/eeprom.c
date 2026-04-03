#include <REGX52.H>
#include "IIC.h"
#include "Delay.h"

void eeprom_write_onebyte(unsigned char addr, unsigned char dat)
{
	IIC_Start();		//开启I2C总线
	IIC_WriteByte(0xA0);//写入模式
	IIC_WaitAck();
	IIC_WriteByte(addr);//写入eeprom的地址
	IIC_WaitAck();
	IIC_WriteByte(dat);	//写入相关数据
	IIC_WaitAck();
	IIC_Stop();			//关闭I2C总线
	Delayms(10);		//延时防止数据传输不完全
}

unsigned char eeprom_read_onebyte(unsigned char addr)
{
	unsigned char temp = 0;
	
	IIC_Start();		//开启总线
	IIC_WriteByte(0xA0);//写入模式
	IIC_WaitAck();
	IIC_WriteByte(addr);//写入eeprom存储地址
	IIC_WaitAck();
	IIC_Start();		//重新开启总线，改变数据传输方向
	IIC_WriteByte(0xA1);//读取模式
	IIC_WaitAck();
	temp = IIC_ReadByte(0);	//读取eeprom存储的数据
	IIC_Stop();			//关闭总线
	return temp;		//返回eeprom中的数据
}
