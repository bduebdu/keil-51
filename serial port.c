#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char
uchar code KEY_TABLE[]={0xee,0xde,0xbe,0x7e,0xed,0xdd,0xbd,0x7d,0xeb,0xdb,0xbb,0x7b,0xe7,0xd7,0xb7,0x77};//键盘编码
uchar code TABLE[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};//共阴数码管编码
uchar i,key,temp,num;//全局变量
void delay()//延时函数
{
	uint n =1000;
	while(n--);
}
void input()
{
		P2=0xf0;//读列值
		if(P2!=0xf0)//判断有无按键按下
	{
			delay();
		if(P2!=0xf0)//判断有无按键按下
		{
			temp=P2;
		  P2=0x0f;//读行值
		  key=temp|P2;//将行，列相加
		  for(i=0;i<16;i++)
		 {
			 if(key==KEY_TABLE[i])//查询键盘表
		  { 
				num=i;
		    break;
		  }
	   }
		 SBUF=TABLE[num];//接受并发送按键信息
  	}
   }
}
void serial(void) interrupt 4
{
	TI=0;//TI清零
	if(RI)
	{
		RI=0;
		P0=0xfe;
		P1=SBUF;//接受数据，点亮数码管，显示按键值
	}
}
void main()
{ 
	TMOD=0x20;//定时器1选择工作方式2
	TH1=0xfd;
	TL1=0xfd;//9600波特率
	SM0=0;//串口工作方式1
	SM1=1;
	REN=1;//允许接受数据
	EA=1;//打开总中断
	ES=1;//打开串口中断
	TR1=1;//开启定时/计数器1
	input();
}