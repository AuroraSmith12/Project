#include <stdio.h>
#include <string.h>
#include "contrlEquipments.h"
#include "inputCommand.h"
#include <pthread.h>
#include <unistd.h>

struct Equipment *findEquipByName(char *name,struct Equipment *phead);		//一些函数声明
struct Command *findCommandByName(char *name,struct Command *phead);
void *voiceControlThread(void *data);
void *socketControlThread(void *data);
void *socketReadThread(void *data);
void *fireAlarmThread(void *data);
void *airAlarmThread(void *data);

struct Equipment *equiphead = NULL;			//设备工厂链表头节点
struct Command *cmdhead = NULL;				//指令控制工厂链表节点头
struct Command *socketHandler = NULL;		//“网络控制线程”执行的函数使用到的全局变量


int main()
{
	if(wiringPiSetup() == -1){					//使用wiringPi库需要初始化
		printf("wiringPiSetup failed!\n");
		return -1; 
	}

	pthread_t voiceControl_thread;
	pthread_t socketControl_thread;
	pthread_t fireAlarm_thread;
	pthread_t airAlarm_thread;

	//1、设备工厂初始化
	equiphead = addBathroomLightToEquipmentLink(equiphead);			//各设备加入设备工厂
	equiphead = addSecondfloorLightToEquipmentLink(equiphead);	
	equiphead = addLivingroomLightToEquipmentLink(equiphead);
	equiphead = addRestaurantLightToEquipmentLink(equiphead);
	equiphead = addFireDetectionToEquipmentLink(equiphead);
	equiphead = addBuzzerToEquipmentLink(equiphead);
	equiphead = addlockToEquipmentLink(equiphead);
	equiphead = addAirDetectionToEquipmentLink(equiphead);		//煤气传感器（对象）加入设备链表函数

	struct Equipment *tmpequiphead = equiphead;
	while(tmpequiphead != NULL){						//设备工厂所有设备初始化
		tmpequiphead->Init(tmpequiphead->pinNum);
		tmpequiphead = tmpequiphead->next;
	}


	//2、指令工厂初始化
	cmdhead = addVoiceControlToCommandLink(cmdhead);				//各指令控制加入指令控制工厂
	cmdhead = addSocketControlToCommandLink(cmdhead);



	//3、线程池建立
	//3.1 语音线程   
	//int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rtn)(void *), void *restrict arg);  
	pthread_create(&voiceControl_thread,NULL,voiceControlThread,NULL);		//创建线程：语音控制
	//3.2 网络线程 		
	pthread_create(&socketControl_thread,NULL,socketControlThread,NULL);	//创建线程：网络控制
	//3.3 火灾线程 	
	pthread_create(&fireAlarm_thread,NULL,fireAlarmThread,NULL);			//创建线程：火灾报警系统
	//3.4 摄像头线程 
	//3.5煤气线程
	pthread_create(&airAlarm_thread,NULL,airAlarmThread,NULL);			//创建线程：火灾报警系统
	
	pthread_join(voiceControl_thread, NULL);		//主函数等待线程退出
	pthread_join(socketControl_thread, NULL);		//主函数等待线程退出
	pthread_join(fireAlarm_thread, NULL);			//主函数等待线程退出
	pthread_join(airAlarm_thread, NULL);			//主函数等待线程退出
	return 0;
}



void *voiceControlThread(void *data)			//“语音控制线程”执行的函数
{
	int nread;
	char *temName = NULL;
	struct Command *voiceHandler = NULL;
	struct Equipment *linkHandler;


	voiceHandler = findCommandByName("voiceControl",cmdhead);		//寻找“语音控制”所在节点，返回给voiceHandler
	if(voiceHandler == NULL){
		printf("find voiceHandler error\n");
		pthread_exit(NULL);
	}
	if(voiceHandler->Init(voiceHandler) < 0){				//“语音控制”功能初始化
		printf("voiceControl init error\n");
		pthread_exit(NULL);
	}


	while(1){
		nread = voiceHandler->getCommand(voiceHandler);			//获取指令
		if(nread == 0){											//没有获取到指令
			printf("No voiceCommand received\n");
		}else{													//获取到指令
			printf("Get voice command:%s\n",voiceHandler->command);

			//以下为根据不用指令执行相应操作

			//语音模块串口传出来的后面带\r\n，不加对比不出来
			if(strcmp("ycdo\r\n",voiceHandler->command) == 0){
				linkHandler = findEquipByName("bathroomLight",equiphead);//改为泳池灯	
				linkHandler->open(linkHandler->pinNum);
				//printf("已打开浴室灯\n");
				printf("已打开泳池灯\n");
			}

			if(strcmp("ycdc\r\n",voiceHandler->command) == 0){
				linkHandler = findEquipByName("bathroomLight",equiphead);
				linkHandler->close(linkHandler->pinNum);
				//printf("已关闭浴室灯\n");
				printf("已关闭泳池灯\n");
			}

			if(strcmp("eldo\r\n",voiceHandler->command) == 0){
				linkHandler = findEquipByName("secondfloorLight",equiphead);
				linkHandler->open(linkHandler->pinNum);
			}

			if(strcmp("eldc\r\n",voiceHandler->command) == 0){
				linkHandler = findEquipByName("secondfloorLight",equiphead);
				linkHandler->close(linkHandler->pinNum);
			}

			if(strcmp("ktdo\r\n",voiceHandler->command) == 0){
				linkHandler = findEquipByName("livingroomLight",equiphead);
				linkHandler->open(linkHandler->pinNum);
			}

			if(strcmp("ktdc\r\n",voiceHandler->command) == 0){
				linkHandler = findEquipByName("livingroomLight",equiphead);
				linkHandler->close(linkHandler->pinNum);
			}

			if(strcmp("wsdo\r\n",voiceHandler->command) == 0){
				linkHandler = findEquipByName("restaurantLight",equiphead);//改为卧室灯
				linkHandler->open(linkHandler->pinNum);
			}

			if(strcmp("wsdc\r\n",voiceHandler->command) == 0){
				linkHandler = findEquipByName("restaurantLight",equiphead);
				linkHandler->close(linkHandler->pinNum);
			}

			if(strcmp("allo\r\n",voiceHandler->command) == 0){
				linkHandler = findEquipByName("bathroomLight",equiphead);//灯全部打开
				linkHandler->open(linkHandler->pinNum);

				linkHandler = findEquipByName("secondfloorLight",equiphead);
				linkHandler->open(linkHandler->pinNum);

				linkHandler = findEquipByName("livingroomLight",equiphead);
				linkHandler->open(linkHandler->pinNum);

				linkHandler = findEquipByName("restaurantLight",equiphead);
				linkHandler->open(linkHandler->pinNum);
			}

			if(strcmp("allc\r\n",voiceHandler->command) == 0){
				linkHandler = findEquipByName("bathroomLight",equiphead);//灯全部关闭
				linkHandler->close(linkHandler->pinNum);

				linkHandler = findEquipByName("secondfloorLight",equiphead);
				linkHandler->close(linkHandler->pinNum);

				linkHandler = findEquipByName("livingroomLight",equiphead);
				linkHandler->close(linkHandler->pinNum);

				linkHandler = findEquipByName("restaurantLight",equiphead);
				linkHandler->close(linkHandler->pinNum);
			}
			if(strcmp("dooro\r\n",voiceHandler->command) == 0)
			{
				system("./face_rec_final");
			}

		}
	}
}


void *socketControlThread(void *data)				//“网络控制线程”执行的函数
{
	int c_fd;
	struct sockaddr_in c_addr;
	memset(&c_addr,0,sizeof(struct sockaddr_in));
	socklen_t clen = sizeof(struct sockaddr_in);
	pthread_t socketRead_thread; //线程里面套线程，网络连接后信息通信


	socketHandler = findCommandByName("socketControl",cmdhead);		//寻找“网络控制”所在节点，返回给socketHandler
	if(socketHandler == NULL){
		printf("find socketHandler error\n");
		pthread_exit(NULL);
	}
	if(socketHandler->Init(socketHandler) < 0){				//“网络控制”功能初始化
		printf("socketControl init error\n");
		pthread_exit(NULL);
	}


	while(1){
		c_fd = accept(socketHandler->s_fd,(struct sockaddr*)&c_addr,&clen);		//接收连接请求，阻塞至有客户端完成三次握手
		socketHandler->fd = c_fd;					//将套接字描述符返回给“网络控制”链表节点

		pthread_create(&socketRead_thread,NULL,socketReadThread,NULL);			//创建新线程：用于读取TCP端口指令
//只要有连接，就创建线程去对接。线程共用内存资源，同一时刻，所有设备只有一种状态。也可PV操作
//所有线程 只操控一个结构体 再新来一个线程(新手机客户端接入) 前一个客户端失效 因为c_fd被改了。fork()可实现多个客户端同时控制
//不过好像寄存器和内存不是完全同步的 可能缓存没改？还可以多个客户端同时控制？
//如果直接把socketReadThread()拿过来循环的话，则同时刻不能接受新的客户端接入了，因为循环卡在了socketReadThread()函数里面了
	}
}


void *socketReadThread(void *data)				//“读取tcp端口指令线程”执行的函数
{

	int nread;
	struct Equipment *linkHandler;
	//这里没加while循环，客户端只能发送一次
	while(1)
	{
	printf("socketConnect...");
		memset(socketHandler->command,'\0',sizeof(socketHandler->command));		//将指令存放的空间置空
	
		nread = read(socketHandler->fd,socketHandler->command,sizeof(socketHandler->command));		//读取指令
	
		if(nread == 0){
			printf("No socketCommand received\n");			//没有读取到指令
		}else{
			printf("Get socketCommand:%s\n",socketHandler->command);		//读取到指令

			//以下为根据不用指令执行相应操作

			if(strcmp("ycdo",socketHandler->command) == 0){
				linkHandler = findEquipByName("bathroomLight",equiphead);//改为泳池灯	
				linkHandler->open(linkHandler->pinNum);
				//printf("已打开浴室灯\n");
				printf("已打开泳池灯\n");
			}

			if(strcmp("ycdc",socketHandler->command) == 0){
				linkHandler = findEquipByName("bathroomLight",equiphead);
				linkHandler->close(linkHandler->pinNum);
				//printf("已关闭浴室灯\n");
				printf("已关闭泳池灯\n");
			}

			if(strcmp("eldo",socketHandler->command) == 0){
				linkHandler = findEquipByName("secondfloorLight",equiphead);
				linkHandler->open(linkHandler->pinNum);
			}

			if(strcmp("eldc",socketHandler->command) == 0){
				linkHandler = findEquipByName("secondfloorLight",equiphead);
				linkHandler->close(linkHandler->pinNum);
			}

			if(strcmp("ktdo",socketHandler->command) == 0){
				linkHandler = findEquipByName("livingroomLight",equiphead);
				linkHandler->open(linkHandler->pinNum);
			}

			if(strcmp("ktdc",socketHandler->command) == 0){
				linkHandler = findEquipByName("livingroomLight",equiphead);
				linkHandler->close(linkHandler->pinNum);
			}

			if(strcmp("wsdo",socketHandler->command) == 0){
				linkHandler = findEquipByName("restaurantLight",equiphead);//改为卧室灯
				linkHandler->open(linkHandler->pinNum);
			}

			if(strcmp("wsdc",socketHandler->command) == 0){
				linkHandler = findEquipByName("restaurantLight",equiphead);
				linkHandler->close(linkHandler->pinNum);
			}

			if(strcmp("allo",socketHandler->command) == 0){
				linkHandler = findEquipByName("bathroomLight",equiphead);//灯全部打开
				linkHandler->open(linkHandler->pinNum);

				linkHandler = findEquipByName("secondfloorLight",equiphead);
				linkHandler->open(linkHandler->pinNum);

				linkHandler = findEquipByName("livingroomLight",equiphead);
				linkHandler->open(linkHandler->pinNum);

				linkHandler = findEquipByName("restaurantLight",equiphead);
				linkHandler->open(linkHandler->pinNum);
			}

			if(strcmp("allc",socketHandler->command) == 0){
				linkHandler = findEquipByName("bathroomLight",equiphead);//灯全部关闭
				linkHandler->close(linkHandler->pinNum);

				linkHandler = findEquipByName("secondfloorLight",equiphead);
				linkHandler->close(linkHandler->pinNum);

				linkHandler = findEquipByName("livingroomLight",equiphead);
				linkHandler->close(linkHandler->pinNum);

				linkHandler = findEquipByName("restaurantLight",equiphead);
				linkHandler->close(linkHandler->pinNum);
			}
			if(strcmp("dooro",socketHandler->command) == 0)
			{
				linkHandler = findEquipByName("lock",equiphead);
				linkHandler->open(linkHandler->pinNum);
				delay(2000);
				linkHandler->close(linkHandler->pinNum);
			
			}
			if(strcmp("camera",socketHandler->command) == 0)
			{
				system("./start.sh");

			}

		}
	}
}


void *fireAlarmThread(void *data)//有火-返回高电平				//“火灾报警器线程”执行的函数
{
	int status;
	struct Equipment *firetmp = NULL;
	struct Equipment *buztmp = NULL;

	firetmp = findEquipByName("fireDetection",equiphead);		//寻找“火焰传感器”链表节点，返回给firetmp
	buztmp = findEquipByName("buzzer",equiphead);				//寻找“蜂鸣器”链表节点，返回给buztmp

	while(1){
		status = firetmp->readStatus(firetmp->pinNum);			//读取“火焰传感器”状态

		if(status == 1){						//检测到火焰或强光源
			buztmp->open(buztmp->pinNum);		//打开蜂鸣器
			perror("fire-why");
			delay(1000);						//延时1000毫秒=1秒
		}

		if(status == 0){						//未检测到火焰、强光源或解除警报
			buztmp->close(buztmp->pinNum);		//关闭蜂鸣器
		}
	}
}

void *airAlarmThread(void *data)//煤气泄漏-返回低电平				//“煤气泄漏报警器线程”执行的函数
{
	int status;
	struct Equipment *airtmp = NULL;
	struct Equipment *buztmp = NULL;

	airtmp = findEquipByName("airDetection",equiphead);		//寻找“煤气传感器”链表节点，返回给airtmp
	buztmp = findEquipByName("buzzer",equiphead);				//寻找“蜂鸣器”链表节点，返回给buztmp

	while(1){
		status = airtmp->readStatus(airtmp->pinNum);			//读取“煤气传感器”状态
/*	//玄学，加了煤气检测代码，要煤气检测，和火灾同时有，蜂鸣器才能响
		if(status == 0){						//检测到煤气
			buztmp->open(buztmp->pinNum);		//打开蜂鸣器
			perror("air-why");
			delay(1500);						//延时1000毫秒=1秒
		}

		if(status == 1){						//未检测到煤气解除警报
			buztmp->close(buztmp->pinNum);		//关闭蜂鸣器
		}
*/
		}
}

struct Equipment *findEquipByName(char *name,struct Equipment *phead)		//根据名字寻找设备工厂链表链节函数，并返回链节
{
	struct Equipment *tmp = phead;

	if(phead == NULL){
		return NULL;
	}

	while(tmp != NULL){
		if(strcmp(name,tmp->equipName) == 0){
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}


struct Command *findCommandByName(char *name,struct Command *phead)			//根据名字寻找指令控制工厂链表链节函数，并返回链节
{
	struct Command *tmp = phead;

	if(phead == NULL){
		return NULL;
	}

	while(tmp != NULL){
		if(strcmp(name,tmp->commandName) == 0){
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

