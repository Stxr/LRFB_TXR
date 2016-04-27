#ifndef __USART_H_
#define __USART_H_
#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#define LEN 20
u16 usart3_buffer[64],usart3_rx;//usart3_rx:计数状态
void USART_Config(void);
void TIM4_Set(u8 sta);
void TIM4_Init(u16 arr,u16 psc);
#endif
