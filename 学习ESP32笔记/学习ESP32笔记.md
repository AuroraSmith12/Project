# 学习ESP32笔记

## 1.platform IO插件的下载（提前安装好python，不然在中间的一部分会一直报错）

### VS Code下载platform IO时，开加速器（VPN），并且关闭防火墙

#### 这一步比较慢，大概等十来分钟。

![1](D:\Desktop\学习ESP32笔记\pic\1.png)



#### 下面这个就是下载成功。

![2](D:\Desktop\学习ESP32笔记\pic\2.png)





## 2.创建ESP32Demo

![3](D:\Desktop\学习ESP32笔记\pic\3.png)

### 关闭防火墙，用手机热点给电脑连接，打开VPN（在早上创建成功的，早上是玄学），或者也可以不用VPN？

## 3.代码的编译和下载

### 编译

![4](D:\Desktop\学习ESP32笔记\pic\4.png)

### 下载

![5](D:\Desktop\学习ESP32笔记\pic\5.png)



### 那个端口它是自动选择的，不用你自己去选



![6](D:\Desktop\学习ESP32笔记\pic\6.png)

### 串口的选择也可以自己选



![8](D:\Desktop\学习ESP32笔记\pic\8.png)



### 可以看到开发板上面的灯会闪烁

![7](D:\Desktop\学习ESP32笔记\pic\7.jpg)



## 4.快捷键的设置



![9](D:\Desktop\学习ESP32笔记\pic\9.png)





## 5.添加别人写的代码工程



![10](D:\Desktop\学习ESP32笔记\pic\10.png)



### 添加完成之后，然后打开（多刷新几遍，就是多点Projects下面的那几个选项）

![11](D:\Desktop\学习ESP32笔记\pic\11.png)





### 在这边就能看到你所添加的工程文件

![12](D:\Desktop\学习ESP32笔记\pic\12.png)



### 在这边选择你要编译的工程



![13](D:\Desktop\学习ESP32笔记\pic\13.png)



### 在文件中修改的代码，最终都会修改到这个工程指向的路径的文件



![14](D:\Desktop\学习ESP32笔记\pic\14.png)



### 没有工作区间了，就在这打开以前打开的文件





![15](D:\Desktop\学习ESP32笔记\pic\15.png)



## 6.其余库的安装

![16](D:\Desktop\学习ESP32笔记\pic\16.png)



### 示例的阅读，和将这个库加入到你选择的工程里面（和Arduino IDE差不多）

![17](D:\Desktop\学习ESP32笔记\pic\17.png)



## 7.ESP32关于PlatformIO的配置信息

### 看哔站的[ESP32的BLE_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1tv411w74d/?p=7&spm_id_from=333.1007.top_right_bar_window_history.content.click&vd_source=94b21086b08ee28baa241d810cbe7268)P8



## 8.ESP32与FreeRTOS

[FreeRTOS - ESP32 - — ESP-IDF 编程指南 v4.3 文档 (espressif.com)](https://docs.espressif.com/projects/esp-idf/en/v4.3/esp32/api-reference/system/freertos.html)





