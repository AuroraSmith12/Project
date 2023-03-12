#ifndef _FINGERPRINT_H_
#define _FINGERPRINT_H_
#include "stm32f10x.h"
void FP_Init(void);
void SendByte(USART_TypeDef*USARTx,uint16_t Data);
void SendString(USART_TypeDef*USARTx,unsigned char*str);
void ms_delay(uint16_t time);
uint16_t ReceiveByte(USART_TypeDef*USARTx);
void FPM10A_Receive_Data(uint16_t length);
void iwdg_init(void);




#endif
