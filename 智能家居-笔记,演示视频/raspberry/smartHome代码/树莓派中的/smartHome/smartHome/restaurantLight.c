#include "contrlEquipments.h"				//自定义设备类的文件

int restaurantLightInit();			//初始化继电器函数声明
int restaurantLightOpen();			//“打开灯”函数声明
int restaurantLightClose();			//“关闭灯”函数声明
struct Equipment *addRestaurantLightToLink(struct Equipment *phead);
//餐厅灯（对象）加入设备链表函数声明


struct Equipment restaurantLight = {			//定义餐厅灯（对象）
	.equipName = "restaurantLight",				//名字
	.pinNum = 3,								//树莓派 3号(wPi)引脚
	.Init = restaurantLightInit,				//指定初始化函数
	.open = restaurantLightOpen,				//指定“打开灯”函数
	.close = restaurantLightClose,				//指定“关闭灯”函数
};


int restaurantLightInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);						//配置引脚为输出模式
	digitalWrite(pinNum,HIGH);					//引脚置高电平，断开继电器
}

int restaurantLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);					//引脚置低电平，闭合继电器
}

int restaurantLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);					//引脚置高电平，断开继电器
}

struct Equipment *addRestaurantLightToEquipmentLink(struct Equipment *phead)		//餐厅灯（对象）加入设备链表函数
{
	if(phead == NULL){
		return &restaurantLight;
	}else{
		restaurantLight.next = phead;
		phead = &restaurantLight;
		return phead;
	}
}

