#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char
sbit cs=P3^7;//片选控制端
sbit wr=P3^6;//输入寄存器写选通信号
sbit s1=P1^0;
sbit s2=P1^1;
sbit s3=P1^2;
uchar k=0;//全局变量
void delay(uint m)//延时函数
{  
  while(m--);
}
void tri_waves()//三角波代码
{
	while(1)//主循环
  {
		P0=k++;//将k值从0到255通过P0口输入到DAC0832
	  delay(100);
	  if(k==0xff)
	  break;
	}	
	while(1)
	{
		P0=k--;//将k值从255到0通过P0口输入到DAC0832
	  delay(100);
	  if(k==0) 
	  break;
  }
}
void square_wave()//方波代码
{ 
	P0=0;
	delay(100000);
	P0=0xff;
	delay(100000);//k值在0和255之间变换
}
void serrated_waves()//三角形波代码
{
		P0=k++;
	  delay(100);
	  P0=0;//k值自增一段时间后归零
}
void INT_0() interrupt 0//进入中断后根据所选择的P1口给出相应的波形
{
		if(s1==0)
	  {
		tri_waves();
	  }
	if(s2==0)
	{
			square_wave();
	}
	if(s3==0)
	{
		serrated_waves();
	}
}
void main()
{
	EX0=1;
	IT0=0;
	EA=1;//打开外部中断和总中断
	cs=0;
	wr=0;
	while(1);//等待中断发生
}