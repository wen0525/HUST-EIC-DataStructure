#include<stdio.h>
#include<stdlib.h>

typedef int datatype;

typedef struct CLNode
{
	datatype No;
	datatype code;
	struct CLNode *next;
}CLNode, *CLinkList;

CLinkList InitNode()
{
	CLinkList L = (CLinkList)malloc(sizeof(CLNode));
	L->next = NULL;
	return L;
}

void CreateCL(CLinkList head, int n)
{
	CLinkList tail, p;
	tail = head;
	for (int i = 1; i <= n; i++)
	{
		p = InitNode();
		p->No = i;
		printf("No.%d Code=", i);
		scanf_s("%d", &p->code);
		tail->next = p;
		tail = p;
	}
	tail->next = head->next;
}

void Solve(CLinkList L, int m)
{
	CLinkList p=L->next, q=NULL;

	while (p->next != p)
	{
		for (int i = 1; i < m; i++)
		{
			q = p;
			p = p->next;
		}
		printf("%d ", p->No);
		m = p->code;
		q->next = p->next;
		free(p);
		p = q->next;

	}
	printf("%d\n", p->No);
	free(p);
}

int main()
{
	int m, n;
	printf("m=");
	scanf_s("%d", &m);
	printf("n=");
	scanf_s("%d", &n);
	CLinkList L=InitNode();
	CreateCL(L, n);
	if (m%n)
		m %= n;
	else
		m = n;
	Solve(L, m);
	return 1;
}

/*
	m=20 n=7
	3
	1
	7
	2
	4
	8
	4
*/


