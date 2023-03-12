#include "stm32f10x.h"
#include "beep.h"

void Beep_Init(void)
{
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC,  ENABLE);
	GPIO_InitTypeDef beep_init;
	beep_init.GPIO_Mode=GPIO_Mode_Out_PP;
	beep_init.GPIO_Pin=GPIO_Pin_0;
	beep_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&beep_init);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);

	
}
