#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char//声明头文件
void delay(uchar c)
{
	uchar a,b;
	for(;c>0;c--)
	for(b=142;b>0;b--)
	for(a=2;a>0;a--);     //延时函数
}
void INT_0() interrupt 0//外部中断子程序(流水灯)
{
	uchar i,temp;//设置中间值temp以防止流水进度被重置
P1=0xfe;
		  temp=P1;
		for(i=0;i<8;i++)
		{		
			delay(1000);	
			temp=_crol_(temp,1);//进行循环移位
			P1=temp;
		}
		P1=0xff;//熄灭所有灯
}
void INT_1() interrupt 2//外部中断子程序(闪烁3次）
{
	uchar a;
	for(a=3;a>0;a--)
	{
		P1=0x00;
		delay(1000);
		P1=0xff;
		delay(1000);
	}	
}
void main()
{
	EX0=1;//打开外部中断0
	IP=0x04;//设置外部中断1为高优先级
	IT0=0;//设置中断触发方式为低电平触发方式
	EX1=1;
	IT1=0;
	EA=1;//打开总中断
  while(1);//等待中断发生
}