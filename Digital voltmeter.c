#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar code wei[] ={0x04,0x02,0x01};        
uchar code duan[] ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};    //数码管段位选
uchar pos[3];
sbit START = P3 ^0;      
sbit OE =P3 ^1;        
sbit EOC = P3 ^2;     
sbit dot =P1 ^7;   //小数点控制位 
static char i =0;
uint temp,num;
void delay()
{
	uint n =1000;
	while(n--);
}
void display()           //数码管显示
{
	pos[0]= num /100;       //百位
	pos[1]= num /10%10;       //十位
	pos[2]= num %10;          //个位
	P2=wei[i];              
	P1=duan[pos[i]];           	
	if(i ==0)
	{
	  dot = 0;
	}         //共阳极为0时小数点亮
	i++;
	if(i ==3)
	{
	  i=0;
	}
}
void INT_0() interrupt 0
{
	OE=1;         //放开读数据
	temp=P0;     //读取数据
	num = temp *1.0/255 * 500;  //数值转换为模拟电压值
	OE=0;       //D0到D7呈高阻状态
	display();
	START=1;      //再次上升沿复位
	START=0;         //下降沿启动下一次转换
}
void main()
{
 	EX0=1;           //开外部中断0
	IT0=1;         //外部中断下降沿触发
	EA=1;              //开总中断
	display();
	delay();
	START =0;   
	OE=0;      
	START =1;      //启动下一次A/D转换
	START =0; 
	while(1);
}