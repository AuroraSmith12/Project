#include "stm32f10x.h"
#include "usart_esp8266.h"
uint16_t data_rx_usart3;
static uint16_t cnt=0;
void usart_esp8266_init(void)
{
     RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,  ENABLE);
     RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART3,  ENABLE);
    
    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    gpio_init.GPIO_Pin=GPIO_Pin_11;
        
    GPIO_Init(GPIOB,&gpio_init);
    
    USART_InitTypeDef usart_init;
    
    usart_init.USART_BaudRate=9600;
    usart_init.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    usart_init.USART_Mode=USART_Mode_Rx;
    usart_init.USART_Parity=USART_Parity_No;
    usart_init.USART_StopBits=USART_StopBits_1;
    usart_init.USART_WordLength=USART_WordLength_8b;

    
     USART_Init( USART3,  &usart_init);
    
     
      USART_ITConfig(USART3,  USART_IT_RXNE,  ENABLE);
      
      NVIC_InitTypeDef nvic_init;
      nvic_init.NVIC_IRQChannel=USART3_IRQn;
      nvic_init.NVIC_IRQChannelCmd=ENABLE;
      nvic_init.NVIC_IRQChannelPreemptionPriority=1;
      NVIC_Init(&nvic_init);



     USART_Cmd( USART3,  ENABLE);
    
}

void USART3_IRQHandler(void)
{
    if( USART_GetITStatus( USART3,  USART_IT_RXNE))
    {
        data_rx_usart3=USART_ReceiveData(USART3);
    }
     USART_ClearITPendingBit(USART3,  USART_IT_RXNE);


}
