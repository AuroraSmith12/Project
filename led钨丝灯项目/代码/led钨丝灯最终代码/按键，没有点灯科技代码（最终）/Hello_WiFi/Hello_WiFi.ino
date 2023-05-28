/* *****************************************************************
 *
 * Download latest Blinker library here:
 * https://github.com/blinker-iot/blinker-library/archive/master.zip
 * 
 * 
 * Blinker is a cross-hardware, cross-platform solution for the IoT. 
 * It provides APP, device and server support, 
 * and uses public cloud services for data transmission and storage.
 * It can be used in smart home, data monitoring and other fields 
 * to help users build Internet of Things projects better and faster.
 * 
 * Make sure installed 2.7.4 or later ESP8266/Arduino package,
 * if use ESP8266 with Blinker.
 * https://github.com/esp8266/Arduino/releases
 * 
 * Make sure installed 1.0.5 or later ESP32/Arduino package,
 * if use ESP32 with Blinker.
 * https://github.com/espressif/arduino-esp32/releases
 * 
 * Docs: https://diandeng.tech/doc
 *       
 * 
 * *****************************************************************
 * 
 * Blinker 库下载地址:
 * https://github.com/blinker-iot/blinker-library/archive/master.zip
 * 
 * Blinker 是一套跨硬件、跨平台的物联网解决方案，提供APP端、设备端、
 * 服务器端支持，使用公有云服务进行数据传输存储。可用于智能家居、
 * 数据监测等领域，可以帮助用户更好更快地搭建物联网项目。
 * 
 * 如果使用 ESP8266 接入 Blinker,
 * 请确保安装了 2.7.4 或更新的 ESP8266/Arduino 支持包。
 * https://github.com/esp8266/Arduino/releases
 * 
 * 如果使用 ESP32 接入 Blinker,
 * 请确保安装了 1.0.5 或更新的 ESP32/Arduino 支持包。
 * https://github.com/espressif/arduino-esp32/releases
 * 
 * 文档: https://diandeng.tech/doc
 *       
 * 
 * *****************************************************************/
static int i;
static int val = LOW;
static int cnt = 0;

void button_func(void)
{
if(val == digitalRead(10))
  {
  delay(300);
  cnt++;
  }
  if(cnt == 1)//按一下最低亮度
  {
  analogWrite(4, 87);
  analogWrite(5, 87);
  analogWrite(12, 87);
  analogWrite(13, 87);    
  }

  if(cnt == 2)//按两下中亮度
  {
  analogWrite(4, 174);
  analogWrite(5, 174);
  analogWrite(12, 174);
  analogWrite(13, 174);      
  }

  if(cnt == 3)//按三下最高亮度
  {
  analogWrite(4, 255);
  analogWrite(5, 255);
  analogWrite(12, 255);
  analogWrite(13, 255);     
  }

  if(cnt == 4)//按四下呼吸灯模式
  {
  for(i = 0; i <= 255; i++)
  {
  analogWrite(4, i);
  analogWrite(5, i);
  analogWrite(12, i);
  analogWrite(13, i);
  delay(5);

  if(val == digitalRead(10))
  {
  delay(300);
  cnt++;
  }
  }
    for(i = 255; i > 0; i--)
  {
  analogWrite(4, i);
  analogWrite(5, i);
  analogWrite(12, i);
  analogWrite(13, i);
  delay(5);


  if(val == digitalRead(10))
  {
  delay(300);
  cnt++;
  }
  }  
  }

  if(cnt == 5)//按五下关闭灯
  {

    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW); 
    cnt = 0;     
  }
  if(cnt > 5)
  {

    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW); 
    cnt = 0;  
  }  
}
void setup()
{
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    pinMode(5, OUTPUT);
    digitalWrite(5, LOW);
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    pinMode(10, INPUT_PULLUP);
}

void loop() {
    button_func();

}
