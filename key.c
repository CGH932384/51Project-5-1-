#include <REGX52.H>
#include "Delay.h"


unsigned char MatrixKey()
{
	unsigned char KeyValue=0;
	P1=0x0f; 
	if(P1!=0x0f)//��ȡ�����Ƿ���
	{
		if(P1!=0x0f)//�ٴμ���Ƿ���
        {
			//������
			P1=0x0f;
			switch(P1) 
            { case(0X07): KeyValue=1;break;
              case(0X0b): KeyValue=2;Delay(100);break; 
              case(0X0d): KeyValue=3;Delay(100);break; 
              case(0X0e): KeyValue=4;Delay(100);break;
			}
			//������
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
