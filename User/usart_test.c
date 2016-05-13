//功能：主要是用来测试ADC转换后的数值
//IO:PA9 发送  PA10接收
#include "usart_test.h"
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	/* USART1 GPIO config */
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 9600;                  //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //传输数据位数
	USART_InitStructure.USART_StopBits = USART_StopBits_1;        //停止位1
	USART_InitStructure.USART_Parity = USART_Parity_No ;          //不用校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //不用流量控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  //使用接收和发送功能
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);     //串口1 接收中断 使能

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //设置中断配置为第2组，4位设置抢占优先级，4位设置响应优先级

	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;  //串口中断1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;  //最低优先级防止掉台
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
// void USART3_Config(void)
// {
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	USART_InitTypeDef USART_InitStructure;
// 	NVIC_InitTypeDef NVIC_InitStructure;
//
// 	/* config USART3 clock */
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO| RCC_APB2Periph_GPIOD, ENABLE);
// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
// 	GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);
//
// 	/* USART3 GPIO config */
// 	/* Configure USART3 Tx (PD.08) as alternate function push-pull */
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOD, &GPIO_InitStructure);
// 	/* Configure USART3 Rx (PD.9) as input floating */
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_Init(GPIOD, &GPIO_InitStructure);
//
// 	/* USART3 mode config */
// 	USART_InitStructure.USART_BaudRate = 9600;                  //波特率
// 	USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //传输数据位数
// 	USART_InitStructure.USART_StopBits = USART_StopBits_1;        //停止位1
// 	USART_InitStructure.USART_Parity = USART_Parity_No ;          //不用校验位
// 	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //不用流量控制
// 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  //使用接收和发送功能
// 	USART_Init(USART3, &USART_InitStructure);
// 	USART_Cmd(USART3, ENABLE);
// 	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);     //串口3 接收中断 使能
//
// 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //设置中断配置为第2组，4位设置抢占优先级，4位设置响应优先级
//
// 	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;  //串口中断3
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;  //最低优先级防止掉台
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
// 	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
// 	NVIC_Init(&NVIC_InitStructure);
// 	TIM4_Init(100-1,7200-1);		//10ms中断
// 	usart3_rx=0;		//清零
// 	TIM4_Set(0);			//关闭定时器4
// }
void USART_Config(void)
{
	USART1_Config();
//	USART3_Config();
}
//设置TIM4的开关
//sta:0，关闭;1,开启;
// void TIM4_Set(u8 sta)
// {
// 	if(sta)
// 		{
// 			TIM_SetCounter(TIM4,0);//计数器清空
// 			TIM_Cmd(TIM4, ENABLE);  //使能TIMx
// 		}
// 	else
// 		TIM_Cmd(TIM4, DISABLE);//关闭定时器4
// }
// void TIM4_Init(u16 arr,u16 psc)
// {
// 	NVIC_InitTypeDef NVIC_InitStructure;
// 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//
// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能//TIM4时钟使能
//
// 	//定时器TIM4初始化
// 	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
// 	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
// 	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
// 	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
// 	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
//
// 	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM4中断,允许更新中断
//
//
// 	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级1
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
// 	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
// }

///重定向c库函数printf到USART1
int fputc(int ch, FILE *f)
{
	/* 发送一个字节数据到USART1 */
	USART_SendData(USART1, (uint8_t) ch);

	/* 等待发送完毕 */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	return (ch);
}

///重定向c库函数scanf到USART1
int fgetc(FILE *f)
{
	/* 等待串口1输入数据 */
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

	return (int)USART_ReceiveData(USART1);
}
/*********************************************END OF FILE**********************/
