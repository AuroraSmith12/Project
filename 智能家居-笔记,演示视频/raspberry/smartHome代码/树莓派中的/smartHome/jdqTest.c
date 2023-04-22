#include <stdio.h>
#include<wiringPi.h>

int cnt = 0;
int turn = 0;
void led_one_by_one(void)
{
	for(cnt = 1; cnt < 7; cnt ++)
	{
		digitalWrite(cnt, HIGH);
		delay(200);
	}
	for(cnt = 1; cnt < 7; cnt ++)
	{
		digitalWrite(cnt, LOW);
		delay(200);
	}
	for(cnt = 6; cnt > 0; cnt --)
	{
		digitalWrite(cnt, HIGH);
		delay(200);
	}
	for(cnt = 6; cnt > 0; cnt --)
	{
		digitalWrite(cnt, LOW);
		delay(200);
	}

}
void all_on_off(void)
{
	for(turn = 0; turn < 4; turn ++)
	{
	for(cnt = 1; cnt < 7; cnt ++)
	{
		pinMode(cnt, OUTPUT);
		digitalWrite(cnt, LOW);
	}
		delay(200);
	for(cnt = 1; cnt < 7; cnt ++)
	{
		pinMode(cnt, OUTPUT);
		digitalWrite(cnt, HIGH);
	}
		delay(200);
	for(cnt = 1; cnt < 7; cnt ++)
	{
		pinMode(cnt, OUTPUT);
		digitalWrite(cnt, LOW);
	}
		delay(200);
	for(cnt = 1; cnt < 7; cnt ++)
	{
		pinMode(cnt, OUTPUT);
		digitalWrite(cnt, HIGH);
	}
		delay(200);
	for(cnt = 1; cnt < 7; cnt ++)
	{
		pinMode(cnt, OUTPUT);
		digitalWrite(cnt, LOW);
	}
	}

}
int main()
{
	int err_num = wiringPiSetup();

	if(-1 == err_num)
	{
		printf("wiringPiSetup err\n");
		return -1;
	}
	for(cnt = 1; cnt < 7; cnt ++)
	{
		pinMode(cnt, OUTPUT);
		digitalWrite(cnt, LOW);//继电器打开
	}
	while(1)
	{
	led_one_by_one();
	all_on_off();
	}

	return 0;
}
