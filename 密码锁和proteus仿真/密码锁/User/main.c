#include "stm32f10x.h"                  // Device header
#include "MatrixKeyboard.h"
#include "buzzer.h"
static uint8_t keynum=0;
static uint16_t key[6]={1,2,3,4,5,6};
static uint16_t compare[6]={0};
static uint8_t cnt=0;
static uint8_t cmp=0;
static uint16_t flag=0;
void pwd_input(void)
{
        if(keynum>0&&keynum<10)
        {
            compare[cnt++]=keynum;
            if(cnt==6)
            {
                flag=1;
                cnt=0;
            }
        }    
}
int pwd_compare(uint16_t*compare,uint16_t*key)
{
    if(flag)
    {
        flag=0;
    for(cmp=0;cmp<6;cmp++)
    {
        if(compare[cmp]!=key[cmp])
            return -1;
            
    }
    return 0;

    }
    return -2;
}
int main(void)
{
    buzzer_init();
	while(1)
	{
		keynum=MatrixKeyboard_Init();
        pwd_input();
        if(!pwd_compare(compare,key))//ÃÜÂëÕıÈ·
        {
            GPIO_ResetBits(GPIOB,GPIO_Pin_4);//ÁÁµÆÌáÊ¾
            delay_ms(2000);
            GPIO_SetBits(GPIOB,GPIO_Pin_4);
            delay_ms(2000);
        }
        if(-1==(pwd_compare(compare,key)))//ÃÜÂë´íÎó
        {
            GPIO_ResetBits(GPIOB,GPIO_Pin_5);//ÁÁµÆÌáÊ¾
            delay_ms(2000);
            GPIO_SetBits(GPIOB,GPIO_Pin_5);
            delay_ms(2000);            
        }
                    GPIO_ResetBits(GPIOB,GPIO_Pin_5);//ÁÁµÆÌáÊ¾
            delay_ms(2000);
            GPIO_SetBits(GPIOB,GPIO_Pin_5);
            delay_ms(2000); 
	}
}
