#include "contrlEquipments.h"				//自定义设备类的文件

int livingroomLightInit();			//初始化继电器函数声明
int livingroomLightOpen();			//“打开灯”函数声明
int livingroomLightClose();			//“关闭灯”函数声明
//struct Equipment *addLivingroomLightToLink(struct Equipment *phead);
//客厅灯（对象）加入设备链表函数声明
/*
struct Equipment						//设备类
{
	char equipName[128];				//设备名
	int pinNum;							//引脚号
	int (*Init)(int pinNum);			//“初始化设备”函数指针
	int (*open)(int pinNum);			//“打开设备”函数指针
	int (*close)(int pinNum);			//“关闭设备”函数指针

	int (*readStatus)(int pinNum);		//“读取设备状态”函数指针  为火灾报警器准备
	int (*changeStatus)(int status);	//“改变设备状态”函数指针

	struct Equipment *next;
};
*/

struct Equipment livingroomLight = {			//定义客厅灯（对象）
	.equipName = "livingroomLight",				//名字
	.pinNum = 1,						//树莓派 1号(wPi)引脚
	.Init = livingroomLightInit,				//指定初始化函数
	.open = livingroomLightOpen,				//指定“打开灯”函数
	.close = livingroomLightClose,				//指定“关闭灯”函数
};


int livingroomLightInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);						//配置引脚为输出模式
	digitalWrite(pinNum,HIGH);					//引脚置高电平，断开继电器
}

int livingroomLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);					//引脚置低电平，闭合继电器
}

int livingroomLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);					//引脚置高电平，断开继电器
}

struct Equipment *addLivingroomLightToEquipmentLink(struct Equipment *phead)		//客厅灯（对象）加入设备链表函数
{
	if(phead == NULL){
		return &livingroomLight;
	}else{
		livingroomLight.next = phead;
		phead = &livingroomLight;
		return phead;
	}
}
