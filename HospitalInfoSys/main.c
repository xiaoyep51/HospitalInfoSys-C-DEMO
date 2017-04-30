#include <stdio.h>
#include <string.h>
#include "data.h"

void printFlow()
{
	system("cls");
	printf("请选择流程编号\n");
	printf("--------------------------------------------------\n");
	printf("1.挂号\n");
	printf("2.查询所有挂号\n");
	printf("3.根据收银排序\n");
	printf("4.收银汇总\n");
	printf("10.清屏\n");
	printf("-1.退出系统\n");
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