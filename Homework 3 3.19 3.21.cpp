#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;

//SqStack
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char SElemType;

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

Status GetTop(SqStack S, SElemType &e)
{
	if (S.top == S.base)
		return ERROR;
	e = *(S.top - 1);
	return OK;
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

//Test
Status fun19(char *s)
{
	SqStack S;
	InitStack(S);
	SElemType e;
	while (*s!='\0')
	{
		if (*s == '(' || *s == '[' || *s == '{')
			Push(S, *s);
		else if (*s == ')')
			if (GetTop(S, e), e == '(')
				Pop(S, e);
			else
				return ERROR;
		else if (*s == ']')
			if (GetTop(S, e), e == '[')
				Pop(S, e);
			else
				return ERROR;
		else if (*s == '}')
			if (GetTop(S, e), e == '{')
				Pop(S, e);
			else
				return ERROR;
		s++;
	}
	return OK;
}

char *fun21(char *s)
{
	SqStack S1, S2;
	InitStack(S1);
	InitStack(S2);
	Push(S1, '#');
	char e;
	int len = 0;
	while (*s != '\0')
	{
		switch (*s)
		{
			case '(':
				Push(S1, *s);
				break;
			case ')':
				while (GetTop(S1, e), e != '(')		//将上一个'('之后的栈顶元素逐个出栈并送入S2
				{
					Pop(S1, e);
					Push(S2, e);
				}
				Pop(S1, e);							//舍弃'('
				break;
			case '+':
			case '-':
				for (GetTop(S1, e); e != '#'; GetTop(S1, e))
				{
					if (e == '(')
						break;
					else
					{
						Pop(S1, e);
						Push(S2, e);
					}
				}
				Push(S1, *s);
				len++;
				break;
			case '*':
			case '/':
				for (GetTop(S1, e); e != '#'&&e != '+'&&e != '-'; GetTop(S1, e))
				{
					if (e == '(')
						break;
					else
					{
						Pop(S1, e);
						Push(S2, e);
					}
				}
				Push(S1, *s);
				len++;
				break;
			default:
				Push(S2, *s);
				len++;
		}
		s++;
	}
	while (S1.top != S1.base&&*(S1.top - 1) != '#')
	{
		Pop(S1, e);
		Push(S2, e);
	}
	char *p;
	p = (char *)malloc((len + 1) * sizeof(char));
	p += len;
	*p = '\0';
	while (S2.top != S2.base)
	{
		p--;
		Pop(S2, e);
		*p = e;
	}
	return p;
}


int main()
{
	/*Test 3.19
	char s[] = "(a+b*[c/(d+e)-f]+a*{b+c}-d)*f";
	printf("%d\n", fun19(s));*/

	/*Test 3.21
	char s[] = "a+b*c-d+a*(b-c+d)";
	puts(fun21(s));*/

	return 1;
}