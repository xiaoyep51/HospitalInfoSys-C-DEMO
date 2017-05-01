#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义实体
struct Patient
{
	char cardID[10];
	char name[20];
	char sex[4];
	char money[10];
	float f_money;
};
struct PatientNode 
{
	struct Patient p;
	struct PatientNode *next;
};
typedef struct PatientNode NODE;

int fileSize(char* filename)  
{
	int size=0;
	FILE *fp=fopen(filename,"r");
	if(!fp) return -1;
	fseek(fp,0L,SEEK_END);
	size=ftell(fp);
	fclose(fp);

	return size;
}

int lengthOfList(NODE *head)
{
	NODE *p = head;
	unsigned int len=0;
	while(p!=NULL)
	{
		p = p->next;
		len++;
	}
	return len;
}

NODE* getItemByIndex(NODE *head,int index)
{
	NODE *p = head->next;
	int i=1,j=lengthOfList(head)-1;
	for(i=1;i<index;i++)
	{
		if(p==NULL)
		{
			printf("无法获取第%d条记录\n",index);
			return NULL;
		}
		p=p->next;
	}

	return p;
}

void Pfree(NODE *head)
{
	NODE *p,*q;
	p=head;
	while (p->next!=NULL)
	{
		q=p->next;
		p->next=q->next;
		free(q);
	}
	free(p);
}

void initialization(NODE **head,NODE **pnow)
{
	int i=0;
	FILE* fpRead = fopen("data.txt","r");
	NODE *temp;

	*head=(NODE *)malloc(sizeof(NODE));
	if (*head==NULL) 
	{
		return;
	}
	if(fpRead==NULL || fileSize("data.txt")<=0)
	{
		(*head)->next=NULL;
		*pnow=*head;
		return;
	}

	while(!feof(fpRead))
	{
		temp=(NODE *)malloc(sizeof(NODE));
		if (temp==NULL) 
		{
			return;
		}
		fscanf(fpRead,"%s %s %s %s\n",temp->p.cardID,temp->p.name,temp->p.sex,temp->p.money);
		temp->next=NULL;
		if(i==0)
			(*head)->next=temp;
		else
			(*pnow)->next=temp;

		*pnow=temp;
		i++;
	}
	fclose(fpRead);
}

NODE* getInput(NODE **pnow)
{
	NODE *pnew;

	pnew=(NODE *)malloc(sizeof(NODE));
	if (pnew==NULL)
	{
		return;
	}

	printf("请按如下格式录入挂号信息，各值之间以空格分隔\n");
	printf("挂号单号 姓名 性别（男、女） 收银\n");

	scanf("%s %s %s %s",pnew->p.cardID,pnew->p.name,pnew->p.sex,pnew->p.money);

	pnew->next=NULL;
	(*pnow)->next=pnew;
	*pnow=pnew;

	printf("录入成功\n");
	return *pnow;
}

void showData(NODE *head)
{
	NODE *p;
	if(head->next!=NULL)
	{
		printf("\n");
		printf("挂号单号 姓名 性别（男、女） 收银\n");
		for (p=head->next; p!=NULL; p=p->next)
			printf("%s %s %s %s\n",p->p.cardID,p->p.name,p->p.sex,p->p.money);
		printf("\n");
	}
	else 
	{
		printf("暂无数据\n");
	}
}

void saveFile(NODE *head)
{
	NODE *p;
	FILE* fp = fopen("data.txt","w+");

	if(head->next!=NULL)
	{
		for (p=head->next; p!=NULL; p=p->next)
			fprintf(fp,"%s %s %s %s\n",p->p.cardID,p->p.name,p->p.sex,p->p.money);
		fflush(fp);
		printf("数据保存成功\n");
	}
	fclose(fp);
}

void initMoney(NODE *head)
{
	NODE *p;

	if(head->next!=NULL)
	{
		for (p=head->next; p!=NULL; p=p->next)
			p->p.f_money=atof(p->p.money);
	}
}

NODE *BubbleSort(NODE *pNode)
{	
	NODE *pMove;
	int count = lengthOfList(pNode);
	pMove = pNode->next;

	initMoney(pNode);
	while (count > 1)
	{
		while (pMove->next != NULL)
		{
			if (pMove->p.f_money > pMove->next->p.f_money)
			{
				struct Patient temp;
				temp = pMove->p;
				pMove->p = pMove->next->p;
				pMove->next->p = temp;
			}
			pMove = pMove->next;  
		}
		count--;

		pMove = pNode->next;
	}

	printf("排序成功，请查看\n");
	return pNode;  
}

int moneySum(NODE *head)
{
	NODE *p = head->next;
	float sum=0;
	if(p==NULL)
	{
		printf("没有记录，清先录入\n");
		return sum;
	}
	initMoney(head);
	while(p!=NULL)
	{
		sum+=p->p.f_money;
		p = p->next;
	}
	printf("总收银为：%.2f\n",sum);
	return sum;
}

int update(NODE *head)
{
	NODE *p = head->next,*pnew;
	int index;
	if(head->next==NULL)
	{
		printf("没有数据，无需修改\n");
		return -1;
	}

	printf("请输入要修改记录的序号，1到%d：",lengthOfList(head)-1);
	scanf("%d",&index);

	p=getItemByIndex(head,index);
	if(p==NULL)
	{
		printf("修改失败\n");
		return -1;
	}

	pnew=(NODE *)malloc(sizeof(NODE));
	if (pnew==NULL)
	{
		return;
	}

	printf("请按如下格式录入挂号信息，各值之间以空格分隔\n");
	printf("挂号单号 姓名 性别（男、女） 收银\n");

	scanf("%s %s %s %s",p->p.cardID,p->p.name,p->p.sex,p->p.money);

	printf("修改成功\n");
	return 0;
}