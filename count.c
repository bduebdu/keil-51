#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char
uchar code TABLE[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};//共阴数码管编码
uchar code wei[]={0xfd,0xfe};
uchar temp[]={0,0};
uchar i;
uchar count=0;
void init()//初始化定时器
{
	TMOD=0x15;//设置定时器0工作方式为方式1，定时器1工作方式为方式1
	TH0=(65536-1)/256;
	TL0=(65536-1)%256;//计数器0每来一次脉冲中断一次
  TH1=(65536-1000)/256;//定时器1每1ms中断一次
	TL1=(65536-1000)%256;
	EA=1;//开启总中断
	ET0=1;//开启计数器0中断
	ET1=1;//开启定时器1中断
	TR0=1;//启动计数器0
	TR1=1;//启动定时器1
}
void count0()interrupt 1
{
	TH0=(65536-1)/256;
	TL0=(65536-1)%256;//计数器0每来一次脉冲中断一次
	count++;
	if(count==100)//计数满100归0
		count=0;
}
void time1() interrupt 3
{
	static int timecount=0,weicount=0;//设置静态变量
	TH1=(65536-1000)/256;//定时器1每1ms中断一次
	TL1=(65536-1000)%256;//每2ms刷新数码管
	if(++timecount>=2)
	{
		P2=wei[weicount];
		P1=TABLE[temp[weicount]];//数码管位选和段选
		weicount++;
		timecount=0;//清零2ms计时
		if(weicount==2)
			weicount=0;//清零位选和段选标志位
	}
}
void display()//计数结果存入数组
{
  temp[0]=count/10;
	temp[1]=count%10;
}
void main()
{
	init();
	while(1)
	{
	display();
	}
}
