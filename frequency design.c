#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar code TDUAN[]={ 
0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46}; //数码管阴级编码
uchar code TWEI[]={0x80,0x40,0x20,0x10,0x08}; //位码
uchar pos[5]={16,16,16,16,16}; //开始1s不显示数码管
uchar i;
uint num;
bit flag_1s,flag_2ms;
void TimerInit(void) 
{
   TMOD= 0x25; //设置t0计数器为模式1，t1定时器为模式2
   TL1 = 256-200; 
   TH1 = 256-200; //设置定时初值和重载值
   TH0 = 0; //计数器初始化
   TL0 = 0;
   TF1 = 0; //清除TF1标志
   EA = 1; //打开总中断
   ET1 = 1; //打开定时器1中断
   TR1 = 1; //定时器1计时
   TR0 = 1;//开启计数器0
}
void NumSet()//段选从个位到万位
{
   pos[0]= num%10; 
   pos[1]= num/10%10; 
   pos[2]= num/100%10; 
   pos[3]= num/1000%10; 
   pos[4]= num/10000; 
}
void Display()
{
   P2=0x00; //消影
   P2=TWEI[i]; //位选段选
   P1=~TDUAN[pos[i]]; //~便于切换共阳共阴数码管
   if(++i>=5) 
		 i=0;
}
void Timer1() interrupt 3
{
   static uint count_1s,count_2ms;
   if(++count_1s>=5000)//每秒获取一次频率
	{ 
   count_1s=0;
   num=TH0<<8|TL0; 
   TH0=TL0=0;//重置
   flag_1s=1;
  }
   if(++count_2ms>=2)//动态显示
   { 
   count_2ms=0;
   flag_2ms=1;
   }
}
void main()
{
   TimerInit();
   while(1) 
	{
    if(flag_1s==1) 
    { 
			flag_1s=0; 
		  NumSet(); //设置每位数字
		}
    if(flag_2ms==1) 
     { 
			 flag_2ms=0; 
		   Display(); //数码管显示
		 }
  }
}