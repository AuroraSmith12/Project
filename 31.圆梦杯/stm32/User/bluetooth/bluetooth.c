#include "bluetooth.h"
#include "stm32f10x.h"

void bluetooth_init(void)
{
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO,  ENABLE);
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,  ENABLE);
	 RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2,  ENABLE);
	
	//PA2 -- TX
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode=GPIO_Mode_AF_PP;
	gpio_init.GPIO_Pin=GPIO_Pin_2;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&gpio_init);
	
	//PA3 -- RX
	gpio_init.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpio_init.GPIO_Pin=GPIO_Pin_3;
	
	GPIO_Init(GPIOA,&gpio_init);
	
	USART_InitTypeDef Usart_InitStructure;
    USART_StructInit( &Usart_InitStructure);

	Usart_InitStructure.USART_BaudRate=9600;
	Usart_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	Usart_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	Usart_InitStructure.USART_Parity=USART_Parity_No;
	Usart_InitStructure.USART_StopBits=USART_StopBits_1;
	Usart_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init( USART2,  &Usart_InitStructure);
	
	 USART_Cmd( USART2,  ENABLE);	
}
void UARTSendByte( USART_TypeDef* USARTx, uint16_t Data)//·¢ËÍ×Ö·û
{
	 USART_SendData( USARTx,  Data);

	while( USART_GetFlagStatus( USARTx,  USART_FLAG_TXE)==RESET);
	
}



void UARTSendString( USART_TypeDef* USARTx,  char * str1)//·¢ËÍ×Ö·û´®
{
	uint16_t i=0;
	
	do
	{
 UARTSendByte(  USARTx,  *(str1+i));//·¢ËÍ×Ö·û
		i++;
		
		
		
		
		
	}while(*(str1+i)!='\0');
	
	while( USART_GetFlagStatus( USARTx,  USART_FLAG_TC)==RESET);//TC¼ì²â×Ö·û´®·¢ËÍÍê³É
	
	
	
	
}

int fputc(int ch,FILE*f)//printf   putchar
{
		 USART_SendData( USART2,  (uint8_t)ch);
	while( USART_GetFlagStatus( USART2,  USART_FLAG_TXE)==RESET);

	return (ch);
}


int fgetc(FILE*f)//ÊäÈëscanf getchar
{
	
		while( USART_GetFlagStatus( USART2,  USART_FLAG_RXNE)==RESET);

	
	return (int) USART_ReceiveData( USART2);

	
}


