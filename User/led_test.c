//好久没弄32了，点亮一盏灯练练手。
//LED:PE5，共阳接法
#include "led_test.h"
void GPIO_LED_InitConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);  //开启GPIOE的时钟
	GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStruction.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6;   //PE5,PE6
	GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;  // 速率50MHZ
	GPIO_Init(GPIOE,&GPIO_InitStruction);     //将设置的值装入寄存器中
}
