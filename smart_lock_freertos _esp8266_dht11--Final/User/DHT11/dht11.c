#include "stm32f10x.h"
#include "dht11.h"
#include "delay.h"

//DATA--PA8


char arr[5];


void ms_delay(uint16_t time)
{
	uint16_t i=0;
	while(time--)
	{
		i=12000;
		while(i--);
	}
	
	
}
void us_delay(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=10;  //自己定义
      while(i--) ;    
   }
}
void SetOutput_Mode(void)
{
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,  ENABLE);
	
	GPIO_InitTypeDef DHT11_Init;
	DHT11_Init.GPIO_Mode=GPIO_Mode_Out_PP;
	DHT11_Init.GPIO_Pin=GPIO_Pin_10;
	DHT11_Init.GPIO_Speed=GPIO_Speed_50MHz;
	
	
	 GPIO_Init( GPIOB,  &DHT11_Init);

}

void SetInput_Mode(void)
{
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,  ENABLE);
	
	GPIO_InitTypeDef DHT11_init;
	DHT11_init.GPIO_Mode=GPIO_Mode_IPU;
	DHT11_init.GPIO_Pin=GPIO_Pin_10;
	DHT11_init.GPIO_Speed=GPIO_Speed_50MHz;
	
	
	 GPIO_Init( GPIOB,  &DHT11_init);

}

void DHT11_Start(void) //返回0表示通讯失败,返回1则表示通讯成功
{
	uint8_t flag;
	uint8_t tmp=0;
	int i;
	int j;
	SetOutput_Mode();
	 GPIO_ResetBits( GPIOB,  GPIO_Pin_10);
	ms_delay(20);
	 GPIO_SetBits( GPIOB,  GPIO_Pin_10);
	us_delay(30);
	SetInput_Mode();

	
	while( GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_10)==1);
                                                  
	while( GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_10)==0);
                                                  
	while( GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_10)==1);
	while( GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_10)==0);
	for(i=0;i<5;i++)
	{
		for(j=0;j<8;j++)
		{
	while( GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_10)==0);

	us_delay(35);
			
	if(	( GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_10)==SET))
	{
		flag=1;
		while(GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_10)==SET);
	}
	else
	{
		flag=0;
	}
	tmp=tmp<<1;
	tmp|=flag;
}
	arr[i]=tmp;	
}
}
void IWDG_Init(void)
{
	 IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable);
	 IWDG_SetPrescaler( IWDG_Prescaler_8);
	 IWDG_SetReload( 0xFFF);//定一个819.2 ms
	 IWDG_ReloadCounter();
	 IWDG_Enable();
}
