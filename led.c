/******�������****************/
#include<reg51.h>
#define  uint unsigned int

/***********������ʱ����*****************/
void delay()
{
	uint i,j;
	for(i= 10;i> 0;i--)
	for(j= 1000;j> 0;j--);
}

/************����������**************/
void main()
{
	while(1)                //����whileѭ��
	{
		P1= 0xff;             //��ȫ��P2�ڶ����ֵ������ߵ�ƽ����ֹ���������
	if(P1!= 0xff)           //һ�ֲ�ѯ��ʽ�������ر�����ʱ�ı仯��
	{
		P1= P1 << 2;          //��λ���㣬�����ƶ�4λ���������4������״̬�͸�LED�ơ�
		delay();              //��ʱ
	}
}
	}