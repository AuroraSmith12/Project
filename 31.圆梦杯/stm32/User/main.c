#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "mlx90614.h"
#include "bsp_SysTick.h"
#include "gdcgq.h"
#include "flow.h"
#include "usart.h"
#include "bluetooth.h"
#include <stdio.h>

unsigned char arr[]={0xAA,0x02,0x00,0xAC};//播放 -- 4个字节
unsigned char arr1[]={0xAA, 0x1F, 0x02, 0x00, 0x01, 0xCC};// （选曲不播放）            请佩戴口罩          -- 6个字节
unsigned char arr2[]={0xAA, 0x1F, 0x02, 0x00, 0x02, 0xCD};// （选曲不播放）            体温正常            -- 6个字节
unsigned char arr3[]={0xAA, 0x1F, 0x02, 0x00, 0x03, 0xCE};//  （选曲不播放）           体温异常            -- 6个字节
unsigned char arr4[]={0xAA, 0x1F, 0x02, 0x00, 0x04, 0xCF};//  （选曲不播放）           欢迎使用防疫巴士    -- 6个字节
unsigned char arr5[]={0xAA, 0x1F, 0x02, 0x00, 0x05, 0xD0};//  （选曲不播放）           已佩戴好口罩        -- 6个字节
unsigned char arr6[]={0xAA, 0x1F, 0x02, 0x00, 0x06, 0xD1};//  （选曲不播放）           正在进行体温检测     -- 6个字节
unsigned char arr7[]={0xAA, 0x1F, 0x02, 0x00, 0x07, 0xD2};//   （选曲不播放）          正在进行口罩佩戴检测  -- 6个字节
uint16_t people=0;
/*
		人体正常体温：36.2℃～37.2℃
		测温模块：
		SCL--PB10
		SDA--PB11
		
		OLED模块：
		SCL--PB8
		SDA--PB9
		
		光电传感器：
		PB1--黑线
		
		人流量测量：
		PA6--DO

		语音模块：
		PA9接模块RX
		供电用stm32供电
		供电要单独供电，不然就没有语音


	usart.c第58行注释了while,记得测试一下

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
	//串口收到1 -- 表示未佩戴口罩
	//串口收到2 -- 表示佩戴口罩
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
		SendString(USART1,arr1,6);//请佩戴口罩		
		SendString(USART1,arr,4);//播放
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
		SendString(USART1,arr5,6);//已佩戴好口罩		
		SendString(USART1,arr,4);//播放
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
		SendString(USART1,arr2,6);//体温正常		
		SendString(USART1,arr,4);//播放
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
		SendString(USART1,arr3,6);//体温异常		
		SendString(USART1,arr,4);//播放
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
		printf("people:%d\r\n",people);//打印人流量到串口		
	}
	EXTI_ClearITPendingBit(EXTI_Line6);
}
