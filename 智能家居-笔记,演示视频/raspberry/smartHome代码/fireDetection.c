#include "contrlEquipments.h"							//自定义设备类的文件

int fireDetectionInit(int pinNum);				//初始化“火焰传感器”函数声明
int readFireDetectionStatus(int pinNum);		//读取“火焰传感器”状态函数声明


struct Equipment fireDetection = {				//定义火焰传感器（对象）
	.equipName = "fireDetection",				//名字
	.pinNum = 21,								//树莓派 21号(wPi)引脚
	.Init = fireDetectionInit,					//指定初始化函数
	.readStatus = readFireDetectionStatus,		//指定读取“火焰传感器”状态函数
};

int fireDetectionInit(int pinNum)
{
	pinMode(pinNum,INPUT);						//配置引脚为输入模式
	digitalWrite(pinNum,LOW);					//引脚置高电平，状态为1
}

int readFireDetectionStatus(int pinNum)
{
	return digitalRead(pinNum);					//读取引脚电平，并返回，高电平返回 1，低电平返回 0(有火)
}

struct Equipment *addFireDetectionToEquipmentLink(struct Equipment *phead)		//火焰传感器（对象）加入设备链表函数
{
	if(phead == NULL){
		return &fireDetection;
	}else{
		fireDetection.next = phead;
		phead = &fireDetection;
		return phead;
	}
}

