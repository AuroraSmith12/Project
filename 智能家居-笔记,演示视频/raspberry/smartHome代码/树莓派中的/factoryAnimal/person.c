#include "animal.h"

void personEat()
{
	printf("person eat rice\n");
}

void personBeat()
{
	printf("person bite  your brother\n");
}

struct Animal person = {
	.name = "xiaoming",
	.peat = personEat,
	.pbeat = personBeat

};


struct Animal* putPersonInLink(struct Animal *phead)
{
	if(phead == NULL){
		phead = &person;
		return phead;
	}else{
		person.next = phead;
		phead = &person;
		return phead;

	}
}

