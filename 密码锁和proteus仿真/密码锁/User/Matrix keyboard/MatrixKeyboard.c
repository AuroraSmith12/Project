#include "stm32f10x.h"
#include "MatrixKeyboard.h"
/*
@brief 矩阵键盘
@retval keynum
*/
//PA0--C4
//PA1--C3
//PA2--C2
//PA3--C1
//PA4--R1
//PA5--R2
//PA6--R3
//PA7--R4

void delay_ms(uint16_t time)
{
	uint16_t i=0;
	while(time--)
	{
		i=12000;
		while(i--);
	}
}
uint8_t MatrixKeyboard_Init(void)
{
	uint8_t KeyNumber=0;
	//使用行扫描，行给赋值，读取列的电平
	//行用输出模式，列用输入模式
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,  ENABLE);
	
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio_init.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;

	 GPIO_Init( GPIOA,  &gpio_init);
	
	GPIO_InitTypeDef Gpio_Init;
	 GPIO_StructInit( &Gpio_Init);

	Gpio_Init.GPIO_Mode=GPIO_Mode_IPU;
	Gpio_Init.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	
	GPIO_Init(GPIOA,&Gpio_Init);
	
	//第一行赋值
	 GPIO_ResetBits( GPIOA,  GPIO_Pin_7);
	 GPIO_SetBits( GPIOA,  GPIO_Pin_4);
	 GPIO_SetBits( GPIOA,  GPIO_Pin_5);
	 GPIO_SetBits( GPIOA,  GPIO_Pin_6);

	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_0)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_0)==RESET);delay_ms(20);KeyNumber=1;}
	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_1)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_1)==RESET);delay_ms(20);KeyNumber=2;}
	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_2)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_2)==RESET);delay_ms(20);KeyNumber=3;}
	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_3)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_3)==RESET);delay_ms(20);KeyNumber=4;}

	//第二行赋值
	 GPIO_ResetBits( GPIOA,  GPIO_Pin_6);
	 GPIO_SetBits( GPIOA,  GPIO_Pin_4);
	 GPIO_SetBits( GPIOA,  GPIO_Pin_5);
	 GPIO_SetBits( GPIOA,  GPIO_Pin_7);

	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_0)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_0)==RESET);delay_ms(20);KeyNumber=5;}
	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_1)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_1)==RESET);delay_ms(20);KeyNumber=6;}
	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_2)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_2)==RESET);delay_ms(20);KeyNumber=7;}
	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_3)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_3)==RESET);delay_ms(20);KeyNumber=8;}

	//第三行赋值
	 GPIO_ResetBits( GPIOA,  GPIO_Pin_5);
	 GPIO_SetBits( GPIOA,  GPIO_Pin_4);
	 GPIO_SetBits( GPIOA,  GPIO_Pin_7);
	 GPIO_SetBits( GPIOA,  GPIO_Pin_6);

	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_0)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_0)==RESET);delay_ms(20);KeyNumber=9;}
	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_1)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_1)==RESET);delay_ms(20);KeyNumber=10;}
	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_2)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_2)==RESET);delay_ms(20);KeyNumber=11;}
	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_3)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_3)==RESET);delay_ms(20);KeyNumber=12;}

	//第四行赋值
	 GPIO_ResetBits( GPIOA,  GPIO_Pin_4);
	 GPIO_SetBits( GPIOA,  GPIO_Pin_7);
	 GPIO_SetBits( GPIOA,  GPIO_Pin_5);
	 GPIO_SetBits( GPIOA,  GPIO_Pin_6);

	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_0)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_0)==RESET);delay_ms(20);KeyNumber=13;}
	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_1)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_1)==RESET);delay_ms(20);KeyNumber=14;}
	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_2)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_2)==RESET);delay_ms(20);KeyNumber=15;}
	if( GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_3)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_3)==RESET);delay_ms(20);KeyNumber=16;}

	return KeyNumber;
}
