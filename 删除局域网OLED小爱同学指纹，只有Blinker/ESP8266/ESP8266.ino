/*
 * 局域网和oled删除版本
 * D3门，D4灯，D5门继电器，D7蜂鸣器，D6指纹继电器
 * 用到的库：blinker Arduino库( https://diandeng.tech/doc/001-%E5%BF%AB%E9%80%9F%E5%BC%80%E5%A7%8B%2F02-esp8266-WiFi%E6%8E%A5%E5%85%A5.md )
 * 库版本请和视频对应
 */

#define BLINKER_PRINT Serial
#define BLINKER_WIFI
#include <Blinker.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <Servo.h>
/*************************************/
Servo myservo;  // 定义Servo对象来控制
int pos = 0;    // 角度存储变量
/************************修改******************************/
char auth[] = "cad07cf4ebb9";//你的密钥
char ssid[] = "pig"; //要接入的WIFI名
char pswd[] = "1421040608"; //接入的密码
/*********************************************************/

/***************BLINKER新建组件对象*****************/
BlinkerButton Button1("door");
BlinkerButton Button2("on");
BlinkerButton Button3("off");
/*****************************************************/
//注意，为达到精确控制，开门，开灯关灯过程中，CPU都会被占用，请勿重复按开门，否则会开两次
/*****************************开门****************************/
void door(){    
 //for (pos = 0; pos <= 180; pos+=45) { // 0°到180°
    // in steps of 1 degree
    myservo.write(180);              // 舵机角度写入
    delay(3000);                       // 等待转动到指定角度
  //}
  //for (pos = 180; pos >= 0; pos -=45) { // 从180°到0°
    myservo.write(0);              // 舵机角度写入
    delay(3000);                       // 等待转动到指定角度
  //}
    digitalWrite(D3, LOW);
}
/*************************************************************/
/************开灯*************/
void light_on(){
      for(int i=0;i<50;i++){
      digitalWrite(D4, HIGH);
      delayMicroseconds(1800);
      digitalWrite(D4, LOW);
      delay(10);
      }
      for(int i=0;i<50;i++){
      digitalWrite(D4, HIGH);
      delayMicroseconds(1500);
      digitalWrite(D4, LOW);
      delay(10);
      }
}
/****************************/
/*******关灯*******/
void light_off(){
      for(int i=0;i<50;i++){
      digitalWrite(D4, HIGH);
      delayMicroseconds(1000);
      digitalWrite(D4, LOW);
      delay(10);
      }
      for(int i=0;i<50;i++){
      digitalWrite(D4, HIGH);
      delayMicroseconds(1500);
      digitalWrite(D4, LOW);
      delay(10);
      }
}
/*****************/
/****蜂鸣器长响一声****/
void beer_one(){
      digitalWrite(D7, HIGH); 
      delay(500);  
      digitalWrite(D7, LOW);
}
/*********************/
/****蜂鸣器长响两声****/
void beer_two(){
      digitalWrite(D7, HIGH);
      delay(150); 
      digitalWrite(D7, LOW); 
      delay(150); 
      digitalWrite(D7, HIGH);
      delay(150); 
      digitalWrite(D7, LOW); 
}
/*********************/
/*蜂鸣器响三声*/
void beer_three(){
 
      digitalWrite(D7, HIGH);
      delay(150); 
      digitalWrite(D7, LOW); 
      delay(150); 
      digitalWrite(D7, HIGH);
      delay(150); 
      digitalWrite(D7, LOW); 
      delay(150); 
      digitalWrite(D7, HIGH);
      delay(150); 
      digitalWrite(D7, LOW); 
}
/************/

/**************BLINKER按下按键即会执行该函数***************/
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    //beer_one();
    door();
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
}
void button2_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    light_on();
}
void button3_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    light_off();
}
/********************************************************/

void setup() {
/***********初始化串口和IO**********/
ESP.wdtFeed();
    Serial.begin(9600);
    delay(500);
    pinMode(D8, INPUT);
    pinMode(D7, OUTPUT);  
    pinMode(D6, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D3, OUTPUT);
    myservo.attach(D3);
//  pinMode(D2, OUTPUT);
//  pinMode(D1, OUTPUT);
//  pinMode(D0, INPUT);

//  digitalWrite(D8, LOW);
    digitalWrite(D7, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D5, LOW);
    digitalWrite(D4, LOW);
    digitalWrite(D3, LOW);
//  digitalWrite(D2, LOW);
//  digitalWrite(D1, LOW);
//  digitalWrite(D0, LOW);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
/***********************************/
delay(1000);
/******************初始化blinker********************/
    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif
    Blinker.begin(auth, ssid, pswd);
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Button3.attach(button3_callback);
/****************************************************/
Blinker.run();
delay(1000);
}
void loop() {
    Blinker.run();
}
