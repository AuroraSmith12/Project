static int i;
static int val = LOW;
static int cnt = 0;

void setup() {
  // put your setup code here, to run once:
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
  // put your main code here, to run repeatedly:
  if(val == digitalRead(10))
  {
  delay(50);
  digitalWrite(10, HIGH);
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
  delay(50);
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
  delay(50);
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
