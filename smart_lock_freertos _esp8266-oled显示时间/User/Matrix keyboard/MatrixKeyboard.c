#include "stm32f10x.h"
#include "MatrixKeyboard.h"
/*
@brief 矩阵键盘
@retval keynum
*/
//Pb12--C4
//Pb13--C3
//Pb14--C2
//Pb15--C1
//Pb3--R1
//Pb4--R2
//Pb5--R3
//Pb6--R4

//void delay_ms(uint16_t time)
//{
//	uint16_t i=0;
//	while(time--)
//	{
//		i=12000;
//		while(i--);
//	}
//}
uint8_t MatrixKeyboard_Init(void)
{
	uint8_t KeyNumber=0;
	//使用行扫描，行给赋值，读取列的电平
	//行用输出模式，列用输入模式
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,  ENABLE);
	 //RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,  ENABLE);
	
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio_init.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;

	 GPIO_Init( GPIOB,  &gpio_init);
	
	GPIO_InitTypeDef Gpio_Init;
	 GPIO_StructInit( &Gpio_Init);

	Gpio_Init.GPIO_Mode=GPIO_Mode_IPU;
	Gpio_Init.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	
	GPIO_Init(GPIOB,&Gpio_Init);
	
//	GPIO_InitTypeDef GPio_init;
//	GPio_init.GPIO_Mode=GPIO_Mode_IPU;
//	GPio_init.GPIO_Pin=GPIO_Pin_8;
//	GPIO_Init(GPIOA,&GPio_init);
	
	//第一行赋值
	 GPIO_ResetBits( GPIOB,  GPIO_Pin_6);
	 GPIO_SetBits( GPIOB,  GPIO_Pin_4);
	 GPIO_SetBits( GPIOB,  GPIO_Pin_5);
	 GPIO_SetBits( GPIOB,  GPIO_Pin_3);

	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_12)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_12)==RESET);delay_ms(20);KeyNumber=1;}
	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_13)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_13)==RESET);delay_ms(20);KeyNumber=2;}
	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_14)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_14)==RESET);delay_ms(20);KeyNumber=3;}
	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_15)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_15)==RESET);delay_ms(20);KeyNumber=4;}

	//第二行赋值
	 GPIO_ResetBits( GPIOB,  GPIO_Pin_5);
	 GPIO_SetBits( GPIOB,  GPIO_Pin_4);
	 GPIO_SetBits( GPIOB,  GPIO_Pin_6);
	 GPIO_SetBits( GPIOB,  GPIO_Pin_3);

	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_12)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_12)==RESET);delay_ms(20);KeyNumber=5;}
	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_13)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_13)==RESET);delay_ms(20);KeyNumber=6;}
	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_14)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_14)==RESET);delay_ms(20);KeyNumber=7;}
	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_15)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_15)==RESET);delay_ms(20);KeyNumber=8;}

	//第三行赋值
	 GPIO_ResetBits( GPIOB,  GPIO_Pin_4);
	 GPIO_SetBits( GPIOB,  GPIO_Pin_3);
	 GPIO_SetBits( GPIOB,  GPIO_Pin_5);
	 GPIO_SetBits( GPIOB,  GPIO_Pin_6);

	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_12)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_12)==RESET);delay_ms(20);KeyNumber=9;}
	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_13)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_13)==RESET);delay_ms(20);KeyNumber=10;}
	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_14)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_14)==RESET);delay_ms(20);KeyNumber=11;}
	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_15)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_15)==RESET);delay_ms(20);KeyNumber=12;}

	//第四行赋值
	 GPIO_ResetBits( GPIOB,  GPIO_Pin_3);
	 GPIO_SetBits( GPIOB,  GPIO_Pin_4);
	 GPIO_SetBits( GPIOB,  GPIO_Pin_5);
	 GPIO_SetBits( GPIOB,  GPIO_Pin_6);

	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_12)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_12)==RESET);delay_ms(20);KeyNumber=13;}
	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_13)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_13)==RESET);delay_ms(20);KeyNumber=14;}
	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_14)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_14)==RESET);delay_ms(20);KeyNumber=15;}
	if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_15)==RESET){delay_ms(20);while(GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_15)==RESET);delay_ms(20);KeyNumber=16;}

	return KeyNumber;
}
