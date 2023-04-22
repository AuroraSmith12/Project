#include "animal.h"
#include <string.h>

struct Animal* findUtilByName(char* str, struct Animal* phead)//结构体查询
{
	struct Animal *tmp= phead;

	if(phead== NULL){
		printf("空\n");
		return NULL;
	}else{
		while(tmp != NULL){
			if(strcmp(tmp->name,str) == 0){
				return tmp;
			}
			tmp=tmp->next;
		}
		return NULL;
	}
}

int main()
{
	char buf[128]={'\0'};
	struct Animal *phead = NULL;
	struct Animal *ptmp;

	phead = putCatInLink(phead);
	phead = putDogInLink(phead);
	phead = putPersonInLink(phead);//至此已经组合完成整个链表


	while(1){
		printf("please input：Tom，ahuang, xiaoming\n");  //链表的查询
		scanf("%s",buf);
		ptmp = findUtilByName(buf,phead);

		if(ptmp != NULL){
			ptmp->pbeat();
			ptmp->peat();
		}
		memset(buf, '\0',sizeof(buf)); //此处不能用strlen
	}

	return 0;
}

