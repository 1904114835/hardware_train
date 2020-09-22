#include <stm32f10x.h>
#include <string.h>
#include "time.h"



void delay_ms1(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  
      while(i--) ;    
   }
}

void TIM_int_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_OCInitTypeDef TIM_OcStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 1;
	TIM_TimeBaseStructure.TIM_Prescaler= 35999;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	
	TIM_Cmd(TIM2,ENABLE);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //TIM3 �ж�   ***************************************����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //�����ȼ� 0 ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ ͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure); //��ʼ�� NVIC
	
	TIM_OcStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OcStructure.TIM_Pulse = 1350;
	TIM_OcStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OcStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC2Init(TIM2,&TIM_OcStructure);
	TIM_Cmd(TIM2,ENABLE);

}


void GPIO_int_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); 
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
}

void TIM2_IRQHandler(void)   //TIM2�ж�
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
				GPIOA->ODR ^= (1<<0);
				GPIOA->ODR ^= (1<<1);
				GPIOA->ODR ^= (1<<2);
				GPIOA->ODR ^= (1<<3);

    }
}
