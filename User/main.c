//类人非标程序2016
/*
  引脚说明：
          光电中断：PE2，PE3，PE4，PE5 (PE2:左前 PE3：右前)
          红外测距：PC0 PC1 PC2 PC3 分别对应ADC1_IN10 ADC1_IN11 ADC1_IN12 ADC1_IN13 (PC2：右 PC3：左)
          电机：PA6 PA7  分别控制TIM3_CH1 TIM3_CH2(PA6：左 PA7：右)
               PE7 PE8 PE9 PE10 控制机器人电机正反转(接线：PE7：A1 PE8：A2 PE9：B1 PE10：B2)
               PWM：TIM3
  主要函数说明：
          move(int a,int b); 控制电机 左:a 右:b 速度为（-900——900）
          chess(void); 推棋子程序
          Get_Adc_Average(u8 ch,u32 times); 红外检测程序 ch：通道 times：采样次数
					printf();向USART1输出测试值，向外接一个无线蓝牙模块，就可以实时检测到机器的运行状态
	中断优先级说明：
					中断		抢断优先级    子优先级
					PE2：			2 						0
					PE3：			2							0
					PE4：			2							0
					PE5：			2							0
					TIM2：		1							2

*/
#include "stm32f10x.h" //stm32官方头文件
#include "delay.h"  //延时函数
#include "motor.h"  //电机
#include "adc.h"   //AD
#include "exti.h" //中断
#include "tool.h" //一些工具
#include "uart5.h"
#include "usart_test.h"//USART1测试程序
#include "tim.h"  //TIM2配置
void walk(void);
void hand(void);
int flag_pe4=-1;//flag_pe4=1 可以进入上升沿中断标志位 flag_pe4=0 进入下降沿标志位
int flag_fuc=-1;//flag_fuc=1 推棋子 flag_fuc=0 对抗
/**************************************主函数****************************************/
int main(void)
{
	flag_fuc=0;//0:对抗 1:推棋子
	delay_init();  //延时函数初始化
	Motor_InitConfig();  //电机初始化
	ADC_InitConfig(); //ADC初始化
	uart5_init(1000000);				//与舵机通信
	TIM2_Init();
	USART_Config();
	//软启动
	move(0,0);
	printf("ready\n");
	while(Get_Adc_Average(13,1)<30);

	// 上台程序
	move(500,500);
	delay_ms(1000);
	move(300,600);
	delay_ms(500);

	EXTI_InitConfig();//中断初始化(开中断)

	while(1)
	{
		walk();//推棋子程序
	//	hand();
//		printf("%d\n",Get_Adc_Average(10,1));
	}
	return 0;
}

/***************************************中断*******************************************/
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(Check_pe2()) //这个很重要
	{
		printf("exti2 in\n");
		if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
		{
			unsigned int con=0,value;
			if(flag_fuc)//0:对抗 1:推棋子
			{
					//棋子对齐程序
					while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)    //pe3 右前
					{
						move(20,300);
						con++;
						if (con>300000)
						{
							con=0;
							break;
						}
					}
					for(int i=0; i<10; i++)
					{
						value-=60;
						delay_ms(10);
						move(value,value);
					}
			}
			move(-400,-400);
			for (int i=0; i<40; i++)
				delay_ms(10);
			move(-300,400);
			delay_ms(300);
			delay_ms(350);
			EXTI_ClearITPendingBit(EXTI_Line3|EXTI_Line2);
		}
	}
	printf("exti2 out\n");
}
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(Check_pe3())//这个很重要
	{
		printf("exti3 in\n");
		if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
		{
			unsigned int con=0;
			if(flag_fuc)//0:对抗 1:推棋子
			{
					//棋子对齐程序
					while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0)    //pe2 左前
					{
						move(400,20);
						con++;
						if (con>300000)
						{
							con=0;
							break;
						}
					}
			}
			move(-400,-400);
			for (int i=0; i<40; i++)
				delay_ms(10);
			move(400,-300);
			delay_ms(300);
			delay_ms(350);
			EXTI_ClearITPendingBit(EXTI_Line3|EXTI_Line2);
		}
	}
	printf("exti3 out\n");
}
void EXTI4_IRQHandler(void) //中间中断
{
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
	{
		printf("exti4 in\n");
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==RESET)
		{
			TIM2_Set(1);
			flag_pe4=0;
			printf("pe4=0\n");
		}
		else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)!=RESET && flag_pe4==1)
		{
			TIM2_Set(0);
			move(-400,-400);
			for (int i=0; i<40; i++)
				delay_ms(10);
			move(0,0);
			delay_ms(300);
			delay_ms(350);
			printf("flag_pe4\n");
		}
		else if (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)!=RESET)
		{
			TIM_SetCounter(TIM2,0);
			TIM2_Set(0);
			printf("tim2=0\n");
			flag_pe4=0;
		}
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
	printf("exti4 out\n");
}

//测速中断
void EXTI9_5_IRQHandler(void)
{

}
//定时器4中断服务程序
void TIM4_IRQHandler(void)
{

}
//定时器3中断服务程序
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)//是更新中断
	{
		printf("tim2 in\n");
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		TIM2_Set(0);
		flag_pe4=1;
	}
		printf("tim2 out\n");
}
void USART1_IRQHandler(void)
{
}

void USART3_IRQHandler(void)
{

}
/***********************************推棋子*************************************/
void walk()
{
	long int s=0;
	if((Get_Adc_Average(10,3)>25))			//前 测距
	{
		move(600,600);
	}
	if(Get_Adc_Average(12,3)>20)				//右
	{
		move(-200,400);//
		delay_ms(700);
		s=0;
		do
		{
			s++;
		}
		while(((Get_Adc_Average(10,3)>1600)&&(Get_Adc_Average(11,3)>1900))&&(s<=100000));
	}
	else if(Get_Adc_Average(13,3)>20)	//左
	{
		move(400,-200);
		delay_ms(700);
		s=0;
		do
		{
			s++;
		}
		while(((Get_Adc_Average(10,3)>1600)&&(Get_Adc_Average(11,3)>1900))&&(s<=100000));
	}
// 	else if(Get_Adc_Average(4,3)>26)//后
// 	{
// 		move(-400,400);//
// 		delay_ms(700);
// 		s=0;
// 		do
// 		{
// 			s++;
// 		}
// 		while(((Get_Adc_Average(10,3)>1600)&&(Get_Adc_Average(11,3)>1900))&&(s<=100000));
// 	}
	else  move(400,400); 					//寻敌
	printf("walk\n");
}
/************************************手臂***********************************/
void hand(void)
{
	SetServoPosition(2,600,200);
	delay_ms(500);
	SetServoPosition(1,761,200);
	delay_ms(1000);
	SetServoPosition(1,761,200);
	SetServoPosition(2,355,200);
	SetServoPosition(3,622,200);
	delay_ms(1000);
	SetServoPosition(1,761,200);
	SetServoPosition(2,628,200);
	SetServoPosition(3,424,200);
	delay_ms(1000);
	SetServoPosition(1,761,200);
	SetServoPosition(2,355,200);
	SetServoPosition(3,622,200);
	delay_ms(1000);
	SetServoPosition(1,761,200);
	SetServoPosition(2,628,200);
	SetServoPosition(3,424,200);
	delay_ms(1000);
	SetServoPosition(1,512,200);
	delay_ms(500);
}

/**************************END OF FILE*************************/
