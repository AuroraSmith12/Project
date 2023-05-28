static int i;
void setup() {
  // put your setup code here, to run once:
    pinMode(4, OUTPUT);
    digitalWrite(4, HIGH);
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(i = 0; i <= 255; i++)
  {
  analogWrite(4, i);
  analogWrite(5, i);
  delay(5);
  }
    for(i = 255; i > 0; i--)
  {
  analogWrite(4, i);
  analogWrite(5, i);
  delay(5);
  }
}
