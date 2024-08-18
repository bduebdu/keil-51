#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]=" HELLO WORLD! ";
uchar code table1[]="YS          2023";//显示的字符
sbit lcden=P3^4;
sbit lcdrs=P3^5;
uchar num;
void delay(uint z)//延时用
{
	uint x,y;
	for(x=z;x>0;x--)
	for(y=110;y>0;y--);
}
void write_com(uchar com)
{
	lcdrs=0;//写命令
	P0=com;//com命令码送给P0
	delay(5);
	lcden=1;//使能端置高电平
	delay(5);
	lcden=0;
}
void write_data(uchar date)
{
	lcdrs=1;//写数据
	P0=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void init()//初始化
{
	lcden=0;
	write_com(0x38);//显示模式设置
	write_com(0x0e);//打开光标
	write_com(0x06);//写入字符后指针地址加1
	write_com(0x01);//清屏
	write_com(0x80+0x1);//设置字符显示的首地址
}
//通过单总线向DS18B20写一个字节
void Write_DS18B20(unsigned char dat)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        DQ = 0;
        DQ = dat & 0x01;
        Delay_OneWire(5);
        DQ = 1;
        dat >>= 1;
    }
    Delay_OneWire(5);
}
//从DS18B20读取一个字节
unsigned char Read_DS18B20(void)
{
    unsigned char i;
    unsigned char dat;
    for (i = 0; i < 8; i++)
    {
        DQ = 0;
        dat >>= 1;
        DQ = 1;
        if (DQ)
        {
            dat |= 0x80;
        }
        Delay_OneWire(5);
    }
    return dat;
}

//DS18B20设备初始化
bit init_DS18B20(void)
{
    bit initflag = 0;
    DQ = 1;
    Delay_OneWire(12);
    DQ = 0;
    Delay_OneWire(80);
    DQ = 1;
    Delay_OneWire(10);
    initflag = DQ;
    Delay_OneWire(5);
    return initflag;
}
void DS18B20_Start(void) //启动温度转换
{
    init_DS18B20();
    Write_DS18B20(OW_SKIP_ROM);
    Write_DS18B20(DS18B20_CONVERT);
}
int DS18B20_Get(void) //读取数据(返回16位带符号整数)
{
    unsigned int low = 0, high = 0;
    int temp;
    init_DS18B20();
    Write_DS18B20(OW_SKIP_ROM);
    Write_DS18B20(DS18B20_READ);
    low = Read_DS18B20();
    high = Read_DS18B20();
    temp = (high << 8) | low;
    return temp;
}
void int0() interrupt 0
{
for(num=0;num<14;num++)//显示第一行
	{
		write_data(table[num]);
		delay(20);
	}
	write_com(2);//回车换行
	write_com(0x80+0x40);
	for(num=0;num<16;num++)//显示第二行
	{
		write_data(table1[num]);
		delay(20);
	}
}
void int1() interrupt 2//清屏用
{
	write_com(1);
}
void main()
{
	init();
  delay(100);
  EA=1;//打开总中断，外部中断0和1
	EX0=1;
	EX1=1;
	while(1);//等待中断发生
}