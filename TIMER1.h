#ifndef _TIMER1_H
#define _TIMER1_H

#include "public.h"


//��������
extern u8 gmsec;//ms������
extern u8 gsec;//�붨��
extern u8 gmin;//�ֶ���
extern u8 gshi;//ʱ����
extern u8 year;
extern u8 mouth;
extern u8  day;
//��������
void Timer1_init(void);
void Timer1_stop(void);
void Timer1_start(void);
#endif
