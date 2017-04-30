#include <stdio.h>
#include <string.h>
#include "data.h"

void printFlow()
{
	system("cls");
	printf("��ѡ�����̱��\n");
	printf("--------------------------------------------------\n");
	printf("1.�Һ�\n");
	printf("2.��ѯ���йҺ�\n");
	printf("3.������������\n");
	printf("4.��������\n");
	printf("10.����\n");
	printf("-1.�˳�ϵͳ\n");
	printf("--------------------------------------------------\n");
}

int main()
{
	int flow=0;
	NODE *head=NULL,*pnow=NULL,*ptemp=NULL;

	initialization(&head,&pnow);
	printFlow();

	while (1)
	{
		scanf("%d",&flow);
		if (flow == -1)
			break;

		switch(flow)
		{
		case 1:
			getInput(&pnow);
			printFlow();
			break;
		case 2:
			showData(head);
			break;
		case 3:
			BubbleSort(head);
			break;
		case 10:
			printFlow();
			break;
		default: break;
		}
	}

	saveFile(head);
	printf("\n");
	system("pause");

	return 0;
}