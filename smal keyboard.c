#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char
uchar code KEY_TABLE[]={0xee,0xde,0xbe,0x7e,0xed,0xdd,0xbd,0x7d,0xeb,0xdb,0xbb,0x7b,0xe7,0xd7,0xb7,0x77};//键盘编码
uchar code TABLE[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};//共阴数码管编码
uchar i;//全局变量
void output();
void delays()//延时消除按键抖动
{
	uint n =1000;
	while(n--);
}
void delayl()
{
	uint n =5000;
	while(n--);
}
void input()
{
    uchar key,temp;
		P3=0xf0;//读列值
		if(P3!=0xf0)//判断有无按键按下
	{
			delays();
		if(P3!=0xf0)//判断有无按键按下
		{
			temp=P3;
		  P3=0x0f;//读行值
		  key=temp|P3;//将行，列相加
		  for(i=0;i<16;i++)
		 {
			 if(key==KEY_TABLE[i])//查询键盘表
		  { 
		    break;
		  }
	   }
  	}
   }
}
void output()//键盘得出的值由此显示
{
	uchar sw,gw;
		sw=i/10;   
		gw=i%10; 
		P2=0xfe;    
		P1=TABLE[gw];	
	  delays();	
		P2=0xfd;    
		P1=TABLE[sw];	   		
}
void main()//主函数将上述子函数进行循环
{ 
	while (1)
	{
	input();
  output();
  delayl();
	}
}