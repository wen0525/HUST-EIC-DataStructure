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

Status CreateBiTree(BiTree &T)	//先序遍历
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

void PrintBiTree(BiTree T)	//先序遍历
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
void DLR(BiTree T, int &sum)	//先序遍历
{
	if (T != NULL)
	{
		if (!T->lchild && !T->rchild)
		{
			sum++;
			printf("%c\t", T->data);	//不必要
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

//Test 6.47 无法正常输出
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

//Test 6.49 无法正常输出
Status IsCompleteBiTree(BiTree &T)
{			//层次遍历
	if (T = NULL)
		return OK;
	EnQueue(Q, T);
	BiTree temp;
	while (!QueueIsEmpty(Q))
	{
		DeQueue(Q, temp);
		if (temp->rchild)			//右孩子不为空
		{
			if (!temp->lchild)		//左孩子为空即若某个节点只有右孩子则输出ERROR
				return ERROR;
			else					//左孩子不为空
			{			
				EnQueue(Q, temp->lchild);
				EnQueue(Q, temp->rchild);
			}
		}
		else						//右孩子为空，则该节点之后的节点均为叶子节点
		{
			if (temp->lchild)
				EnQueue(Q, temp->lchild);
			while (!QueueIsEmpty(Q))
			{
				DeQueue(Q, temp);
				if (temp->lchild || temp->rchild)	//只要不是叶子节点就输出ERROR
					return ERROR;
			}
		}
	}
	return OK;
}

//Test 6.65 无法正常输出
#define N 11
char pre[] = "-+a*b-cd/ef";
char in[] = "a+b*c-d-e/f";
BiTree create_pre_in(char *pre, char *in, int n)//pre存放前序序列，in存放中序序列，n为序列的长度
{
	int i = 0;
	int n1 = 0, n2 = 0;
	int m1 = 0, m2 = 0;
	BiTree tree = NULL;
	char lchild_pre[N], rchild_pre[N];//lchild_pre[N] 存放前序序列中的左子树；rchild_pre[N]存放前序序列中的右子树
	char lchild_in[N], rchild_in[N]; //lchild_in[N]存放中序序列中的左子树；rchild_in[N]存放中序序列中的右子树
	if (n == 0)
		return NULL;
	tree = (BiTNode *)malloc(sizeof(BiTNode));
	if(tree==NULL)
		return NULL;
	tree->data = pre[0]; //前序序列的第一个元素一定是根节点
	for (i = 0; i < n; i++)
	{
		//求前序序列中的左子树和右子树
		if ((i <= n1) && (in[i] != pre[0]))
			lchild_in[n1++] = in[i];
		else if (in[i] != pre[0])
			rchild_in[n2++] = in[i];
	}
	for (i = 1; i < n; i++)
	{
		//求中序序列中的左子树和右子树
		if (i < (n1 + 1))
			lchild_pre[m1++] = pre[i];
		else
			rchild_pre[m2++] = pre[i];
	}
	//使用递归，分别插入左子树和右子树
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