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
	struct Animal cat = {
			    .peat = catEat//选择性赋值
				};
	struct Animal dog = {
			    .peat = dogEat
				};
	
	dog.peat();
	cat.peat();

	return 0;
}
