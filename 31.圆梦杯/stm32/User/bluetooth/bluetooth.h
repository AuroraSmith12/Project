#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_
#include "stm32f10x.h"
#include <stdio.h>
void bluetooth_init(void);
void UARTSendByte( USART_TypeDef* USARTx, uint16_t Data);
void UARTSendString( USART_TypeDef* USARTx, char *str1);//·¢ËÍ×Ö·û´®



#endif
