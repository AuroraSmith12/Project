#include <stdio.h>


struct Animal{
	char name[128];
	int  age;
	int  sex;
	int  others;
	void (*peat)();
	void (*pbeat)();
	void (*test)();

	struct Animal *next;

};

struct Animal* putPersonInLink(struct Animal *phead);//先声明
struct Animal* putCatInLink(struct Animal *phead);
struct Animal* putDogInLink(struct Animal *phead);

