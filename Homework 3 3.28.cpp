#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;

typedef int QElemType;

typedef struct QNode {
	QElemType data;
	QNode *next;
}QNode, *QueuePtr;
typedef struct {
	QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue &Q)
{
	Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.rear)
		exit(OVERFLOW);
	Q.rear->next = Q.rear;
	return OK;
}

Status EnQueue(LinkQueue &Q, QElemType e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = Q.rear->next;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

Status DeQueue(LinkQueue &Q, QElemType &e)
{
	if (Q.rear->next == Q.rear)
		return ERROR;
	QueuePtr p = Q.rear->next->next;
	e = p->data;
	Q.rear->next->next = p->next;
	if (Q.rear == p)
		Q.rear->next = Q.rear;
	free(p);
	return OK;
}

void print_list(LinkQueue Q)
{
	QueuePtr p = Q.rear->next->next;
	while (p != Q.rear->next)
	{
		printf("%d ", p->data);
		if (p != Q.rear)
		{
			printf("-> ");
		}
		p = p->next;
	}
	printf("\n");
}

int main()
{
	QElemType e;
	LinkQueue Q;
	InitQueue(Q);
	for (int i = 1; i < 6; i++)
		EnQueue(Q, i*i);
	print_list(Q);
	EnQueue(Q, 200);
	EnQueue(Q, 300);
	DeQueue(Q, e);
	printf("%d\n", e);
	DeQueue(Q, e);
	printf("%d\n", e);
	print_list(Q);
	return 1;
}