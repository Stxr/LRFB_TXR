#include "tool.h"
u8 Check_pe2(void)
{
	u8 t=0;
	u8 tx=0;//记录松开的次数
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOE,2)!=0)//已经按下了
		{
			t++;
			tx=0;
		}
		else
		{
			tx++; //超过300ms内没有WKUP信号
			if(tx>3)
			{
				return 0;//错误的按键,按下次数不够
			}
		}
		delay_ms(1);
		if(t>=20)//按下超过3秒钟
		{
			return 1; //按下3s以上了
		}
	}
}
u8 Check_pe3(void)
{
	u8 t=0;
	u8 tx=0;//记录松开的次数
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOE,3)!=0)//已经按下了
		{
			t++;
			tx=0;
		}
		else
		{
			tx++; //超过300ms内没有WKUP信号
			if(tx>3)
			{
				return 0;//错误的按键,按下次数不够
			}
		}
		delay_ms(1);
		if(t>=20)//按下超过3秒钟
		{
			return 1; //按下3s以上了
		}
	}
}
