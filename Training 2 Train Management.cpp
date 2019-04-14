#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;

//SqStack
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S)
{
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
		exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}

Status StackEmpty(SqStack S)
{
	if (S.top == S.base)
		return OK;
	return ERROR;
}

Status Push(SqStack &S, SElemType e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base)
			exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack &S, SElemType &e)
{
	if (S.top == S.base)
		return ERROR;
	e = *--S.top;
	return OK;
}

Status PrintArray(int *s,int n)
{
	for (int i = 0; i < n; i++)
		printf("%5d", s[i]);
	printf("\n");
	return OK;
}

void Move(SqStack temp, int In[], int Out[], int i,int j,int n)
{
	if (i < n)					//ÈëÕ»
	{
		Push(temp, In[i]);
		Move(temp, In, Out, i + 1, j, n);
		Pop(temp, Out[j]);
	}
	if (!StackEmpty(temp))		//³öÕ»
	{
		Pop(temp, Out[j]);
		Move(temp, In, Out, i, j + 1, n);
		Push(temp, Out[j]);
	}
	if (j >= n && StackEmpty(temp))
	{
		printf("\t\tOut---->");
		PrintArray(Out, n);
	}	
}

#define N 5

int main()
{
	int In[N];
	int i;
	for (i = 0; i < N; i++)
		In[i] = i + 1;
	printf("\t\tIn <----");
	PrintArray(In, N);
	printf("\t\t||\n\t\t||\n\t\t||\n\t\t||\n================\n\t\t||\n\t\t||\n\t\t||\n\t\t||\n");
	SqStack temp;
	InitStack(temp);
	int Out[N];
	Move(temp, In, Out, 0, 0, N);
	return 0;
}