//功能：设置ADC，并用DMA的方式将adc的值传出来
// IO:PC0 ,PC1, PC2, PC3分别对应ADC1_IN10 ADC1_IN11 ADC1_IN12 ADC1_IN13
#include "adc.h"
#include "delay.h"
// #define ADC1_DR_Address    ((u32)0x40012400+0x4c)  不用dma应该可以去掉
void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1,ENABLE);  //开启GPIOC和ADC1时钟

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;  //作为adc输入的时候，必须用模拟输入
	GPIO_Init(GPIOC,&GPIO_InitStructure);      //作为输入的时候不用设置速率
}
void ADC_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;  //独立adc模式
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;  //扫描模式用单通道采集
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None; //转换使用软件转换而不是外部出发转换
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;  //右对齐
	ADC_InitStructure.ADC_NbrOfChannel=4;  //要转换的通道数目：4
	ADC_Init(ADC1,&ADC_InitStructure);

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //PCLK的6分频，12Hz 最大为14Hz

	ADC_Cmd(ADC1,ENABLE);  //使能ADC1
	ADC_ResetCalibration(ADC1);//复位校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));//等待复位完成

	ADC_StartCalibration(ADC1);//ADC校准
	while(ADC_GetCalibrationStatus(ADC1)); //等待校准完成

	//ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //软件触发使能
}
void ADC_InitConfig(void)
{
	ADC_GPIO_Config();
	ADC_Mode_Config();
}
u16 Get_ADC(u8 ch)
{
	ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_239Cycles5); //	ADC1 ch通道 采样周期为55.5
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //软件触发使能

	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
u16 Get_Adc_Average(u8 ch,u32 times)
{
	u32 temp_val[5]={0};
	u32 temp=0;
	u8 t,i,j;
	for(t=0;t<5;t++)
	{
		temp_val[t]=Get_ADC(ch);
		delay_ms(5);
	}
	for(j=0;j<4;j++)
        for(i=0;i<4-j;i++)
        {
            if(temp_val[i]>temp_val[i+1])
            {
                temp=temp_val[i];
                temp_val[i]=temp_val[i+1];
                temp_val[i+1]=temp;
            }
        }
	return temp_val[2]/100;
}
