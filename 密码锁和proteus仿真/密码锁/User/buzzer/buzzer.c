#include "stm32f10x.h"
#include "buzzer.h"

void buzzer_init(void)//pb4£¬pb5
{
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,  ENABLE);
    
    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Mode=GPIO_Mode_Out_PP;
    gpio_init.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
    gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOB,&gpio_init);
    
    GPIO_SetBits(GPIOB,GPIO_Pin_4|GPIO_Pin_5);  
}

