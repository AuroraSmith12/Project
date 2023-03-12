#ifndef _USART_H_
#define _USART_H_
#include "stm32f10x.h"

void Usart_Init(void);
uint16_t Receive_Byte(USART_TypeDef*USARTx);


#endif
