#include "animal.h"

void dogEat()
{
	printf("dog eat shi\n");
}

void dogBeat()
{
	printf("dog bite your little brother\n");
}

struct Animal dog = {
	.name = "ahuang",
	.peat = dogEat,
	.pbeat = dogBeat

};


struct Animal* putDogInLink(struct Animal *phead)
{
	if(phead == NULL){
		phead = &dog;
		return phead;
	}else{
		dog.next = phead;
		phead = &dog;
		return phead;

	}
}

