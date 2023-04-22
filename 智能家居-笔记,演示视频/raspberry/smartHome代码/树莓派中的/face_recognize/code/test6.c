#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<wiringPi.h>

#define true 1
#define false 0
typedef unsigned int bool;


int gpio_init(void)
{
	int err_num = wiringPiSetup();
	pinMode(1, OUTPUT);
	digitalWrite(1,HIGH);
	return err_num;
}

void lock_open(void)
{
	digitalWrite(1,LOW);
	delay(1000);
	digitalWrite(1,HIGH);
}

size_t read_func( void *ptr, size_t size, size_t nmemb, void *stream)
{
        char buf[1024] = {0};
        strncpy(buf, ptr, 1024);
        printf("======================get data======================\n");
        printf("%s\n",buf);

        printf("=====================result=======================\n");
        if(strstr(buf,"是") != NULL)
        {
		lock_open();
                printf("the same person\n");
        }
        else
        {
                printf("different person\n");
        }

}
char* getPicBase64FromFile(char *filePath)
{

        char *bufPic;
        char cmd[128]={'\0'};

        sprintf(cmd,"base64 %s >tmpFile",filePath);

        system(cmd);

        int fd = open("./tmpFile",O_RDWR);
        int fd_len = lseek(fd,0,SEEK_END);
        lseek(fd,0,SEEK_SET);

        bufPic = (char*)malloc(fd_len+2);

        memset(bufPic,'\0',fd_len+2);

        read(fd,bufPic,fd_len);

        close(fd);

        system("rm -rf tmpFile");

        return bufPic;

}

bool postUrl()
{
        CURL *curl;
        CURLcode res;

        char *postString;

        char *img1;
        char *img2;
        char *key = "7qUgFcjemNwL5m5dCFH7gk";
        char *secret = "c8a238f46dae4ea3a98eb8baaa2ab2d0";
        int typeID = 21;
        char *formate = "xml";

	//拍摄图片
	system("raspistill -o after.jpg -t 1000");

        //图片转字符流

        img1 = getPicBase64FromFile("./before.jpg");

        img2 = getPicBase64FromFile("./after.jpg");
	
	//删除拍摄的图片
	system("rm -rf after.jpg");

        postString = (char*)malloc(strlen(key)+strlen(secret)+strlen(img1)+strlen(img2)+1024);
        memset(postString,'\0',strlen(postString));

        //字符串拼接
        sprintf(postString,"&img1=%s&img2=%s&key=%s&secret=%s&typeId=%d&formate=%s",
                        img1,     img2,    key,    secret,   typeID,    formate);

        curl = curl_easy_init();
        if (curl)
        {
                curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt"); // 指定cookie文件
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postString);    // 指定post内容
                curl_easy_setopt(curl, CURLOPT_URL,"https://netocr.com/api/faceliu.do");   // 指定url
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_func); //通过回调函数存储数据
                res = curl_easy_perform(curl);

                printf("OK:%d\n",res);


                curl_easy_cleanup(curl);
        }
        free(img1);
        free(img2);
        free(postString);
        return true;
}
int main(void)
{
	int err_num = gpio_init();
	if(err_num == -1)
	{
		return -1;
	}
	while(1)
	{
        postUrl();

	}
}


