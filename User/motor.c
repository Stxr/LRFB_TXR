//驱动机器人电机
//IO:PA6 PA7  分别控制TIM3_CH1 TIM3_CH2
//   PE7 PE8 PE9 PE10 控制机器人电机正反转
#include "motor.h"
void Motor_InitConfig(void)
{

	//结构体定义
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruction;  //初始化TIM
	TIM_OCInitTypeDef TIM_OCInitTypeStruction;   //TIM输出模式配置
	//GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);  //开启GPIOA的时钟和管脚的复用功能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//开启TIM3的时钟
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;  //控制pwm波
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;                            //复用推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;//控制电机正反
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	//TIM3
	TIM_TimeBaseStruction.TIM_Period=900-1; //定时器从0计数到999，为一个定时周期
	TIM_TimeBaseStruction.TIM_Prescaler=0;   //设置预分频：不分频  72MHz
	TIM_TimeBaseStruction.TIM_ClockDivision=0;  //设置时钟分频：不分频
	TIM_TimeBaseStruction.TIM_CounterMode=TIM_CounterMode_Up;  //向上计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruction);  //配置TIM_CCR预装载使能
	//TIM3 CH1
	TIM_OCInitTypeStruction.TIM_OCMode=TIM_OCMode_PWM1;  //配置pwm的模式：模式1——当向前计数时为有效电平
	TIM_OCInitTypeStruction.TIM_OutputState=TIM_OutputState_Enable; //输出使能
	TIM_OCInitTypeStruction.TIM_OCPolarity=TIM_OCPolarity_High;  //有效为高电平
	TIM_OC1Init(TIM3,&TIM_OCInitTypeStruction);  //TIM3通道1初始化
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);  //配置TIM_CCR预装载使能
	//TIM3 CH2
	TIM_OCInitTypeStruction.TIM_OCMode=TIM_OCMode_PWM1;  //配置pwm的模式：模式1——当向前计数时为有效电平
	TIM_OCInitTypeStruction.TIM_OutputState=TIM_OutputState_Enable; //输出使能
	TIM_OCInitTypeStruction.TIM_OCPolarity=TIM_OCPolarity_High;  //有效为高电平
	TIM_OC2Init(TIM3,&TIM_OCInitTypeStruction);  //TIM3通道1初始化
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);  //配置TIM_CCR预装载使能

	TIM_Cmd(TIM3,ENABLE);  //使能定时器2
}
void move(int a,int b)  //控制电机
{
	if (a>=0&&b>=0) //电机正转
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_7);  //INT1 1
			GPIO_ResetBits(GPIOE,GPIO_Pin_8);//INT2 0
			GPIO_SetBits(GPIOE,GPIO_Pin_9);  //INT3 1
			GPIO_ResetBits(GPIOE,GPIO_Pin_10);//INT4 0
		}
	else if(a>=0&&b<0)//右边反转
		{
			b=-b;
			GPIO_ResetBits(GPIOE,GPIO_Pin_7);//INT1 0
			GPIO_SetBits(GPIOE,GPIO_Pin_8);//INT2 1
			GPIO_SetBits(GPIOE,GPIO_Pin_9);  //INT3 1
			GPIO_ResetBits(GPIOE,GPIO_Pin_10);//INT4 0
		}
	else if(a<0&&b>=0)//左边反转
		{
			a=-a;
			GPIO_SetBits(GPIOE,GPIO_Pin_7);//INT1 1
			GPIO_ResetBits(GPIOE,GPIO_Pin_8);//INT2 0
			GPIO_ResetBits(GPIOE,GPIO_Pin_9);//INT3 0
			GPIO_SetBits(GPIOE,GPIO_Pin_10);  //INT4 1
		}
	else if(a<0&&b<0)//后退
		{
			a=-a;
			b=-b;
			GPIO_ResetBits(GPIOE,GPIO_Pin_7);//INT1 0
			GPIO_SetBits(GPIOE,GPIO_Pin_8);//INT2 1
			GPIO_ResetBits(GPIOE,GPIO_Pin_9);//INT3 0
			GPIO_SetBits(GPIOE,GPIO_Pin_10);  //INT4 1
		}
	TIM_SetCompare1(TIM3,a);   //PA6
	TIM_SetCompare2(TIM3,b);   //PA7

}
