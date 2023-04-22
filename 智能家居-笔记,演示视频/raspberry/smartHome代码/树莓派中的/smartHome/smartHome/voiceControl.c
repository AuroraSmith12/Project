#include "inputCommand.h"			//自定义类文件
#include <unistd.h>

int voiceControlInit(struct Command *file);						//“语音控制”功能初始化函数声明

int voiceControlGetCommand(struct Command *cmd);					//“获取指令”函数初始化
struct Command *addVoiceControlToCommandLink(struct Command *phead);		//“语音控制”（对象）加入指令链表函数声明

struct Command voiceControl = {						//定义“语音控制”对象
	.commandName = "voiceControl",					//名字
	.deviceFilesName = "/dev/ttyAMA0",				//树莓派串口文件所在地址
	.command = {'\0'},								//初始化储存“指令”的空间
	.Init = voiceControlInit,						//指定“语音控制”功能初始化函数
	.getCommand = voiceControlGetCommand,			//指定“获取指令”函数
};

int voiceControlInit(struct Command *file)  //  C语言要传参，java可直接访问
{
	int fd;
	if((fd = serialOpen(file->deviceFilesName,115200)) == -1){		//打开树莓派串口，波特率指定为115200
		exit(-1);
	}
	file->fd = fd;	//(传过来的是地址)打开串口文件成功，返回“文件描述符”到“语音控制”链节中
}

int voiceControlGetCommand(struct Command *cmd)
{
	int nread = 0;
	nread = read(cmd->fd,cmd->command,sizeof(cmd->command));	//读取串口
	if(nread == 0){
		printf("usart for voice over time\n");
    }else{
	return nread;            //返回读取到数据的字节数,实际读取的指令放到了command里
	}												
}

struct Command *addVoiceControlToCommandLink(struct Command *phead)	//“语音控制”（对象）加入指令方式链表函数
{
	if(phead == NULL){
		return &voiceControl;
	}else{
		voiceControl.next = phead;
		phead = &voiceControl;
		return phead;
	}
}
