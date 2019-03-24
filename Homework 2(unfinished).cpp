#include<stdio.h>
#include<stdlib.h>

#define maxsize 1000

typedef float datatype;

//SeqList
typedef struct
{
	datatype elem[maxsize];
	int length;
}SqList;

SqList *init_seqlist()
{
	SqList *L;
	L = (SqList*)malloc(sizeof(SqList));
	L->length = 0;
	return L;
}

int insert_seqlist(SqList *L, int i, datatype e)
{
	int j;
	if (L->length == maxsize - 1)
	{
		printf("list is already full\n");
		return -1;
	}
	if (i<0 || i>L->length + 1)
	{
		printf("wrong position\n");
		return -1;
	}
	for (j = L->length; j >= i - 1; --j)
	{
		L->elem[j + 1] = L->elem[j];
	}
	L->elem[i] = e;
	L->length++;
	return 1;
}

void print_seqlist(SqList *L)
{
	int i;
	for (i = 0; i < L->length-1; ++i)
	{
		printf("%f -> ", L->elem[i]);
	}
	printf("%f\n", L->elem[L->length-1]);
}

//LinkList
typedef struct Node
{
	datatype data;
	Node *next;
} LNode,*LinkList;

LNode *init()
{
	LNode *L = (LinkList)malloc(sizeof(Node));
	L->next = NULL;
	return L;
}

int length(LinkList L)
{
	LinkList p = L;
	int j = 0;
	while (p)
	{
		p = p->next;
		++j;
	}
	return j;
}

LinkList find(datatype x, LinkList L)
{
	LinkList p = L;
	while (p != NULL && p->data != x)
	{
		p = p->next;
	}
	return p;
}

LinkList findkth(int k, LinkList L)
{
	LinkList p = L;
	int i = 1;
	while (p != NULL && i < k)
	{
		p = p->next;
		++i;
	}

	if (i == k)
	{
		return p;
	}
	else
	{
		return NULL;
	}
}

LinkList insert(LinkList L, int i, datatype x)
{
	LinkList p, s;
	if (i == 1)
	{
		s = (LinkList)malloc(sizeof(LNode));
		s->data = x;
		s->next = L;
		return s;
	}
	p = findkth(i - 1, L);
	if (NULL == p)
	{
		printf("out of range\n");
		return NULL;
	}
	else
	{
		s = (LinkList)malloc(sizeof(LNode));
		s->data = x;
		s->next = p->next;
		p->next = s;
		return L;
	}
}

LinkList inverse(LinkList L)
{
	LinkList p = L;
	LinkList q = NULL;
	LinkList head = NULL;
	while (p)
	{
		q = p->next;
		p->next = head;
		head = p;
		p = q;
	}
	return head;
}

void print_linklist(LinkList L)
{
	LinkList p = L;
	while (NULL != p)
	{
		printf("%f ", p->data);
		if (p->next != NULL)
		{
			printf("-> ");
		}
		p = p->next;
	}
	printf("\n");
}


LinkList fun19(LinkList L, datatype mink, datatype maxk)
{
	LinkList p = L;
	LinkList q = p;
	while (p->data<mink&&p->next!=NULL)
	{
		q = p;
		q->next = p->next;
		p = p->next;
	}
	if (q->next == NULL)
	{
		printf("not found\n");
		return NULL;
	}
	while (p->data < maxk && p->next != NULL)
		p = p->next;
	if (q->next == p)
	{
		printf("not found\n");
		return NULL;
	}
	LinkList m=q->next;
	while (m!=p)
	{
		q->next = m->next;
		free(m);
		m = q->next;
	}
	return L;
}

void fun21(SqList* L)
{
	int i,n=L->length;
	datatype temp;
	for (i = 0; i < n / 2; i++)
	{
		temp = L->elem[i];
		L->elem[i] = L->elem[n - 1 - i];
		L->elem[n - 1 - i] = temp;
	}
}

void fun24(LinkList A, LinkList B, LinkList C)
{
	LinkList pa = A->next, pb = B->next, pc = A;
	C = pc;
	while (pa&&pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;	//CÍê³ÉµÝÔöÅÅÐò
	free(B);
	LinkList iC = inverse(C);	//C¾ÍµØÄæÖÃ
	C = iC;
	print_linklist(C);
}

int main()
{
	int i = 0;
	datatype x = 0;

	/*TEXT 2.19
	LinkList L = init();
	for (i = 0; i < 5; ++i)
	{
		insert(L, i + 1, i*i);
	}
	print_linklist(L);

	printf("TEXT 2.19:\n");
	float mink = 3, maxk = 10;
	fun19(L, mink, maxk);
	print_linklist(L);*/

	/*TEXT 2.21
	SqList* L = init_seqlist();
	for (i = 0; i < 6; ++i)
	{
		insert_seqlist(L, i , i*i);
	}
	print_seqlist(L);

	printf("TEXT 2.21:\n");
	fun21(L);
	print_seqlist(L);*/

	/*TEXT 2.24
	LinkList A = init(), B = init();
	for(i=0;i<5;i++)
	{ 
		insert(A, i + 1, i*i);
	}
	for (i = 0; i < 7; i++)
	{
		insert(B, i + 1, i*2);
	}
	print_linklist(A);
	print_linklist(B);
	LinkList C = init();
	printf("TEXT 2.24:\n");
	fun24(A, B, C);*/

	return 1;
}
