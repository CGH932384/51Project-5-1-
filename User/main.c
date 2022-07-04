#include "public.h"
#include "lcd1602.h"
#include "key.h"
#include "Timer0.h"
#include "TImer1.h"
#include "mkey.h"
#include "ired.h"
#include "string.h"
#include "beep.h"
#include "AT24C02.h"
#define sjia		0x08
#define sjian		0x1C
#define fjia		0x42
#define fjian		0x52
 char choice=0,choice2=0,choice3=0;
unsigned char KeyValue;
unsigned char key;
unsigned char shan=0;
unsigned char mode=0;
unsigned char ok=0;
unsigned char temp=0;
unsigned char keynum,Runflag;
unsigned char timeSetSelect,timeSetFlashFlag,Value;
unsigned char time[11];
unsigned char ctime[11];
unsigned char timec[9];
char  w;
u8 time_buf[9];
u8 ired_tempx=0;
u8 cshi=8;//ms级定义
u8 csec=10;//秒定义
u8 cmin=17;//分定义
u8 cyear=22;
u8 cmouth=6;
u8  cday=29;
/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void set()
{	

if(choice==1&&shan==1&&choice2!=1&&choice2!=2&&choice3==0)
{
	lcd1602_show_string(0,0," ");
	
}

if(choice==2&&shan==1&&choice2!=1&&choice2!=2&&choice3==0)
{
lcd1602_show_string(0,1," ");

}	

if(choice==2&&shan==1&&choice2==2&&choice2!=1&&choice3==0)
{
lcd1602_show_string(0,1," ");}

if(choice==1&&shan==1&&choice2==1&&choice2!=2&&choice3==0)
{
lcd1602_show_string(0,0," ");}

	if(choice==1&&shan==1&&choice2==2&&choice2!=1&&choice3==0)
{
lcd1602_show_string(0,0," ");}

if(choice ==2&&shan==1&&choice2==1&&choice2!=2&&choice3==0)
{
lcd1602_show_string(0,1," ");}

if(choice==1&&choice2==2&&shan!=1&&choice3==0){lcd1602_show_string(0,0,"1.Scloc");lcd1602_show_string(0,1,"2.Salar");}
if(choice==2&&choice2==2&&shan!=1&&choice3==0){lcd1602_show_string(0,0,"1.Scloc");lcd1602_show_string(0,1,"2.Salar");}

if (choice==1&&choice2==1&&shan!=1&&choice3==0){lcd1602_show_string(0,0,"1.clock");lcd1602_show_string(0,1,"2.alarm");}
if (choice==2&&choice2==1&&shan!=1&&choice3==0){lcd1602_show_string(0,0,"1.clock");lcd1602_show_string(0,1,"2.alarm");}
if(choice3!=1&&choice3!=2&&choice2!=1&&choice2!=2&&shan!=1)
{
	lcd1602_show_string(0,0,"1.ShowT");
lcd1602_show_string(0,1,"2.SettT");
}
}




void showtime()
{
	u8 temp,temp1;
	u8  W[4];
	
	if(mouth==1)
	{temp=mouth;temp1=year;
		mouth=13;year=year-1;
	w=(day+2*mouth+3*(mouth+1)/5+year+year/4-year/100+year/400)%7;
	mouth=temp;year=temp1;}
	if(mouth==2)
	{temp=mouth;temp1=year;
		mouth=14;year=year-1;
	w=(day+2*mouth+3*(mouth+1)/5+year+year/4-year/100+year/400)%7;
	mouth=temp;year=temp1;}
	else w=(day+2*mouth+3*(mouth+1)/5+year+year/4-year/100+year/400)%7;
	time_buf[0]=gshi/10+0x30;
		time_buf[1]=gshi%10+0x30;//分
		time_buf[2]=':';//-
		time_buf[3]=gmin/10+0x30;
		time_buf[4]=gmin%10+0x30;//秒
		time_buf[5]=':';//-
		time_buf[6]=gsec/10+0x30;
		time_buf[7]=gsec%10+0x30;//毫秒
		time_buf[8]='\0';
	time[0]=2+0x30;
	time[1]=0+0x30;
	time[2]=year/10+0x30;
	time[3]=year%10+0x30;
	time[4]='-';
	time[5]=mouth/10+0x30;
	time[6]=mouth%10+0x30;
	time[7]='-';
	time[8]=day/10+0x30;
	time[9]=day%10+0x30;
	time[10]='\0';
	W[2]=w+0x31;
	W[0]=0x57;
	W[1]=':';
	W[3]='\0';
lcd1602_show_string(0,0,time);
	lcd1602_show_string(0,1,time_buf);
	lcd1602_show_string(12,0,W);
}


void showclock()
{
	ctime[0]=2+0x30;
	ctime[1]=0+0x30;
	ctime[2]=cyear/10+0x30;
	ctime[3]=cyear%10+0x30;
	ctime[4]='-';
	ctime[5]=cmouth/10+0x30;
	ctime[6]=cmouth%10+0x30;
	ctime[7]='-';
	ctime[8]=cday/10+0x30;
	ctime[9]=cday%10+0x30;
	ctime[10]='\0';
	timec[0]=cshi/10+0x30;
		timec[1]=cshi%10+0x30;//分
		timec[2]=':';//-
		timec[3]=cmin/10+0x30;
		timec[4]=cmin%10+0x30;//秒
		timec[5]=':';//-
		timec[6]=csec/10+0x30;
		timec[7]=csec%10+0x30;//毫秒
		timec[8]='\0';
	lcd1602_show_string(12,0,"C"); 
	lcd1602_show_string(0,0,ctime); 
	lcd1602_show_string(0,1,timec);
}	
	
	void init()
	{gshi=AT24C02_ReadByte(0);
	gmin=AT24C02_ReadByte(1);
	gsec=AT24C02_ReadByte(2);
		year=AT24C02_ReadByte(3);
	mouth=AT24C02_ReadByte(4);
	day=AT24C02_ReadByte(5);
	}
	
	void init1()
	{
		AT24C02_WriteByte(0,gshi);
		delay_ms(5);
		AT24C02_WriteByte(1,gmin);
		delay_ms(5);
		AT24C02_WriteByte(2,gsec);
		delay_ms(5);
		AT24C02_WriteByte(3,year);
		delay_ms(5);
		AT24C02_WriteByte(4,mouth);
		delay_ms(5);
		AT24C02_WriteByte(5,day);
		delay_ms(5);
	}

void panduan()
{	
if(key==KEY1_PRESS){choice++;}
if(key==KEY4_PRESS){
if(choice2==2&&mode==0)choice2=0;else choice2--; 
if(mode==1||mode==2||mode==3||mode==4)lcd1602_show_string(0,0,"   			          ");lcd1602_show_string(0,1,"             ");mode=0;
}
if(choice2<=0){choice2=0;}
if(choice3<=0){choice3=0;}
if(key==KEY3_PRESS){
	if(choice2!=1&&choice2!=2&&choice==1&&shan==1)choice2=1;
	if(choice2!=1&&choice2!=2&&choice==2&&shan==1)choice2=2;
	
}
if(key==KEY2_PRESS)
	{	
		if(choice==1&&choice2==1)mode=1;
		if(choice==1&&choice2==2)mode=2;
		if(choice==2&&choice2==1)mode=3;
		if(choice==2&&choice2==2)mode=4;
	}
	
if(choice>2){choice=0;}
if(choice2>2){choice=0;}
if(mode>4){mode=0;}
if((year==cyear)&&(gshi==cshi)&&(gmin==cmin)&&(gsec==csec)&&(mouth==cmouth)&&(day==cday))
{beep_alarm(100000,10);}
			
}
		
		
 void settime()
 {Value=MatrixKey();
		switch(Value)
						{
									case 1:gshi++;if(gshi>=24)gshi=0;Value=0;delay_ms(10); break;
									case 2:if(gshi==0)gshi=24;gshi--;Value=0;delay_ms(10); break;
									case 3:gmin++;if(gmin>=60)gmin=0;Value=0;delay_ms(10); break;
									case 4:if(gmin==0)gmin=60;gmin--;Value=0;delay_ms(10); break;
									case 5:year++;if(year>=100)year=0;Value=0;delay_ms(10); break;
									case 6:if(year==0)year=100;year--;Value=0;delay_ms(10); break;
									case 7:mouth++;if(mouth==13){year++;mouth=1;day=1;}Value=0;delay_ms(10); break;
									case 8:if(mouth==1)mouth=13;mouth--;Value=0;delay_ms(10); break;
									case 9:day++;if((year%4)==0&&mouth==2&&day>29){mouth++;day=1;} 
														if(mouth==12&&day>31){mouth=1;day=1;year++;}
														if(day>=32){mouth++;day=1;}
														 if((mouth==4||mouth==6||mouth==9||mouth==11)&&day>30){day=1;mouth++;}
if((year%4)!=0&&mouth==2&&day>28){mouth++;day=1;}Value=0;delay_ms(10); break;
									case 10:if(day==1)day=32;day--;Value=0;delay_ms(10); break;
									default:break;
									}
 if(ired_tempx==sjia)//如果是第一键按下
		{
			gired_data[2]=0;//清零,等待下次按键按下
			gshi++;
			if(gshi>=24)gshi=0;
		}
		else if(ired_tempx==sjian)//如果是第一键按下
		{
			gired_data[2]=0;//清零,等待下次按键按下
			if(gshi==0)gshi=24;gshi--;
		}
		else if(ired_tempx==fjia)//如果是第一键按下
		{
			gired_data[2]=0;//清零,等待下次按键按下
			gmin++;
		if(gmin>=60)gmin=0;
			
		}
		else if(ired_tempx==fjian)//如果是第一键按下
		{
			gired_data[2]=0;//清零,等待下次按键按下
			if(gmin==0)gmin=60;	gmin--;}
		}
void csettime()
 {Value=MatrixKey();
		switch(Value)
						{
								
									case 1:cshi++;if(cshi>=24)cshi=0;Value=0;delay_ms(10); break;
									case 2:if(cshi==0)cshi=24;cshi--;Value=0;delay_ms(10); break;
									case 3:cmin++;if(cmin>=60)cmin=0;Value=0;delay_ms(10); break;
									case 4:if(cmin==0)cmin=60;cmin--;Value=0;delay_ms(10); break;
									case 5:cyear++;if(cyear>=100)cyear=0;Value=0;delay_ms(10); break;
									case 6:if(cyear==0)cyear=100;cyear--;Value=0;delay_ms(10); break;
									case 7:cmouth++;if(cmouth==13){cyear++;cmouth=1;cday=1;}Value=0;delay_ms(10); break;
									case 8:if(cmouth==1)cmouth=13;cmouth--;Value=0;delay_ms(10); break;
									case 9:cday++;if((cyear%4)==0&&cmouth==2&&cday>29){cmouth++;cday=1;} 
														if(cmouth==12&&cday>31){cmouth=1;cday=1;cyear++;}
														if(cday>=32){cmouth++;cday=1;}
														 if((cmouth==4||cmouth==6||cmouth==9||cmouth==11)&&cday>30){cday=1;cmouth++;}
if((cyear%4)!=0&&cmouth==2&&cday>28){cmouth++;cday=1;}Value=0;delay_ms(10); break;
									case 10:if(cday==1)cday=32;cday--;Value=0;delay_ms(10); break;
									default:break;
									}   
 if(ired_tempx==sjia)//如果是第一键按下
		{
			gired_data[2]=0;//清零,等待下次按键按下
			cshi++;
			if(cshi>=24)cshi=0;
		}
		else if(ired_tempx==sjian)//如果是第一键按下
		{
			gired_data[2]=0;//清零,等待下次按键按下
			if(cshi==0)cshi=24;cshi--;
		}
		else if(ired_tempx==fjia)//如果是第一键按下
		{
			gired_data[2]=0;//清零,等待下次按键按下
			cmin++;
		if(cmin>=60)cmin=0;
			
		}
		else if(ired_tempx==fjian)//如果是第一键按下
		{
			gired_data[2]=0;//清零,等待下次按键按下
			if(cmin==0)cmin=60;	cmin--;}
		}
void main()
{	unsigned char MatrixKey();
	init();
	lcd1602_init();//LCD1602初始化
	Timer0_init();
	Timer1_init();
	Timer0_start();
	Timer1_start();
	ired_init();
	
	while(1)
	{		ired_tempx=gired_data[2];
		
		panduan();
	init1();
		key = key_scan(0);
							
									
									switch(mode)
									{	case 0:set();	break;	
										case 2:showtime();settime();break;
										case 1:showtime();break;
										case 3:showclock();break;
										case 4:showclock();csettime();break;
									}
												
		
		
		
	}	
	
}
	








































void Timer0_Routine() interrupt 1 
{
	static unsigned int i=0;
	TH0=0xDC;//给定时器赋初值，定时10ms
	TL0=0x00;
	i++;
	
	if (i >= 500)
	{
		i = 0;
		shan = !shan;
		
		
	}
}