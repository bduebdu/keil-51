#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char   //声明头文件
void delay()
{
  uchar i,j;
	for(i=200;i>0;i--)
	for(j=150;j>0;j--);
}
void main()
{
	uchar i;
	uchar temp=0xFF;
	P1=temp;
	while(1)
	{
		P1=0xFE;//点亮与P1连接的灯
		for(i=0;i<8;i++)
		{
			P1=_crol_(P1,1);//该函数对P1的值进行循环移位
			delay();//延时一段时间
		}
	}
}