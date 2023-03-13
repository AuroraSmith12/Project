#include "kz.h"
#include "sys.h"
#include "usart.h"
extern uint8_t Data_ID[4][4];

extern uint8_t ERR_COUNT;
extern uint8_t Run_flag;
extern uint8_t Lock_flag;
uint8_t Err_Count=0;
uint8_t data_kz(uint8_t *value)
{
	uint8_t i ,flag=0;
	uint8_t ave;
	int num=0;
	for(i=0;i<4;i++)
	{
		printf("card_id=%d\t",value[i]);
		num+=value[i]*(i+1);
	}
	printf("num=%d\r\n",num);
	ave=num/4;
	printf("ave=%d\r\n",ave);
	switch(ave)
	{
		case 117:flag=1;break;
		case 135:flag=2;break;
		case 249:flag=3;break;
		case 244:flag=4;break;
		case 98:flag=5;break;
		case 39:flag=6;break;
		case 27:flag=7;break;
		case 143:flag=8;break;
		case 223:flag=9;break;
		case 224:flag=10;break;
		default :flag=0;Err_Count++;
		
	}
	if(Err_Count==5)
	{
		Run_flag=0;
		Lock_flag=1;
	}
	return flag;
}

