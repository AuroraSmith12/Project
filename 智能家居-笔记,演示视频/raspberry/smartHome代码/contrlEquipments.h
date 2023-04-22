#include <wiringPi.h>					//wiringPi库
#include <stdio.h>
#include <stdlib.h>
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

struct Equipment *addBathroomLightToEquipmentLink(struct Equipment *phead);		//“浴室灯”加入设备链表函数声明
struct Equipment *addSecondfloorLightToEquipmentLink(struct Equipment *phead);		//“二楼灯”加入设备链表函数声明
struct Equipment *addLivingroomLightToEquipmentLink(struct Equipment *phead);		//“客厅灯”加入设备链表函数声明
struct Equipment *addRestaurantLightToEquipmentLink(struct Equipment *phead);		//“餐厅灯”加入设备链表函数声明
struct Equipment *addFireDetectionToEquipmentLink(struct Equipment *phead);			//“火焰传感器”加入设备链表函数声明
struct Equipment *addBuzzerToEquipmentLink(struct Equipment *phead);				//“蜂鸣器”加入设备链表函数声明
struct Equipment *addlockToEquipmentLink(struct Equipment *phead);
struct Equipment *addAirDetectionToEquipmentLink(struct Equipment *phead);		//煤气传感器（对象）加入设备链表函数
