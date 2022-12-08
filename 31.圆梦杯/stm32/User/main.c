#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "mlx90614.h"
#include "bsp_SysTick.h"
#include "gdcgq.h"
#include "flow.h"
#include "usart.h"
#include "bluetooth.h"
#include <stdio.h>

unsigned char arr[]={0xAA,0x02,0x00,0xAC};//���� -- 4���ֽ�
unsigned char arr1[]={0xAA, 0x1F, 0x02, 0x00, 0x01, 0xCC};// ��ѡ�������ţ�            ���������          -- 6���ֽ�
unsigned char arr2[]={0xAA, 0x1F, 0x02, 0x00, 0x02, 0xCD};// ��ѡ�������ţ�            ��������            -- 6���ֽ�
unsigned char arr3[]={0xAA, 0x1F, 0x02, 0x00, 0x03, 0xCE};//  ��ѡ�������ţ�           �����쳣            -- 6���ֽ�
unsigned char arr4[]={0xAA, 0x1F, 0x02, 0x00, 0x04, 0xCF};//  ��ѡ�������ţ�           ��ӭʹ�÷��߰�ʿ    -- 6���ֽ�
unsigned char arr5[]={0xAA, 0x1F, 0x02, 0x00, 0x05, 0xD0};//  ��ѡ�������ţ�           ������ÿ���        -- 6���ֽ�
unsigned char arr6[]={0xAA, 0x1F, 0x02, 0x00, 0x06, 0xD1};//  ��ѡ�������ţ�           ���ڽ������¼��     -- 6���ֽ�
unsigned char arr7[]={0xAA, 0x1F, 0x02, 0x00, 0x07, 0xD2};//   ��ѡ�������ţ�          ���ڽ��п���������  -- 6���ֽ�
uint16_t people=0;
/*
		�����������£�36.2�桫37.2��
		����ģ�飺
		SCL--PB10
		SDA--PB11
		
		OLEDģ�飺
		SCL--PB8
		SDA--PB9
		
		��紫������
		PB1--����
		
		������������
		PA6--DO

		����ģ�飺
		PA9��ģ��RX
		������stm32����
		����Ҫ�������磬��Ȼ��û������


	usart.c��58��ע����while,�ǵò���һ��

*/
void delay_ms(uint16_t time)
{
	uint16_t i=0;
	while(time --)
	{
		i=12000;
		while(i--);
	}
}
int main(void)
{
	//�����յ�1 -- ��ʾδ�������
	//�����յ�2 -- ��ʾ�������
	usart_init();
	bluetooth_init();
	gd_init();
	flow_init();
	OLED_Init();
	SMBus_Init();
	SysTick_Init();
	OLED_ShowString(1,6,"00.00");
	OLED_ShowString(1,1,"Temp:");
	OLED_ShowString(2,1,"flow:");
	
	while(1)
	{
		//uint16_t data_f=0;
		//data_f=Receive_Byte( USART1);
		//if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_1)==RESET)
		//{
		float a=SMBus_ReadTemp();
		OLED_ShowNum(1,6,a,2);
		OLED_ShowNum(1,9,(uint16_t)(a*100)%100,2);
		delay_ms(100);
		//}
	if(Receive_Byte( USART2) =='1')
	{
		SendString(USART1,arr1,6);//���������		
		SendString(USART1,arr,4);//����
		OLED_ShowNum(2,6,people,3);
		if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_1)==RESET)
		{
		float a=SMBus_ReadTemp();
		OLED_ShowNum(1,6,a,2);
		OLED_ShowNum(1,9,(uint16_t)(a*100)%100,2);
		delay_ms(100);
		}
		delay_ms(3000);
	}
	if(Receive_Byte( USART2)=='2')
	{
		SendString(USART1,arr5,6);//������ÿ���		
		SendString(USART1,arr,4);//����
		OLED_ShowNum(2,6,people,3);
		if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_1)==RESET)
		{
		float a=SMBus_ReadTemp();
		OLED_ShowNum(1,6,a,2);
		OLED_ShowNum(1,9,(uint16_t)(a*100)%100,2);
		delay_ms(100);
		}
		delay_ms(3000);		
		
	}
//	data_f=0;
	//USART1->DR='0';
	
	uint16_t data_tiwen=SMBus_ReadTemp();
	if(data_tiwen>32&&data_tiwen<38)
	{
		SendString(USART1,arr2,6);//��������		
		SendString(USART1,arr,4);//����
		OLED_ShowNum(2,6,people,3);
		if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_1)==RESET)
		{
		float a=SMBus_ReadTemp();
		OLED_ShowNum(1,6,a,2);
		OLED_ShowNum(1,9,(uint16_t)(a*100)%100,2);
		delay_ms(100);
		}
		delay_ms(3000);	
	}
	if(data_tiwen>38)
	{
		SendString(USART1,arr3,6);//�����쳣		
		SendString(USART1,arr,4);//����
		OLED_ShowNum(2,6,people,3);
		if( GPIO_ReadInputDataBit( GPIOB,  GPIO_Pin_1)==RESET)
		{
		float a=SMBus_ReadTemp();
		OLED_ShowNum(1,6,a,2);
		OLED_ShowNum(1,9,(uint16_t)(a*100)%100,2);
		delay_ms(100);
		}
		delay_ms(3000);	
	}
		OLED_ShowNum(2,6,people,3);
		delay_ms(100);
	data_tiwen=0;	
OLED_ShowString(1,6,"00.00");
//	OLED_ShowString(1,1,"Temp:");
//	OLED_ShowString(2,1,"flow:");
	}

}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line6)==SET)
	{
		people++;
		delay_ms(200);
		printf("people:%d\r\n",people);//��ӡ������������		
	}
	EXTI_ClearITPendingBit(EXTI_Line6);
}
