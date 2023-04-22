#include "contrlEquipments.h"				//自定义设备类的文件

int secondfloorLightInit();			//初始化继电器函数声明
int secondfloorLightOpen();			//“打开灯”函数声明
int secondfloorLightClose();		//“关闭灯”函数声明

//struct Equipment *addSecondfloorLightToLink(struct Equipment *phead);
////二楼灯（对象）加入设备链表函数声明

struct Equipment secondfloorLight = {			//定义二楼灯（对象）
	.equipName = "secondfloorLight",			//名字
	.pinNum = 4,								//树莓派 4号(wPi)引脚
	.Init = secondfloorLightInit,				//指定初始化函数
	.open = secondfloorLightOpen,				//指定“打开灯”函数
	.close = secondfloorLightClose,				//指定“关闭灯”函数
};


int secondfloorLightInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);						//配置引脚为输出模式
	digitalWrite(pinNum,HIGH);					//引脚置高电平，断开继电器
}

int secondfloorLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);					//引脚置低电平，闭合继电器
}

int secondfloorLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);					//引脚置高电平，断开继电器
}

struct Equipment *addSecondfloorLightToEquipmentLink(struct Equipment *phead)		//二楼灯（对象）加入设备链表函数
{
	if(phead == NULL){
		return &secondfloorLight;
	}else{
		secondfloorLight.next = phead;
		phead = &secondfloorLight;
		return phead;
	}
}

