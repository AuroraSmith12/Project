#include "stm32f10x.h"
#include "usart.h"

void usart_init(void)
{
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO,  ENABLE);
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,  ENABLE);
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1,  ENABLE);
	
	//PA9 -- TX
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode=GPIO_Mode_AF_PP;
	gpio_init.GPIO_Pin=GPIO_Pin_9;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&gpio_init);
	
	//PA10 -- RX
	gpio_init.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpio_init.GPIO_Pin=GPIO_Pin_10;
	
	GPIO_Init(GPIOA,&gpio_init);
	
	USART_InitTypeDef Usart_InitStructure;
    USART_StructInit( &Usart_InitStructure);

	Usart_InitStructure.USART_BaudRate=9600;
	Usart_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	Usart_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	Usart_InitStructure.USART_Parity=USART_Parity_No;
	Usart_InitStructure.USART_StopBits=USART_StopBits_1;
	Usart_InitStructure.USART_WordLength=USART_WordLength_8b;
 USART_Init( USART1,  &Usart_InitStructure);
	
	 USART_Cmd( USART1,  ENABLE);	
}
void send_data(USART_TypeDef* USARTx, uint16_t Data)
{
	 USART_SendData( USARTx,  Data);
	 while(USART_GetFlagStatus( USARTx,  USART_FLAG_TC)==RESET);

}
void SendString(USART_TypeDef*USARTx,unsigned  char*str,char num)
{
		uint16_t i=0;
	
	do
	{
		send_data(  USARTx,  *(str+i));//·¢ËÍ×Ö·û
		i++;
		
	}while(i!=num);
	
	while( USART_GetFlagStatus( USARTx,  USART_FLAG_TC)==RESET);//TC¼ì²â×Ö·û´®·¢ËÍÍê³É
}
uint16_t Receive_Byte(USART_TypeDef* USARTx)
{
	//while( USART_GetFlagStatus( USARTx,  USART_FLAG_RXNE)==RESET);
	return  USART_ReceiveData( USARTx);

}
