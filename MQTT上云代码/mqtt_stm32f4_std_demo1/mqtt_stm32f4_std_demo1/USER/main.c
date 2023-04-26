#include "stm32f4xx.h"
#include "sys.h"
#include "usart.h"
#include "esp8266.h"
#include "esp8266_mqtt.h"
#include "delay.h"
#include "led.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int32_t rt;
	int32_t i=0;
	uint32_t delay_1ms_cnt=0;
	char *p=NULL;
	
	//led初始化
	led_init();
	
	//串口1初始化波特率为115200bps
	usart1_init(115200);
	
	//发送数据
	printf("This is esp8266 mqtt with aliyun test by teacher.wen\r\n");
	

	while(esp8266_mqtt_init())
	{
		printf("esp8266_mqtt_init ...");
		
		delay_ms(1000);
	
	
	}
	printf("esp8266 connect aliyun with mqtt success\r\n");	
	
	while(1)
	{
		//检查接收到数据
		if(g_esp8266_rx_end && g_esp8266_transparent_transmission_sta)
		{
			for(i=0;i<g_esp8266_rx_cnt;i++)
			{
	

				//判断的关键字符是否为 1"
				//核心数据，即{"switch_led_1":1}中的“1”
				if(g_esp8266_rx_buf[i]==0x31 && g_esp8266_rx_buf[i+1]==0x22)
				{
					
					//打印关键字符后的 
					
					if(g_esp8266_rx_buf[i]== 0x31)   //'1'
					{
						//判断控制变量
						if( g_esp8266_rx_buf[i+3]=='1' )
							PFout(9)=0;//控制灯亮
						else
							PFout(9)=1;//控制灯灭
					}
	
					break;
				}
	
			}	
			//清空接收缓冲区、接收计数值、接收结束标志位
			memset((void *)g_esp8266_rx_buf,0,sizeof g_esp8266_rx_buf);
			g_esp8266_rx_cnt=0;
			g_esp8266_rx_end=0;
		}
		
		delay_1ms_cnt++;
		
		delay_ms(1);
		
		//1秒时间到达
		if(delay_1ms_cnt >= 1000)
		{
			delay_1ms_cnt=0;

			//发送心跳包
			mqtt_send_heart();
		
			//上报设备状态
			mqtt_report_devices_status();			
		}
	
	}

}



