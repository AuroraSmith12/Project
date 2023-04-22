#include <stdio.h>


struct Animal{
	char name[20];
	int sex;
	void (*peat)();

};

void dogEat(void)
{
	printf("dog eats shit\n");
}
void catEat(void)
{
	printf("cat eats fish\n");
}
int main()
{
	struct Animal cat;
	struct Animal dog;
	
	cat.peat = catEat;
	dog.peat = dogEat;

	dog.peat();
	cat.peat();

	return 0;
}
