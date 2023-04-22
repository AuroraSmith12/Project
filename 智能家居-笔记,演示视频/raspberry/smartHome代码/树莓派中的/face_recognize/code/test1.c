#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
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

        char img1[12];
        char img2[12];
        char *key = "MPWeajiYjAtrYDfZweE8vk";
        char *secret = "9e300b424e7e4a20a7dabd3799410c56";
        int typeId = 21;
        char *formate = "xml";

        postString = (char*)malloc(strlen(key)+strlen(secret)+2048);


        //字符串拼接
        sprintf(postString,"&img1=%s&img2=%s&key=%s&secret=%s&typeId=%d&formate=%s",
                                  "",     "",    key,    secret,   typeId,    formate);

        curl = curl_easy_init();
        if (curl)
        {
                curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt"); // 指定cookie文件
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postString);    // 指定post内容
                curl_easy_setopt(curl, CURLOPT_URL, "https://netocr.com/api/faceliu.do");   // 指定url
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_func); //通过回调函数存储数据
                res = curl_easy_perform(curl);

                printf("OK:%d\n",res);


                curl_easy_cleanup(curl);
        }
        return true;
}
int main(void)
{
        postUrl();
}


