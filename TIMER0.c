#include "TIMER0.h"

void Timer0_start(void)
{
	TR0=1;//打开定时器	
}

/*******************************************************************************
* 函 数 名       : time0_stop
* 函数功能		 : 定时器0关闭
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void Timer0_stop(void)
{
	TR0=0;//关闭定时器
	TH0=0X00;
	TL0=0X00;	
}


void Timer0_init()
{
	TMOD|=0X10;//选择为定时器0模式，工作方式1
	TH0=0xDC;//给定时器赋初值，定时10ms
	TL0=0x00;	
	ET0=1;//打开定时器1中断允许
	EA=1;//打开总中断
	TR0=0;//关闭定时器	
	}