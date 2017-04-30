#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//����ʵ��
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
	if(fpRead==NULL)
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
}

NODE* getInput(NODE **pnow)
{
	NODE *pnew;

	pnew=(NODE *)malloc(sizeof(NODE));
	if (pnew==NULL)
	{
		return;
	}

	printf("�밴���¸�ʽ¼��Һ���Ϣ����ֵ֮���Կո�ָ�\n");
	printf("�Һŵ��� ���� �Ա��С�Ů�� ����\n");
	printf("--------------------------------------------------\n");

	scanf("%s %s %s %s",pnew->p.cardID,pnew->p.name,pnew->p.sex,pnew->p.money);

	pnew->next=NULL;
	(*pnow)->next=pnew;
	*pnow=pnew;
	return *pnow;
}

void showData(NODE *head)
{
	NODE *p;
	if(head->next!=NULL)
	{
		printf("\n");
		printf("�Һŵ��� ���� �Ա��С�Ů�� ����\n");
		printf("--------------------------------------------------\n");
		for (p=head->next; p!=NULL; p=p->next)
			printf("%s %s %s %s\n",p->p.cardID,p->p.name,p->p.sex,p->p.money);
		printf("\n");
	}
	else 
	{
		printf("��������\n");
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
		printf("���ݱ���ɹ�\n");
	}
}

void Pfree(NODE *head) {
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

void initMoney(NODE *head)
{
	NODE *p;
	FILE* fp = fopen("data.txt","w+");

	if(head->next!=NULL)
	{
		for (p=head->next; p!=NULL; p=p->next)
			p->p.f_money=atof(p->p.money);
	}
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

	return pNode;  
}