#include "contrlEquipments.h"				//自定义设备类的文件

int lockInit();			//初始化继电器函数声明
int lockOpen();			//“打开灯”函数声明
int lockClose();			//“关闭灯”函数声明

struct Equipment lock = {			//定义客厅灯（对象）
	.equipName = "lock",				//名字
	.pinNum = 5,						//树莓派 1号(wPi)引脚
	.Init = lockInit,				//指定初始化函数
	.open = lockOpen,				//指定“打开灯”函数
	.close = lockClose,				//指定“关闭灯”函数
};


int lockInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);						//配置引脚为输出模式
	digitalWrite(pinNum,HIGH);					//引脚置高电平，断开继电器
}

int lockOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);					//引脚置低电平，闭合继电器
}

int lockClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);					//引脚置高电平，断开继电器
}

struct Equipment *addlockToEquipmentLink(struct Equipment *phead)		//客厅灯（对象）加入设备链表函数
{
	if(phead == NULL){
		return &lock;
	}else{
		lock.next = phead;
		phead = &lock;
		return phead;
	}
}
