#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char
uchar count=0;
void time0(void) interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;//重新装载计数器值
  count++;
}
void light()//流水灯
{
	uchar i=0;
	P1=_crol_(P1,1);//该函数对P1的值进行循环移位
}
void main()
{  
	P1=0xFE;
	TMOD=0x01;//定时器工作方式1
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;//初值50ms
	EA=1;//打开总中断
	ET0=1;//打开定时/计数器0中断
	TR0=1;//启动定时/计数器0
	while(1)
	{
		if(count==20)//计满1s
		{
			light();
			count=0;//移位流水灯并重置计数
		}
	}
}