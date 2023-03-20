#include "stm32f10x.h"
#include "fingerprint.h"
volatile uint8_t   FPM10A_RECEICE_BUFFER[51];
void ms_delay(uint16_t time)
{
	uint16_t i=0;
	while(time--)
	{
		i=12000;
		while(i--);
	}
}
void FP_Init(void)
{
		GPIO_InitTypeDef gpio_init;
	USART_InitTypeDef usart_init;

	
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,  ENABLE);
    //RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,  ENABLE);

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO,  ENABLE);
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2,  ENABLE);

	//PA9--TX
	gpio_init.GPIO_Mode=GPIO_Mode_AF_PP;//引脚控制权给外设
	gpio_init.GPIO_Pin=GPIO_Pin_2;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_Init( GPIOA,  &gpio_init);
	
	//PA10--RX
	gpio_init.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpio_init.GPIO_Pin=GPIO_Pin_3;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init( GPIOA,  &gpio_init);
	//PA12
	gpio_init.GPIO_Pin=GPIO_Pin_12;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init( GPIOA,  &gpio_init);
	
	
	usart_init.USART_BaudRate=9600;
	usart_init.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	usart_init.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	usart_init.USART_Parity=USART_Parity_No;
	usart_init.USART_StopBits=USART_StopBits_1;
	usart_init.USART_WordLength=USART_WordLength_8b;
	
   USART_Init( USART2,  &usart_init);
    USART_Cmd( USART2,  ENABLE);
}
void SendByte(USART_TypeDef*USARTx,uint16_t Data)
{
	 USART_SendData(USARTx,  Data);
	while( USART_GetFlagStatus( USARTx,  USART_FLAG_TXE)==RESET);
}
void SendString(USART_TypeDef*USARTx,unsigned  char*str)
{
		uint16_t i=0;
	
	do
	{
 SendByte(  USARTx,  *(str+i));//发送字符
		i++;
		
	}while(i!=17);
	
	while( USART_GetFlagStatus( USARTx,  USART_FLAG_TC)==RESET);//TC检测字符串发送完成
}
uint16_t ReceiveByte(USART_TypeDef*USARTx)
{
	while( USART_GetFlagStatus( USARTx,  USART_FLAG_RXNE)==RESET);
	return USART_ReceiveData( USARTx);
}
void FPM10A_Receive_Data(uint16_t length)
{
	uint16_t i=0;
	for(i=0;i<length;i++)
	{
		FPM10A_RECEICE_BUFFER[i]=ReceiveByte(USART2);
	}
}
void iwdg_init(void)
{
	 //RCC_LSICmd( ENABLE);//不需要
	 IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable);
	 IWDG_SetPrescaler( IWDG_Prescaler_16);//定1638.4ms
	 IWDG_SetReload( 0xFFF);
	 IWDG_ReloadCounter();//喂狗
	 IWDG_Enable();
}
