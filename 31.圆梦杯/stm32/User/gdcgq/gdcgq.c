#include "gdcgq.h"
#include "stm32f10x.h"

void gd_init(void)
{
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,  ENABLE);
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC,  ENABLE);
	
	GPIO_InitTypeDef gdInit;
	GPIO_InitTypeDef ledInit;
	
	gdInit.GPIO_Mode=GPIO_Mode_IPU;
	gdInit.GPIO_Pin=GPIO_Pin_1;
	gdInit.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_Init(GPIOB,&gdInit);
	
	ledInit.GPIO_Mode=GPIO_Mode_Out_PP;
	ledInit.GPIO_Pin=GPIO_Pin_13;
	ledInit.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&ledInit);
	 GPIO_SetBits(GPIOC,  GPIO_Pin_13);
	 GPIO_SetBits(GPIOB,  GPIO_Pin_9);

	
	
}	
