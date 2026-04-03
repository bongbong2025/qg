#include <REGX52.H>
#include "Delay.h"
#include "UART.h"
#include "eeprom.h"
//宏定义 eeprom的地址
#define EEPROM_ADDR 0

//函数声明
void show_proce(void);

//定义储存数据的变量
unsigned char eeprom_dat;
unsigned char uart_dat;
unsigned char RI_Flag;

void main(void)
{
	Uart_Init();

	while(1)
	{
		show_proce();
		Delayms(1000);
	}
	
}



void UART_Routine() interrupt 4
{
	if(RI == 1)	//串口发送判断
	{
		uart_dat = SBUF;//读取串口发送的数据
		RI_Flag = 1;	//串口发送标志位
		RI = 0;	//手动还原串口发送
	}
}

void show_proce(void)
{
	unsigned char temp_dat = 0;
	if(RI_Flag)	//串口发送数据判断标志位
	{
		eeprom_write_onebyte(EEPROM_ADDR,uart_dat);	//将串口发送的数据写入eeprom
		temp_dat = eeprom_read_onebyte(EEPROM_ADDR);//读取eeprom中的数据
		eeprom_dat = temp_dat;
		RI_Flag = 0;	//串口发送标志位清除
	}
	UART_SendByte(eeprom_dat);	//发送eeprom储存的数据
}
