#include "contrlEquipments.h"							//自定义设备类的文件

int airDetectionInit(int pinNum);				//初始化“煤气传感器”函数声明
int readAirDetectionStatus(int pinNum);		//读取“煤气传感器”状态函数声明


struct Equipment airDetection = {				//定义火焰传感器（对象）
	.equipName = "airDetection",				//名字
	.pinNum = 27,								//树莓派 27号(wPi)引脚
	.Init = airDetectionInit,					//指定初始化函数
	.readStatus = readAirDetectionStatus,		//指定读取“火焰传感器”状态函数
};

int airDetectionInit(int pinNum)
{
	pinMode(pinNum,INPUT);						//配置引脚为输入模式
	digitalWrite(pinNum,HIGH);					//引脚置高电平，状态为1
}

int readAirDetectionStatus(int pinNum)
{
	return digitalRead(pinNum);					//读取引脚电平，并返回，高电平返回 1，低电平返回 0(煤气泄漏)
}

struct Equipment *addAirDetectionToEquipmentLink(struct Equipment *phead)		//煤气传感器（对象）加入设备链表函数
{
	if(phead == NULL){
		return &airDetection;
	}else{
		airDetection.next = phead;
		phead = &airDetection;
		return phead;
	}
}

