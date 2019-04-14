#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char* String;

typedef char ElemType;

//KMP
void get_next(String T, int next[])
{
	int Tlen = strlen(T);
	int i = 0;
	next[0] = -1;
	int j = -1;
	while (i < Tlen)
	{
		if (j == -1 || T[i] == T[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
			j = next[j];
	}
}
int Index_KMP(String S, String T, int pos)
{
	int Slen = strlen(S), Tlen = strlen(T);
	int *next;
	next = (int *)malloc(Tlen * sizeof(ElemType));
	get_next(T, next);
	int i = pos, j = 0;
	while (i < Slen && j < Tlen)
	{
		if (j == 0 || S[i] == T[j])
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j == Tlen)
		return i - Tlen;
	else
		return -1;
}

int main()
{
	/*Testing data for Index_KMP*/
	ElemType S[] = "acabaabaabcacaabc";
	ElemType T[] = "abaabcac";
	printf("%d\n", Index_KMP(S, T, 0));

	return 0;
}
