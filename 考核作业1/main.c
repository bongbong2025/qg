#include <REGX52.H>
#include <INTRINS.H>

#define MAX_TASKS 2 //表示有两个任务
#define MAX_TASK_DEP 32//表示栈的深度

unsigned char idata task_sp[MAX_TASKS];//任务的堆栈指针（存任务的）
unsigned char idata task_stack[MAX_TASKS][MAX_TASK_DEP];//每个task任务的堆栈
unsigned char task_id;//当前任务号

unsigned int T1Count, T2Count;
unsigned char task1_flag, task2_flag;

void Delay1000ms(void);	//延时函数	
void task_switch(void);//任务切换
void task0(void);
void task1(void);
void task_load(unsigned int fn,unsigned char tid);
void Timer0Init(void);

void main()
{
	Timer0Init();
	task_load(task0,0);
	task_load(task1,1);
	task_id = 0;
	SP=task_sp[0];
}

void Delay1000ms()		
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 154;
	k = 122;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void task_switch()
{
   task_sp[task_id]=SP;
	
	task_id=task_id+1;
	if(task_id==MAX_TASKS)	//防止任务溢出，切换为任务1
	{
	  task_id=0;
	}
	SP=task_sp[task_id];
}

void task0()
{
	P1_0=0;
  while(1)
	{
		if(task1_flag)
		{
			P1_0=~P1_0;	//改变灯的状态
			task1_flag = 0;	//标志位清零，等待下一次标志位变化
		}
		task_switch();
	}
}

void task1()
{
	P1_7=0;
  while(1)
	{
		if(task2_flag)
		{
			P1_7=~P1_7;	//改变灯的状态
			task2_flag = 0;	//标志位清零，等待下一次标志位变化
		}
		task_switch();
	}
}
	
void task_load(unsigned int fn,unsigned char tid)
{
  //task_sp[tid]=  task_stack[tid]+1;//跳到下一个任务
	task_stack[tid][1] = (unsigned char)(fn >> 8); 
	task_stack[tid][0] = (unsigned char)fn;  
	task_sp[tid] = (unsigned char)&task_stack[tid][1];
}

void Timer0Init(void)		//定时器初始化
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;		//打开中断
	EA = 1;			
	PT0 = 0;		//优先级配置
	
}

void Timer0_Routine() interrupt 1
{
	//重新赋初始值，为了让计时器更准确的计时
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T1Count ++;
	T2Count ++;
	if(T1Count >= 500) 	//500毫秒改变一次标志位
	{
		task1_flag = 1;
		T1Count = 0;
	}
	if(T2Count >= 1000)	//1s改变一次标志位
	{
		task2_flag = 1;
		T2Count = 0;
	}
		
}
