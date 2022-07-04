#ifndef _TIMER1_H
#define _TIMER1_H

#include "public.h"


//变量声明
extern u8 gmsec;//ms级定义
extern u8 gsec;//秒定义
extern u8 gmin;//分定义
extern u8 gshi;//时定义
extern u8 year;
extern u8 mouth;
extern u8  day;
//函数声明
void Timer1_init(void);
void Timer1_stop(void);
void Timer1_start(void);
#endif
