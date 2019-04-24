#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;

typedef char TElemType;

//BiTree
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

char Tree[] = "ABC$$DE$G$$F$$$";
int i = -1;

Status CreateBiTree(BiTree &T)	//�������
{
	i++;
	if (Tree[i] == '\0')
		return ERROR;
	if (Tree[i] == '$')
		T = NULL;
	else
	{
		if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data = Tree[i];
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}

void PrintBiTree(BiTree T)	//�������
{
	if (T != NULL)
	{
		printf("%c\t", T->data);
		PrintBiTree(T->lchild);
		PrintBiTree(T->rchild);
	}
}

//Queue
typedef BiTree QElemType;

typedef struct QNode {
	QElemType data;
	QNode *next;
}QNode, *QueuePtr;
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue &Q)
{
	Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.rear)
		exit(OVERFLOW);
	Q.front = Q.rear;
	Q.rear->next = NULL;
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
	if (Q.front->next == NULL)
		return ERROR;
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)
		Q.rear->next = NULL;
	free(p);
	return OK;
}

Status QueueIsEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return OK;
	else
		return ERROR;
}


//Test 6.42
void DLR(BiTree T, int &sum)	//�������
{
	if (T != NULL)
	{
		if (!T->lchild && !T->rchild)
		{
			sum++;
			printf("%c\t", T->data);	//����Ҫ
		}
		DLR(T->lchild, sum);
		DLR(T->rchild, sum);
	}
}

//Test 6.43
void ReverseLeftRightChild(BiTree &T)
{
	if (T == NULL)
		return;
	BiTree temp = T->lchild;
	T->lchild = T->rchild;
	T->rchild = temp;
	ReverseLeftRightChild(T->lchild);
	ReverseLeftRightChild(T->rchild);
}

//Test 6.47 �޷��������
LinkQueue Q;
void BFS_Print(BiTree T,LinkQueue Q)
{
	EnQueue(Q, T);
	BiTree temp;
	while (!QueueIsEmpty(Q))
	{
		DeQueue(Q, temp);
		printf("%c\t", temp->data);
		if (temp->lchild)
			EnQueue(Q, temp->lchild);
		if (temp->rchild)
			EnQueue(Q, temp->rchild);
	}
}

//Test 6.49 �޷��������
Status IsCompleteBiTree(BiTree &T)
{			//��α���
	if (T = NULL)
		return OK;
	EnQueue(Q, T);
	BiTree temp;
	while (!QueueIsEmpty(Q))
	{
		DeQueue(Q, temp);
		if (temp->rchild)			//�Һ��Ӳ�Ϊ��
		{
			if (!temp->lchild)		//����Ϊ�ռ���ĳ���ڵ�ֻ���Һ��������ERROR
				return ERROR;
			else					//���Ӳ�Ϊ��
			{			
				EnQueue(Q, temp->lchild);
				EnQueue(Q, temp->rchild);
			}
		}
		else						//�Һ���Ϊ�գ���ýڵ�֮��Ľڵ��ΪҶ�ӽڵ�
		{
			if (temp->lchild)
				EnQueue(Q, temp->lchild);
			while (!QueueIsEmpty(Q))
			{
				DeQueue(Q, temp);
				if (temp->lchild || temp->rchild)	//ֻҪ����Ҷ�ӽڵ�����ERROR
					return ERROR;
			}
		}
	}
	return OK;
}

//Test 6.65 �޷��������
#define N 11
char pre[] = "-+a*b-cd/ef";
char in[] = "a+b*c-d-e/f";
BiTree create_pre_in(char *pre, char *in, int n)//pre���ǰ�����У�in����������У�nΪ���еĳ���
{
	int i = 0;
	int n1 = 0, n2 = 0;
	int m1 = 0, m2 = 0;
	BiTree tree = NULL;
	char lchild_pre[N], rchild_pre[N];//lchild_pre[N] ���ǰ�������е���������rchild_pre[N]���ǰ�������е�������
	char lchild_in[N], rchild_in[N]; //lchild_in[N]������������е���������rchild_in[N]������������е�������
	if (n == 0)
		return NULL;
	tree = (BiTNode *)malloc(sizeof(BiTNode));
	if(tree==NULL)
		return NULL;
	tree->data = pre[0]; //ǰ�����еĵ�һ��Ԫ��һ���Ǹ��ڵ�
	for (i = 0; i < n; i++)
	{
		//��ǰ�������е���������������
		if ((i <= n1) && (in[i] != pre[0]))
			lchild_in[n1++] = in[i];
		else if (in[i] != pre[0])
			rchild_in[n2++] = in[i];
	}
	for (i = 1; i < n; i++)
	{
		//�����������е���������������
		if (i < (n1 + 1))
			lchild_pre[m1++] = pre[i];
		else
			rchild_pre[m2++] = pre[i];
	}
	//ʹ�õݹ飬�ֱ������������������
	tree->lchild = create_pre_in(lchild_pre, lchild_in, n1);
	tree->rchild = create_pre_in(rchild_pre, rchild_in, n2);
	return tree;
}

int main()
{
	BiTree T;
	CreateBiTree(T);
	int sum = 0;
	PrintBiTree(T);
	printf("\n");

	//Test 6.42
	DLR(T, sum);
	printf("The number of leaves is %d.\n", sum);

	//Test 6.43
	ReverseLeftRightChild(T);
	PrintBiTree(T);
	printf("\n");

	//Test 6.47
	//InitQueue(Q);
	//BFS_Print(T, Q);
	//Test 6.49

	//Test 6.65

	return 0;
}