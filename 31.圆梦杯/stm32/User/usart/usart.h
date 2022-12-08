#ifndef _USART_H_
#define _USART_H_
#include "stm32f10x.h"
#define sda(n)  n? GPIO_SetBits(GPIOA,  GPIO_Pin_9): GPIO_ResetBits( GPIOA,  GPIO_Pin_9)

void usart_init(void);
void send_data(USART_TypeDef* USARTx, uint16_t Data);
void SendString(USART_TypeDef*USARTx,unsigned  char*str,char num);
uint16_t Receive_Byte(USART_TypeDef* USARTx);



#endif
