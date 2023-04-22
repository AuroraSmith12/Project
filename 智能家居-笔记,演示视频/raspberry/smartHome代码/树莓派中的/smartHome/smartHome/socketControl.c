#include "inputCommand.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


int socketControlInit(struct Command *file);						//“网络控制”功能初始化函数声明
struct Command *addSocketControlToLink(struct Command *phead);		//“网络控制”（对象）加入指令链表函数声明


struct Command socketControl = {				//定义“网络控制”对象
	.commandName = "socketControl",				//名字
	.command = {'\0'},							//初始化储存“指令”的空间
	.Init = socketControlInit,					//指定“网络控制”功能初始化函数
	.ipAdress = "192.168.208.227",				    //树莓派 IP地址
	.port = "8880",								//打开的端口号
};

int socketControlInit(struct Command *file)
{
	int s_fd;											//套接字描述符
	struct sockaddr_in s_addr;
	memset(&s_addr,0,sizeof(struct sockaddr_in));

	s_fd = socket(AF_INET,SOCK_STREAM,0);				//创建套接字
    if(s_fd == -1){										//若创建套接字失败
            perror("socketControl error");
            exit(-1);
    }

	s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(atoi(file->port));
    inet_aton(file->ipAdress,&s_addr.sin_addr);
	if(bind(s_fd,(struct sockaddr*)&s_addr,sizeof(struct sockaddr_in)) == -1){		//套接字与端口号绑定
    	perror("bind error");
    	exit(-1);
    }

	if(listen(s_fd,10) == -1){							//打开监听
    	perror("listen error");
    	exit(-1);
    }

	file->s_fd = s_fd;									//发送套接字描述符
}

struct Command *addSocketControlToCommandLink(struct Command *phead)		//“网络控制”（对象）加入指令链表函数
{
	if(phead == NULL){
		return &socketControl;
	}else{
		socketControl.next = phead;
		phead = &socketControl;
		return phead;
	}
}

