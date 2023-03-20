#include "stm32f10x.h"
#include "usart_esp8266.h"
uint16_t data_rx_usart3;
static uint16_t cnt=0;
void usart_esp8266_init(void)
{
     RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,  ENABLE);  
    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Mode=GPIO_Mode_IPD;
    gpio_init.GPIO_Pin=GPIO_Pin_11;
        
    GPIO_Init(GPIOB,&gpio_init);   
}
