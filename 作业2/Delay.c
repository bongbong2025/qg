#include <REGX52.H>
#include "intrins.h"

void Delayms(unsigned int ms)	//延迟毫秒
{
	unsigned char i, j;
	while(ms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

void Delay10us(unsigned int us)	//延迟微秒
{
	unsigned char i;
	while(us--)
	{
		_nop_();
		i = 2;
		while (--i);
	}
}
