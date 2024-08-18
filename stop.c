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
void INT_0() interrupt 0//外部中断子程序
{
	uchar i;
		P0=0xfe;//点亮p0.0的灯
		for(i=0;i<8;i++)
		{
			delay(1000);	
			P0=_crol_(P0,1);//进行循环移位
		}
		P0=0xff;//熄灭所有灯
}
void main()
{
	EA=1;//将EA和EX0置高电平（打开总中断和外部中断0）
	EX0=1;
	IT0=0;//中断触发方式为低电平触发
  while(1);
}