# 1.ESP32获取时间

### 参考博客：[Arduino ESP32 最简单直接获取网络时间方法_esp32获取网络时间_perseverance52的博客-CSDN博客](https://blog.csdn.net/weixin_42880082/article/details/120947163)

### 代码：

```c
/**
  ESP32 最简单直接获取网络时间方法
*/

#include <WiFi.h>

#define NTP1  "ntp1.aliyun.com"
#define NTP2  "ntp2.aliyun.com"
#define NTP3  "ntp3.aliyun.com"

//填写WIFI入网信息
const char* ssid     = "MERCURY_D268G";     // WIFI账户
const char* password = "pba5ayzk"; // WIFI密码

void setClock() {
  struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {//如果获取失败，就开启联网模式，获取时间
        Serial.println("Failed to obtain time");
     //    WiFi.disconnect(false);
        WiFi.mode(WIFI_STA);//开启网络  
       WiFi.begin(ssid, password);
         while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
     configTime(8 * 3600, 0, NTP1, NTP2,NTP3);
        return;
    }
    Serial.println(&timeinfo, "%F %T %A"); // 格式化输出:2021-10-24 23:00:44 Sunday
    Serial.print(asctime(&timeinfo));//默认打印格式：Mon Oct 25 11:13:29 2021
  //   WiFi.disconnect(true);//断开网络连接，关闭网络
}

void setup()
{
    Serial.begin(115200);
    Serial.println();
 //设置ESP32工作模式为无线终端模式
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected!");
 configTime(8 * 3600, 0, NTP1, NTP2,NTP3);
      setClock();
    // 从网络时间服务器上获取并设置时间
    // 获取成功后芯片会使用RTC时钟保持时间的更新
   
//    WiFi.disconnect(true);//断开wifi网络
//    WiFi.mode(WIFI_OFF);//关闭网络
    Serial.println("WiFi disconnected!");
}

void loop()
{
  
  Serial.println("Waiting 10s before the next round...");
  delay(10000);
  setClock();
}


```

![18](D:\Desktop\学习ESP32笔记\pic\18.png)