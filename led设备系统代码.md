### led_device.h

```
#ifndef __LED_DEVICE_H
#define __LED_DEVICE_H

#ifndef NULL
#define NULL (void *)0
#endif

#define LED_WHITE 	0
#define LED_BLUE 	1
#define LED_GREEN 	2

typedef struct LEDDevice {
	int which;

	/* 初始化LED设备, 成功则返回0 */
	int (*Init)(struct LEDDevice *ptLEDDevice);

	/* 控制LED设备, iStatus取值: 1-亮,0-灭 */
	int (*Control)(struct LEDDevice *ptLEDDevice, int iStatus);

	/* 未实现 */
	void (*SetColor)(struct LEDDevice *ptLEDDevice, int iColor);

	/* 未实现 */
	void (*SetBrightness)(struct LEDDevice *ptLEDDevice, int iBrightness);
}LEDDevice, *PLEDDevice;

/**********************************************************************
 * 函数名称： GetLEDDevice
 * 功能描述： 获取LED设备
 * 输入参数： which-哪个LED设备
 *            取值有: LED_WHITE,LED_BLUE或LED_GREEN
 * 输出参数： 无
 * 返 回 值： 成功-LEDDevice指针, 失败-NULL
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/26	     V1.0	  韦东山	      创建
 ***********************************************************************/
PLEDDevice GetLEDDevice(int which);


#endif /* __LED_DEVICE_H */


```

### led_device.c

```

#include <kal_led_device.h>
#include "led_device.h"

/**********************************************************************
 * 函数名称： KAL_LEDDeviceInit
 * 功能描述： 设备层的LED初始化函数
 * 输入参数： ptLEDDevice-哪个LED设备
 * 输出参数： 无
 * 返 回 值： 0-成功
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/26	     V1.0	  韦东山	      创建
 ***********************************************************************/
static int LEDDeviceInit(struct LEDDevice *ptLEDDevice)
{
	return KAL_LEDDeviceInit(ptLEDDevice);
}

/**********************************************************************
 * 函数名称： LEDDeviceControl
 * 功能描述： 设备层的LED控制函数
 * 输入参数： ptLEDDevice-哪个LED设备
 * 输入参数： iStatus, 1-亮, 0-灭
 * 输出参数： 无
 * 返 回 值： 0-成功
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/26	     V1.0	  韦东山	      创建
 ***********************************************************************/
static int LEDDeviceControl(struct LEDDevice *ptLEDDevice, int iStatus)
{
	return KAL_LEDDeviceControl(ptLEDDevice, iStatus);
}


static LEDDevice g_tLEDDevices[] = {
	{LED_WHITE, LEDDeviceInit, LEDDeviceControl},
	{LED_BLUE,  LEDDeviceInit, LEDDeviceControl},
	{LED_GREEN, LEDDeviceInit, LEDDeviceControl},
};

/**********************************************************************
 * 函数名称： GetLEDDevice
 * 功能描述： 获取LED设备
 * 输入参数： which-哪个LED设备
 *            取值有: LED_WHITE,LED_BLUE或LED_GREEN
 * 输出参数： 无
 * 返 回 值： 成功-LEDDevice指针, 失败-NULL
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/26	     V1.0	  韦东山	      创建
 ***********************************************************************/
PLEDDevice GetLEDDevice(int which)
{
	if (which >= LED_WHITE && which <= LED_GREEN)
		return &g_tLEDDevices[which];
	else
		return NULL;
}


```

### kal_led_device.h

```
#ifndef __KAL_LED_DEVICE_H
#define __KAL_LED_DEVICE_H

#include <led_device.h>

/**********************************************************************
 * 函数名称： KAL_LEDDeviceInit
 * 功能描述： 内核抽象层的LED初始化函数, 内核不一样时请修改此函数
 * 输入参数： ptLEDDevice-哪个LED设备
 * 输出参数： 无
 * 返 回 值： 0-成功
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/26	     V1.0	  韦东山	      创建
 ***********************************************************************/
int KAL_LEDDeviceInit(struct LEDDevice *ptLEDDevice);

/**********************************************************************
 * 函数名称： KAL_LEDDeviceControl
 * 功能描述： 内核抽象层的LED控制函数, 内核不一样时请修改此函数
 * 输入参数： ptLEDDevice-哪个LED设备
 * 输入参数： iStatus, 1-亮, 0-灭
 * 输出参数： 无
 * 返 回 值： 0-成功
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/26	     V1.0	  韦东山	      创建
 ***********************************************************************/
int KAL_LEDDeviceControl(struct LEDDevice *ptLEDDevice, int iStatus);


#endif /* __KAL_LED_DEVICE_H */


```



### kal_led_device.c

```

#include <led_device.h>
#include <led_device.h>
#include <cal_led_device.h>

/**********************************************************************
 * 函数名称： KAL_LEDDeviceInit
 * 功能描述： 内核抽象层的LED初始化函数, 内核不一样时请修改此函数
 * 输入参数： ptLEDDevice-哪个LED设备
 * 输出参数： 无
 * 返 回 值： 0-成功
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/26	     V1.0	  韦东山	      创建
 ***********************************************************************/
int KAL_LEDDeviceInit(struct LEDDevice *ptLEDDevice)
{	
	/* 对于裸机/FreeRTOS */
	return CAL_LEDDeviceInit(ptLEDDevice);

	/* 对于RT-Thread */

	/* 对于Linux */
}

/**********************************************************************
 * 函数名称： KAL_LEDDeviceControl
 * 功能描述： 内核抽象层的LED控制函数, 内核不一样时请修改此函数
 * 输入参数： ptLEDDevice-哪个LED设备
 * 输入参数： iStatus, 1-亮, 0-灭
 * 输出参数： 无
 * 返 回 值： 0-成功
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/26	     V1.0	  韦东山	      创建
 ***********************************************************************/
int KAL_LEDDeviceControl(struct LEDDevice *ptLEDDevice, int iStatus)
{
	/* 对于裸机/FreeRTOS */
	return CAL_LEDDeviceControl(ptLEDDevice, iStatus);

	/* 对于RT-Thread */

	/* 对于Linux */
}



```

### cal_led_device.h

```
#ifndef __CAL_LED_DEVICE_H
#define __CAL_LED_DEVICE_H


/**********************************************************************
 * 函数名称： CAL_LEDDeviceInit
 * 功能描述： 芯片抽象层的LED初始化函数, 芯片函数不一样时请修改此函数
 * 输入参数： ptLEDDevice-哪个LED设备
 * 输出参数： 无
 * 返 回 值： 0-成功
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/26	     V1.0	  韦东山	      创建
 ***********************************************************************/
int CAL_LEDDeviceInit(struct LEDDevice *ptLEDDevice);

/**********************************************************************
 * 函数名称： CAL_LEDDeviceControl
 * 功能描述： 芯片抽象层的LED控制函数, 芯片函数不一样时请修改此函数
 * 输入参数： ptLEDDevice-哪个LED设备
 * 输入参数： iStatus, 1-亮, 0-灭
 * 输出参数： 无
 * 返 回 值： 0-成功
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/26	     V1.0	  韦东山	      创建
 ***********************************************************************/
int CAL_LEDDeviceControl(struct LEDDevice *ptLEDDevice, int iStatus);


#endif /* __CAL_LED_DEVICE_H */


```



### cal_led_device.c

```

#include <led_device.h>
#include <driver_led.h>


/**********************************************************************
 * 函数名称： CAL_LEDDeviceInit
 * 功能描述： 芯片抽象层的LED初始化函数, 芯片函数不一样时请修改此函数
 * 输入参数： ptLEDDevice-哪个LED设备
 * 输出参数： 无
 * 返 回 值： 0-成功
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/26	     V1.0	  韦东山	      创建
 ***********************************************************************/
int CAL_LEDDeviceInit(struct LEDDevice *ptLEDDevice)
{	
	/* 对于hal */
	/* 已经在MX_GPIO_Init初始化了引脚 */
	return 0;
}

/**********************************************************************
 * 函数名称： CAL_LEDDeviceControl
 * 功能描述： 芯片抽象层的LED控制函数, 芯片函数不一样时请修改此函数
 * 输入参数： ptLEDDevice-哪个LED设备
 * 输入参数： iStatus, 1-亮, 0-灭
 * 输出参数： 无
 * 返 回 值： 0-成功
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/26	     V1.0	  韦东山	      创建
 ***********************************************************************/
int CAL_LEDDeviceControl(struct LEDDevice *ptLEDDevice, int iStatus)
{
	/* 对于hal */
	return HAL_LEDDeviceControl(ptLEDDevice, iStatus);
}



```



### driver_led.h

```
/*  Copyright (s) 2019 深圳百问网科技有限公司
 *  All rights reserved
 * 
 * 文件名称：driver_led.h
 * 摘要：
 *  
 * 修改历史     版本号        Author       修改内容
 *--------------------------------------------------
 * 2020.6.6      v01         百问科技      创建文件
 *--------------------------------------------------
*/

#ifndef __DRIVER_LED_H
#define __DRIVER_LED_H

#include <led_device.h>

/*
 *  函数名：int HAL_LEDDeviceControl(struct LEDDevice *ptLEDDevice, int iStatus)
 *  输入参数：ptLEDDevice-哪个LED
 *  输入参数：iStatus-LED状态, 1-亮, 0-灭
 *  输出参数：无
 *  返回值：0-成功, -1: 失败
 */
int HAL_LEDDeviceControl(struct LEDDevice *ptLEDDevice, int iStatus);

#endif /* __DRIVER_LED_H */

```

### driver_led.c

```
/** @file		driver_led.c
  * @author 	百问网团队
  * @version	v1.0
  * @date		2021-8-10
  * *******************************************
  * @brief		LED驱动源文件
  * 			+
  *
  * @include	包含的头文件
  * 			+ main.h
  * 			+ driver_led.h
  * -------------------------------------------
  * *******************************************
  * -------------------------------------------
  * @attention
  *
  * Copyright (c) 深圳百问网科技有限公司
  * All rights reserved.
  *
  */
#include <led_device.h>

#include "driver_led.h"
#include "main.h"

/*
 *  函数名：int HAL_LEDDeviceControl(struct LEDDevice *ptLEDDevice, int iStatus)
 *  输入参数：ptLEDDevice-哪个LED
 *  输入参数：iStatus-LED状态, 1-亮, 0-灭
 *  输出参数：无
 *  返回值：0-成功, -1: 失败
 */
int HAL_LEDDeviceControl(struct LEDDevice *ptLEDDevice, int iStatus)
{
	GPIO_PinState pinstate;
	
	if (!ptLEDDevice)
		return -1;

	pinstate = iStatus ? GPIO_PIN_RESET : GPIO_PIN_SET;
	
	switch (ptLEDDevice->which)
	{
		case LED_WHITE: 
		{
		    HAL_GPIO_WritePin(WHITE_GPIO_Port, WHITE_Pin, pinstate);
			break;
		}

		case LED_BLUE: 
		{
		    HAL_GPIO_WritePin(BLUE_GPIO_Port, BLUE_Pin, pinstate);
			break;
		}

		case LED_GREEN: 
		{
		    HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, pinstate);
			break;
		}

		default:
			return -1;
	}

	return 0;
	
}



```

### led_test.c

```
#include <kal_time.h>
#include <led_device.h>
#include <stdio.h>


/**********************************************************************
 * 函数名称： led_test
 * 功能描述： 设备系统LED设备单元测试函数
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/27	     V1.0	  韦东山	      创建
 ***********************************************************************/
void led_test(void)
{
	PLEDDevice p1 = GetLEDDevice(LED_WHITE);
	PLEDDevice p2 = GetLEDDevice(LED_BLUE);
	PLEDDevice p3 = GetLEDDevice(LED_GREEN);

	p1->Init(p1);
	p2->Init(p2);
	p3->Init(p3);

	while (1)
	{
		p1->Control(p1, 1);
		p2->Control(p2, 1);
		p3->Control(p3, 1);

		KAL_Delay(500);

		p1->Control(p1, 0);
		p2->Control(p2, 0);
		p3->Control(p3, 0);
		
		KAL_Delay(500);
		
	}
}


```

### kal_time.h

```

#ifndef __KAL_TIMER_H
#define __KAL_TIMER_H

#include <input_system.h>

/**********************************************************************
 * 函数名称： KAL_GetTime
 * 功能描述： 获得系统时间
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值：系统时间
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/ 
TIME_T KAL_GetTime(void);

/**********************************************************************
 * 函数名称： KAL_Delay
 * 功能描述： 延时
 * 输入参数： DelayMS-延时时间,单位: ms
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/27	     V1.0	  韦东山	      创建
 ***********************************************************************/
void KAL_Delay(unsigned int DelayMS);


#endif /* __KAL_TIMER_H */


```

### kal_time.c

```

#include <cal_time.h>

/**********************************************************************
 * 函数名称： KAL_GetTime
 * 功能描述： 获得系统时间
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值：系统时间
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/
TIME_T KAL_GetTime(void)
{
	return CAL_GetTime();
}


/**********************************************************************
 * 函数名称： KAL_Delay
 * 功能描述： 延时
 * 输入参数： DelayMS-延时时间,单位: ms
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/27	     V1.0	  韦东山	      创建
 ***********************************************************************/
void KAL_Delay(unsigned int DelayMS)
{
	CAL_Delay(DelayMS);
}




```

### cal_time.h

```

#ifndef __CAL_TIMER_H
#define __CAL_TIMER_H


#include <input_system.h>
 
/**********************************************************************
 * 函数名称： CAL_GetTime
 * 功能描述： 获得系统时间
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值：系统时间
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/ 
TIME_T CAL_GetTime(void);

/**********************************************************************
 * 函数名称： CAL_Delay
 * 功能描述： 延时
 * 输入参数： DelayMS-延时时间,单位: ms
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/27	     V1.0	  韦东山	      创建
 ***********************************************************************/
void CAL_Delay(unsigned int DelayMS);

#endif /* __CAL_TIMER_H */


```

### cal_time.c

```
#include <input_system.h>
#include "stm32f1xx_hal.h"

/**********************************************************************
 * 函数名称： CAL_GetTime
 * 功能描述： 获得系统时间
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值：系统时间
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/ 
TIME_T CAL_GetTime(void)
{
	/* tick中断里面: count++ */
	return HAL_GetTick();
}

/**********************************************************************
 * 函数名称： CAL_Delay
 * 功能描述： 延时
 * 输入参数： DelayMS-延时时间,单位: ms
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/27	     V1.0	  韦东山	      创建
 ***********************************************************************/
void CAL_Delay(unsigned int DelayMS)
{
	/* HAL函数里是1ms发生一次中断 */
	HAL_Delay(DelayMS);
}


```



### input_system.h

```
#ifndef __INPUT_SYSTEM_H
#define __INPUT_SYSTEM_H

#ifndef NULL
#define NULL (void *)0
#endif

#define TIME_T int
#define INTPU_BUF_LEN 20

typedef enum
{    
	INPUT_EVENT_TYPE_KEY,
	INPUT_EVENT_TYPE_TOUCH,
	INPUT_EVENT_TYPE_NET,
	INPUT_EVENT_TYPE_STDIO
}INPUT_EVENT_TYPE;

typedef struct InputEvent {
	TIME_T time;
	INPUT_EVENT_TYPE eType;
	int iX;
	int iY;
	int iKey;
	int iPressure;
	char str[INTPU_BUF_LEN];
}InputEvent, *PInputEvent;

typedef struct InputDevice {
	char *name;
	int (*GetInputEvent)(PInputEvent ptInputEvent);
	int (*DeviceInit)(void);
	int (*DeviceExit)(void);
	struct InputDevice *pNext;
}InputDevice, *PInputDevice;


/**********************************************************************
 * 函数名称： AddInputDevices
 * 功能描述： 注册多个输入设备
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/
void AddInputDevices(void);


/**********************************************************************
 * 函数名称： InitInputDevices
 * 功能描述： 初始化所有的输入设备
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/
void InitInputDevices(void);

/**********************************************************************
 * 函数名称： InputDeviceRegister
 * 功能描述： 注册一个输入设备
 * 输入参数： ptInputDevice-输入设备
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/
void InputDeviceRegister(PInputDevice ptInputDevice);


#endif /* __INPUT_SYSTEM_H */




```

### input_system.c

```

#include "input_system.h"
#include <gpio_key.h>


static PInputDevice g_ptInputDevices;

/**********************************************************************
 * 函数名称： InputDeviceRegister
 * 功能描述： 注册一个输入设备
 * 输入参数： ptInputDevice-输入设备
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/
void InputDeviceRegister(PInputDevice ptInputDevice)
{
	ptInputDevice->pNext = g_ptInputDevices;
	g_ptInputDevices = ptInputDevice;
}

/**********************************************************************
 * 函数名称： AddInputDevices
 * 功能描述： 注册多个输入设备
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/
void AddInputDevices(void)
{
	AddInputDeviceGPIOKey();
}

/**********************************************************************
 * 函数名称： InitInputDevices
 * 功能描述： 初始化所有的输入设备
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/
void InitInputDevices(void)
{
	PInputDevice pDev = g_ptInputDevices;

	while (pDev)
	{
		pDev->DeviceInit();
		pDev = pDev->pNext;
	}
}


```

### gpio_key.h

```

#ifndef __GPIO_KEY_H
#define __GPIO_KEY_H

#define K1_CODE 1
#define K2_CODE 2


/**********************************************************************
 * 函数名称： AddInputDeviceGPIOKey
 * 功能描述： 注册GPIO按键设备
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/
void AddInputDeviceGPIOKey(void);


#endif /* __GPIO_KEY_H */


```

### gpio_key,c

```

#include "input_system.h"
#include "input_buffer.h"

#include <kal_gpio_key.h>


/**********************************************************************
 * 函数名称： GPIOKeyInit
 * 功能描述： 初始化GPIO按键
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 0-成功, 其他值-失败
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/ 
static int GPIOKeyInit(void)
{
	KAL_GPIOKkeyInit();
	return 0;
}


/* 为GPIO按键构造一个InputDevice */

static InputDevice g_tKeyDevice = {
	"gpio_key",
	NULL,
	GPIOKeyInit,
	NULL,
};

/**********************************************************************
 * 函数名称： AddInputDeviceGPIOKey
 * 功能描述： 注册GPIO按键设备
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/
void AddInputDeviceGPIOKey(void)
{
	InputDeviceRegister(&g_tKeyDevice);
}



```

### kal_gpio_key.h

```
#ifndef __KAL_GPIO_KEY_H
#define __KAL_GPIO_KEY_H

/**********************************************************************
 * 函数名称： KAL_GPIOKkeyInit
 * 功能描述： 内核抽象层的GPIO按键初始化函数, 内核不一样时请修改此函数
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/
void KAL_GPIOKkeyInit(void);

#endif /* __KAL_GPIO_KEY_H */


```

### kal_gpio_key.c

```

#include <cal_gpio_key.h>


/**********************************************************************
 * 函数名称： KAL_GPIOKkeyInit
 * 功能描述： 内核抽象层的GPIO按键初始化函数, 内核不一样时请修改此函数
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/
void KAL_GPIOKkeyInit(void)
{
	/* 对于裸机: 注册中断 */
	CAL_GPIOKkeyInit();

	/* 对于RTOS: 创建任务 */
}



```

### cal_gpio_key.h

```

#ifndef __CAL_GPIO_KEY_H
#define __CAL_GPIO_KEY_H


/**********************************************************************
 * 函数名称： CAL_GPIOKkeyInit
 * 功能描述： 芯片抽象层的GPIO按键初始化函数, 芯片函数不一样时请修改此函数
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/
void CAL_GPIOKkeyInit(void);

#endif /* __CAL_GPIO_KEY_H */


```

### cal_gpio_key.c

```

#include <driver_key.h>

/**********************************************************************
 * 函数名称： CAL_GPIOKkeyInit
 * 功能描述： 芯片抽象层的GPIO按键初始化函数, 芯片函数不一样时请修改此函数
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期       版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2021/09/24	     V1.0	  韦东山	      创建
 ***********************************************************************/
void CAL_GPIOKkeyInit(void)
{
	/* 调用芯片相关的代码,注册GPIO中断 */
	/* 对于ST芯片 */
	KEY_GPIO_ReInit();
}



```

### driver_key.h

```
#ifndef __DRIVER_KEY_H
#define __DRIVER_KEY_H

#include "stm32f1xx_hal.h"

#define KEY_PRESSED			(0)
#define KEY_RELEASED		(1)

#define KEY1_PIN				GPIO_PIN_14
#define KEY2_PIN				GPIO_PIN_15

#define KEY1_PORT				GPIOE
#define KEY2_PORT				GPIOE

#define KEY1_GPIO_CLK_EN()	__HAL_RCC_GPIOE_CLK_ENABLE()
#define KEY2_GPIO_CLK_EN()	__HAL_RCC_GPIOE_CLK_ENABLE()

#define K1_STATUS							HAL_GPIO_ReadPin(KEY1_PORT, KEY1_PIN)
#define K2_STATUS							HAL_GPIO_ReadPin(KEY2_PORT, KEY2_PIN)

extern void KEY_GPIO_ReInit(void);
extern uint8_t KEY1_Value(void);
extern uint8_t KEY2_Value(void);

#endif /* __DRIVER_KEY_H */

```

### driver_key.c

```
#include <input_system.h>
#include <kal_time.h>
#include <gpio_key.h>
#include <input_buffer.h>
#include "driver_key.h"

static volatile uint8_t key1_val = KEY_RELEASED;
static volatile uint8_t key2_val = KEY_RELEASED;

void KEY_GPIO_ReInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	KEY1_GPIO_CLK_EN();
	KEY2_GPIO_CLK_EN();

	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	
	GPIO_InitStruct.Pin = KEY1_PIN;
	HAL_GPIO_Init(KEY1_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = KEY2_PIN;
	HAL_GPIO_Init(KEY1_PORT, &GPIO_InitStruct);
	
	
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 2);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(KEY1_PIN);
	HAL_GPIO_EXTI_IRQHandler(KEY2_PIN);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	InputEvent event;

	/* 消除抖动 */
	
	if(KEY1_PIN == GPIO_Pin)
	{
		/* 构造InputEvent */
		event.time  = KAL_GetTime();  /* kal */
		event.eType = INPUT_EVENT_TYPE_KEY;
		event.iKey  = K1_CODE;

		/* 读取GPIO电平, GPIO为0表示按下, 此时压力是1,松开后压力是0 */
		event.iPressure = !K1_STATUS;  

		/* 放入环形缓冲区 */
		PutInputEvent(&event);
	}
	else if(KEY2_PIN == GPIO_Pin)
	{
		/* 构造InputEvent */
		event.time	= KAL_GetTime();  /* kal */
		event.eType = INPUT_EVENT_TYPE_KEY;
		event.iKey	= K2_CODE;

		/* 读取GPIO电平, GPIO为0表示按下, 此时压力是1,松开后压力是0 */
		event.iPressure = !K2_STATUS;

		/* 放入环形缓冲区 */
		PutInputEvent(&event);
	}
}

uint8_t KEY1_Value(void)
{
	return key1_val;
}

uint8_t KEY2_Value(void)
{
	return key2_val;
}

```

