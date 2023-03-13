#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"
#include "stm32f10x_spi.h"
#include "RC522.h"
#include "delay.h"
#include "spi_driver.h"
#include "kz.h"
#include "led.h"
#include "OLED.h"
#include "MatrixKeyboard.h"
#include "lock.h"
#include <string.h>
#include "usart_esp8266.h"
#include "dht11.h"
#include "event_groups.h"

/******************************************************************************


硬件连接
STM32F103C8T6       RC522模块
PA4（SPI1_NSS）      	SDA
PA5（SPI1_SCK）				SCK
PA6（SPI1_MISO）			MISO
PA7（SPI1_MOSI）			MOSI
PA11（RST）						RST
PB1（IRQ）						IRQ  未定义

矩阵键盘
Pb12--C4
Pb13--C3
Pb14--C2
Pb15--C1
Pb3--R1
Pb4--R2
Pb5--R3
Pb6--R4


OLED
pb8--SCL
pb9--SDA

ESP8266

pb11--接esp8266的tx

DHT11

pb10--接dht11data脚


******************************************************************************/
extern uint16_t data_rx_usart3;
uint8_t Card_Type1[2];  
uint8_t Card_ID[4]; 
uint8_t Card_KEY[6] = {0xff,0xff,0xff,0xff,0xff,0xff};    //{0x11,0x11,0x11,0x11,0x11,0x11};   //密码
uint8_t Card_Data[16];
uint8_t status;
uint8_t flag;
uint8_t Run_flag=1;
uint8_t Lock_flag=0;
u16 led0pwmval=0;    
u8 dir=1;
static uint16_t keynum=0;
static uint16_t keynum_func;
uint16_t key[10]={1,2,3,4,5,6};
uint16_t set[10]={0};
uint16_t i=0;


extern char arr[5];
static uint16_t mima_flag=0;

static EventGroupHandle_t even_group_handler;

static TaskHandle_t test1_handler1;
static TaskHandle_t test2_handler2;
static TaskHandle_t test3_handler3;
static TaskHandle_t test4_handler4;
static TaskHandle_t test5_handler5;
static TaskHandle_t test6_handler6;

void first_init()
{
	Card_Type1[0]=0x04;
	Card_Type1[1]=0x00;
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 //串口初始化为115200		
	RC522_IO_Init();
	PcdReset();  //复位RC522
	PcdAntennaOff();  //关闭天线
	delay_ms(100);
	PcdAntennaOn();  //开启天线
	
	LED_Init();
	OLED_Init();
	Lock_Init();
    
    usart_esp8266_init();
	delay_ms(500);
}
void xun_ka(void)
{
		if(MI_OK==PcdRequest(0x52, Card_Type1))  //寻卡函数，如果成功返回MI_OK  打印多次卡号
		{			
			status = PcdAnticoll(Card_ID);//防冲撞 如果成功返回MI_OK
			if(status == MI_OK)
				{
						flag=data_kz(Card_ID);
						if(flag!=0) //选卡成功
						{
                            xEventGroupSetBits(  even_group_handler,(1<<2) );

						}
                        else
                        {
                        OLED_ShowString(3,1," Failed ");
                        delay_ms(1000);
                        OLED_Clear();     
                        }                        
				}			
		}
	}

uint16_t MatrixKeyNum_Show(void)
{
	keynum=MatrixKeyboard_Init();		
    return keynum;
}
uint16_t Compare(uint16_t*arr,uint16_t*arr1)
{
	uint16_t z=0;

	for(z=0;z<6;z++)
	{
		if(arr[z]!=arr1[z])
		{
            return 0;
		}

	}
    memset(set,0,10);
	return 1;
}

void xun_ka_task(void*param)
{
    for(;;)
    {
        portDISABLE_INTERRUPTS();
        xun_ka();
        portENABLE_INTERRUPTS();
    }
}
int passward_input(void)
{
    int i=0;
    for(i=0;i<6;)
    {
        keynum_func=MatrixKeyNum_Show();
        if(keynum_func>0&&keynum_func<=9)
        {
            set[i]=keynum_func;
            i++;
            mima_flag=1;
        }
        vTaskDelay(1);
    }
    return 1;
}
void mima_task(void*param)
{
    uint16_t ret=0;
    for(;;)
    {
        passward_input();
        if(mima_flag)
        {
        ret=Compare(key,set);
        mima_flag=0;
        }
        if(ret)/* 密码正确 */
        {
        xEventGroupSetBits(  even_group_handler,(1<<1) );

        }
        else
        {
		OLED_ShowString(3,1," Failed ");
        delay_ms(1000);
        OLED_Clear();     
        }
        ret=0;            
    }
}
void task_esp8266(void*param)
{
    for(;;)
    {
        if(data_rx_usart3)/* 密码正确 */
        {
			 xEventGroupSetBits(  even_group_handler,(1<<0) );
        }      
        data_rx_usart3=0;
        vTaskDelay(1);
    }
}
void dht11_task(void*param)
{

    for(;;)
    {
        OLED_ShowString(1,1,"Hum:");
		OLED_ShowString(2,1,"Tem:");
        OLED_ShowString(1,7,".");
		OLED_ShowString(2,7,".");
		DHT11_Start();
		if(arr[0]+arr[1]+arr[2]+arr[3]==arr[4])//验证校验位
		{
			OLED_ShowNum(1,5,arr[0]/10,1);
			OLED_ShowNum(1,6,arr[0]%10,1);
			OLED_ShowNum(1,8,arr[1]/10,1);
			OLED_ShowNum(1,9,arr[1]%10,1);
			
			OLED_ShowNum(2,5,arr[2]/10,1);
			OLED_ShowNum(2,6,arr[2]%10,1);
			OLED_ShowNum(2,8,arr[3]/10,1);
			OLED_ShowNum(2,9,arr[3]%10,1);
            vTaskDelay(3);
        }   
    }
}
void lock_open_task(void*param)
{
	for(;;)
		{
		
       xEventGroupWaitBits(  even_group_handler,(1<<0)|(1<<1)|(1<<2),pdTRUE,pdFALSE,portMAX_DELAY );
       GPIO_ResetBits( GPIOC,	GPIO_Pin_13);
	   Lock_Open();
	   OLED_ShowString(3,1,"Successed!");
	   delay_ms(1000);
	   delay_ms(1000);
	   OLED_Clear();
	   Lock_Close();
       GPIO_SetBits( GPIOC,  GPIO_Pin_13);
		}
}
void first_init_task(void*param)
{
    first_init();
	xTaskCreate(xun_ka_task,"test2", 100, NULL, 3,&test2_handler2);
	xTaskCreate(mima_task,"test3", 200, NULL, 3,&test3_handler3);
	xTaskCreate(task_esp8266,"test4", 100, NULL, 3,&test4_handler4);
	xTaskCreate(dht11_task,"test5", 100, NULL, 3,&test5_handler5);
	xTaskCreate(lock_open_task,"test5", 100, NULL, 3,&test6_handler6);    
    vTaskDelete(NULL);
}
int main(void)

{
     NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4);
	 even_group_handler=xEventGroupCreate();	 
    xTaskCreate(first_init_task,"test1", 100, NULL, 5,&test1_handler1);

    vTaskStartScheduler();          //开启任务调度
	while(1)
	{
		
	}
}
