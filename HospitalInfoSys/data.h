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
			printf("�޷���ȡ��%d����¼\n",index);
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

	printf("�밴���¸�ʽ¼��Һ���Ϣ����ֵ֮���Կո�ָ�\n");
	printf("�Һŵ��� ���� �Ա��С�Ů�� ����\n");

	scanf("%s %s %s %s",pnew->p.cardID,pnew->p.name,pnew->p.sex,pnew->p.money);

	pnew->next=NULL;
	(*pnow)->next=pnew;
	*pnow=pnew;

	printf("¼��ɹ�\n");
	return *pnow;
}

void showData(NODE *head)
{
	NODE *p;
	if(head->next!=NULL)
	{
		printf("\n");
		printf("�Һŵ��� ���� �Ա��С�Ů�� ����\n");
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

	printf("����ɹ�����鿴\n");
	return pNode;  
}

int moneySum(NODE *head)
{
	NODE *p = head->next;
	float sum=0;
	if(p==NULL)
	{
		printf("û�м�¼������¼��\n");
		return sum;
	}
	initMoney(head);
	while(p!=NULL)
	{
		sum+=p->p.f_money;
		p = p->next;
	}
	printf("������Ϊ��%.2f\n",sum);
	return sum;
}

int update(NODE *head)
{
	NODE *p = head->next,*pnew;
	int index;
	if(head->next==NULL)
	{
		printf("û�����ݣ������޸�\n");
		return -1;
	}

	printf("������Ҫ�޸ļ�¼����ţ�1��%d��",lengthOfList(head)-1);
	scanf("%d",&index);

	p=getItemByIndex(head,index);
	if(p==NULL)
	{
		printf("�޸�ʧ��\n");
		return -1;
	}

	pnew=(NODE *)malloc(sizeof(NODE));
	if (pnew==NULL)
	{
		return;
	}

	printf("�밴���¸�ʽ¼��Һ���Ϣ����ֵ֮���Կո�ָ�\n");
	printf("�Һŵ��� ���� �Ա��С�Ů�� ����\n");

	scanf("%s %s %s %s",p->p.cardID,p->p.name,p->p.sex,p->p.money);

	printf("�޸ĳɹ�\n");
	return 0;
}