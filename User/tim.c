#include "tim.h"
void TIM2_Init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    TIM_TimeBaseStructure.TIM_Period=2000-1; //计数到200停止
    TIM_TimeBaseStructure.TIM_Prescaler=36000-1;// 72MHz/3600=2KHz
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

    TIM2_Set(0);
//  	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM4中断,允许更新中断

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}
void TIM2_Set(u8 sta)
{
    if(sta)
        {
//            printf("tim2 on\n");
	          TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM4中断,允许更新中断
            TIM_SetCounter(TIM2,0);//计数器清空
            TIM_Cmd(TIM2, ENABLE); //使能TIMx
        }
    else
        {
//            printf("tim2 off\n");
            TIM_Cmd(TIM2, DISABLE);//关闭定时器2
        }

}
