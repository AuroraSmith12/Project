#ifndef _DHT11_H_


void ms_delay(uint16_t time);
void us_delay(u16 time);

void SetOutput_Mode(void);
void SetInput_Mode(void);
void DHT11_Start(void ); //返回0表示通讯失败,返回1则表示通讯成功
void IWDG_Init(void);


#define _DHT11_H_


#endif


