#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


#define true 1
#define false 0
typedef unsigned int bool;


size_t read_func( void *ptr, size_t size, size_t nmemb, void *stream)
{
        char buf[1024] = {0};
        strncpy(buf, ptr, 1024);
        printf("======================get data======================\n");
        printf("%s\n",buf);
}
bool postUrl()
{
        CURL *curl;
        CURLcode res;

        char *postString;

        char *img1;
        char *img2;
        char *key = "MPWeajiYjAtrYDfZweE8vk";
        char *secret = "9e300b424e7e4a20a7dabd3799410c56";
        int typeID = 21;
        char *formate = "xml";

        system("base64 pyy1.jpg > tmpFile1");
        system("base64 pyy2.jpg > tmpFile2");

        int fd1 = open("./tmpFile1",O_RDWR);
        int fd2 = open("./tmpFile2",O_RDWR);

        int fd1_len = lseek(fd1,0,SEEK_END);
        lseek(fd1,0,SEEK_SET);

        int fd2_len = lseek(fd2,0,SEEK_END);
        lseek(fd2,0,SEEK_SET);

        img1 = (char*)malloc(fd1_len+20);
        img2 = (char*)malloc(fd2_len+20);

        memset(img1,'\0',fd1_len+20);
        memset(img2,'\0',fd2_len+20);

        read(fd1,img1,fd1_len);
        read(fd2,img2,fd2_len);
        postString = (char*)malloc(strlen(key)+strlen(secret)+fd1_len+fd2_len+1024);

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
        close(fd1);
        close(fd2);
        return true;
}
int main(void)
{
        postUrl();
}


