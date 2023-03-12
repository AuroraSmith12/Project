#include "stm32f10x.h"
#include "lock.h"

void Lock_Init(void)
{
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,  ENABLE);
	GPIO_InitTypeDef lock_init;
	lock_init.GPIO_Mode=GPIO_Mode_Out_PP;
	lock_init.GPIO_Pin=GPIO_Pin_8;
	lock_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&lock_init);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);

}
void Lock_Open(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}
void Lock_Close(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
}

