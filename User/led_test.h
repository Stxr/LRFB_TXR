#include "stm32f10x.h"
void GPIO_LED_InitConfig(void);
#define LED5(a) if(a)\
GPIO_SetBits(GPIOE,GPIO_Pin_5);\
else GPIO_ResetBits(GPIOE,GPIO_Pin_5);//共阳接法
#define LED6(a) if(a)\
GPIO_SetBits(GPIOE,GPIO_Pin_6);\
else GPIO_ResetBits(GPIOE,GPIO_Pin_6);//共阳接法
