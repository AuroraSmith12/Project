#include "stm32f10x.h"
#include "usart_face.h"

void Usart_Init(void)
{
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO,  ENABLE);
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,  ENABLE);
	 RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART3,  ENABLE);

	 //GPIO_PinRemapConfig( GPIO_Remap_USART1,  ENABLE);

	GPIO_InitTypeDef gpio_init;
//	//PB6--TX
//	gpio_init.GPIO_Mode=GPIO_Mode_AF_PP;
//	gpio_init.GPIO_Pin=GPIO_Pin_6;
//	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&gpio_init);

	//PB11--RX
	gpio_init.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpio_init.GPIO_Pin=GPIO_Pin_11;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpio_init);

	USART_InitTypeDef usart_init;
	usart_init.USART_BaudRate=115200;
	usart_init.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	usart_init.USART_Mode=USART_Mode_Rx;
	usart_init.USART_Parity=USART_Parity_No;
	usart_init.USART_StopBits=USART_StopBits_1;
	usart_init.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART3,&usart_init);
	 USART_Cmd( USART3,  ENABLE);	
}

uint16_t Receive_Byte(USART_TypeDef*USARTx)
{
	uint16_t data=0;
	if( USART_GetFlagStatus( USARTx,  USART_FLAG_RXNE)==SET)
	data=USART_ReceiveData( USARTx);

	return  data;
	
}
