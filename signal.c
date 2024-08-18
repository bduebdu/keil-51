#include<reg51.h>
#define uchar unsigned char
uchar t=0;
uchar code table[]=
{0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};//共阴数码管编码
void delay(uchar c)
{
	uchar a,b;
	for(;c>0;c--)
	for(b=142;b>0;b--)
	for(a=2;a>0;a--);     //延时函数
}
void main()
{
	uchar sw,gw;
	while(1)
		{
		sw=t/10;   //表示十位
		gw=t%10;  //表示个位
		P2=0xfe;     //p2选中对应的数码管
		P1=table[gw];  //p1输出个位
		delay(30);
		P2=0xfd;    
		P1=table[sw];     //p1输出十位
		delay(30);
		t++;       //自增需要的数，并在100前归0
		if(t==100)
			t=0;
	}
}