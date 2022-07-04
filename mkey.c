#include <REGX52.H>
#include "Delay.h"




unsigned char MatrixKey()
{
	unsigned char KeyValue=0;
	P1=0x0f; 
	if(P1!=0x0f)//读取按键是否按下
	{
		if(P1!=0x0f)//再次检测是否按下
        {
			//测试列
			P1=0x0f;
			switch(P1) 
            { case(0X07): KeyValue=1;break;
              case(0X0b): KeyValue=2;Delay(10);break; 
              case(0X0d): KeyValue=3;Delay(10);break; 
              case(0X0e): KeyValue=4;Delay(10);break;
			}
			//测试行
			P1=0XF0;
			switch(P1) 
			{ case(0X70): KeyValue=KeyValue;break; 
			  case(0Xb0): KeyValue=KeyValue+4;break; 
			  case(0Xd0): KeyValue=KeyValue+8;break;
			  case(0Xe0): KeyValue=KeyValue+12;break; 
			}
 	  } 
   }
	return KeyValue;
}

