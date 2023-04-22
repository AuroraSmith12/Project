#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


struct Command
{
	char commandName[128];						//“控制方式”名
	char deviceFilesName[128];					//存放初始化所需文件的路径
	char command[32];							//存放指令
	int fd;										//存放文件描述符（串口/网络）
	int (*Init)(struct Command *file);			//“初始化”函数指针
	int s_fd;									//存放服务器套接字描述符
	char ipAdress[32];							//存放 IP地址
	char port[12];								//存放端口号
	int (*getCommand)(struct Command *cmd);		//“获取指令”函数指针

	struct Command *next;
};

struct Command *addVoiceControlToCommandLink(struct Command *phead);		//“语音控制”加入指令控制工厂链表函数声明
struct Command *addSocketControlToCommandLink(struct Command *phead);		//“网络控制”加入指令控制工厂链表函数声明
