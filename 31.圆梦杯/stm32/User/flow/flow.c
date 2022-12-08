#include "flow.h"
#include "stm32f10x.h"

void flow_init(void)
{
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,  ENABLE);
	GPIO_InitTypeDef flowInit;

	
	flowInit.GPIO_Mode=GPIO_Mode_IPU;
	flowInit.GPIO_Pin=GPIO_Pin_6;
	flowInit.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_Init(GPIOA,&flowInit);	
	
	

	
	EXTI_InitTypeDef extiInit;
	extiInit.EXTI_Line=EXTI_Line6;
	extiInit.EXTI_LineCmd=ENABLE;
	extiInit.EXTI_Mode=EXTI_Mode_Interrupt;
	extiInit.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&extiInit);
	
	 NVIC_PriorityGroupConfig( NVIC_PriorityGroup_1);
	NVIC_InitTypeDef nvicInit;
	nvicInit.NVIC_IRQChannel=EXTI9_5_IRQn;
	nvicInit.NVIC_IRQChannelCmd=ENABLE;
	nvicInit.NVIC_IRQChannelPreemptionPriority=0;
	nvicInit.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&nvicInit);
	
	 GPIO_EXTILineConfig( GPIO_PortSourceGPIOA,  GPIO_PinSource6);
}
