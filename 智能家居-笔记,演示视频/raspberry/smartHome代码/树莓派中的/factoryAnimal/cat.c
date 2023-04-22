#include "animal.h"

void catEat()
{
	printf("cat eat fish\n");
}

void catBeat()
{
	printf("cat bite your little brother\n");
}

struct Animal cat = {
	.name = "Tom",
	.peat = catEat,
	.pbeat = catBeat

};


struct Animal* putCatInLink(struct Animal *phead)
{
	if(phead == NULL){
		phead = &cat;
		return phead;
	}else{
		cat.next = phead;  //头插法
		phead = &cat;
		return phead;     //返回最新的头

	}
}

