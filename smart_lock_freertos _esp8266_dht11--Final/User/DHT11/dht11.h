#ifndef _DHT11_H_


void ms_delay(uint16_t time);
void us_delay(u16 time);

void SetOutput_Mode(void);
void SetInput_Mode(void);
void DHT11_Start(void ); //����0��ʾͨѶʧ��,����1���ʾͨѶ�ɹ�
void IWDG_Init(void);


#define _DHT11_H_


#endif


