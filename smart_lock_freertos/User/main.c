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
******************************************************************************/
unsigned  char ZWBD[]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x08,0x32,0x03,0xFF,0xFF,0x00,0x00,0x02,0x3C};
extern volatile uint8_t   FPM10A_RECEICE_BUFFER[51];

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

static TickType_t time_before;
static TickType_t time_now;

static uint16_t mima_flag=0;

static TaskHandle_t test1_handler1;
static TaskHandle_t test2_handler2;
static TaskHandle_t test3_handler3;
static TaskHandle_t test4_handler4;

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
	delay_ms(500);
}
void xun_ka(void)
{
		//Breath();
			keynum=MatrixKeyboard_Init();

		if(MI_OK==PcdRequest(0x52, Card_Type1))  //寻卡函数，如果成功返回MI_OK  打印多次卡号
		{			
			status = PcdAnticoll(Card_ID);//防冲撞 如果成功返回MI_OK
			if(status == MI_OK)

				{
						flag=data_kz(Card_ID);
						if(flag!=0) //选卡成功
						{
							
					//匹配成功就灯闪烁
						 GPIO_ResetBits( GPIOC,  GPIO_Pin_13);
							Lock_Open();
							OLED_ShowString(2,1,"Successed!");
                            delay_ms(1000);
							delay_ms(1000);
                            OLED_Clear();
							Lock_Close();
						 GPIO_SetBits( GPIOC,  GPIO_Pin_13);
						}
						else//匹配错误
						{
							OLED_ShowString(2,1," Failed ");
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
	uint16_t x=1;
	for(z=0;z<6;z++)
	{
		if(arr[z]==arr1[z])
		{
			x=1;
		}
		else
		{
			x=0;
			return 0;
		}
	}
    memset(set,0,10);
	return 1;
}
void first_init_task(void*param)
{
    first_init();
    
    vTaskDelete(NULL);
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
    time_before=xTaskGetTickCount();
        //OLED_ShowNum(1,1,time_before,6);
    int i=0;
    for(i=0;i<6;)
    {

        time_now=xTaskGetTickCount();
        //OLED_ShowNum(3,1,time_now,6);
        keynum_func=MatrixKeyNum_Show();
        if(keynum_func>0&&keynum_func<=9)
        {
            set[i]=keynum_func;
            i++;
            mima_flag=1;
        }
        else
        {
            //memset(set,0,6);
            //return 0;
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
						 GPIO_ResetBits( GPIOC,  GPIO_Pin_13);
							Lock_Open();
							OLED_ShowString(2,1,"Successed!");
                            delay_ms(1000);
							delay_ms(1000);
                            OLED_Clear();
							Lock_Close();
						 GPIO_SetBits( GPIOC,  GPIO_Pin_13);            
        }
        else
        {
							OLED_ShowString(2,1," Failed ");
                            delay_ms(1000);
                            OLED_Clear();            
        }
        ret=0;
        
        
    }
}
void task_idle(void*param)
{
    for(;;)
    {
        
    }
}
int main(void)

{
     NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4);
    
    xTaskCreate(first_init_task,"test1", 100, NULL, 4,&test1_handler1);
	xTaskCreate(xun_ka_task,"test2", 100, NULL, 3,&test2_handler2);
	xTaskCreate(mima_task,"test3", 200, NULL, 3,&test3_handler3);
	//xTaskCreate(task_idle,"test4", 100, NULL, 2,&test4_handler4);

    vTaskStartScheduler();          //开启任务调度
	while(1)
	{
		
	}
}
