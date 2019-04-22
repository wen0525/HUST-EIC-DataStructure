#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 27

typedef struct
{ 
	int weight;
	int lchild, rchild, parent;
	char ch;
}HTNode, *HuffmanTree;

typedef char** HuffmanCode;

int w[N] = { 186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1 };
char c[N + 1] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char File[] = "THIS PROGRAM IS MY FAVORITE";
char CodeFile[1000];
char TextFile[100];

void Select(HuffmanTree HT, int i, int &s1, int &s2)
{
	s1 = s2 = 0;
	int j, m1 = 999, m2 = 999;
	for (j = 1; j <= i; j++)
	{
		if (HT[j].parent == 0 && HT[j].weight < m1)
		{
			m2 = m1;
			s2 = s1;
			m1 = HT[j].weight;
			s1 = j;
		}

		else if (HT[j].parent == 0 && HT[j].weight < m2)
		{
			m2 = HT[j].weight;
			s2 = j;
		}
	}
}

void InitHuffmanTree(HuffmanTree &HT, int *w, char *c, int n)
{
	if (n <= 1)
		return;
	int m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	HuffmanTree p;
	int i, s1, s2;
	for (p = HT + 1, i = 1; i <= n; i++, p++, w++, c++)
		*p = {*w, 0, 0, 0, *c};
	for (; i <= m; i++, p++)
		*p = {0, 0, 0, 0, '\0'};
	for (i = n + 1; i <= m; i++)
	{
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}

void CreateHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
	char *cd = (char *)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	int i;
	for (i = 1; i <= n; i++)
	{
		int start = n - 1;
		int c, f;
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char *)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
}

void Encoding(HuffmanCode HC, char *File, char *CodeFile)
{
	int i;
	char *temp;
	for (i = 0; File[i] != '\0'; i++)
	{
		if (File[i] == ' ')
			temp = HC[1];
		else
			temp = HC[File[i] - 'A' + 2];
		strcat(CodeFile, temp);
	}
}

void Decoding(HuffmanTree HT, char *CodeFile, char *TextFile, int n)
{
	int i, j = 2 * n - 1;
	for (i = 0; CodeFile[i] != '\0'; i++)
	{
		if (CodeFile[i] == '0')
			j = HT[j].lchild;
		else
			j = HT[j].rchild;
		if (HT[j].lchild == 0)
		{
			*TextFile = HT[j].ch;
			TextFile++;
			j = 2 * n - 1;
		}
	}
	*TextFile == '\0';
}

int main()
{
	HuffmanTree HT;
	InitHuffmanTree(HT, w, c, N);
	HuffmanCode HC;
	CreateHuffmanCode(HT, HC, N);

	/*±àÂëÊä³ö²âÊÔ
	for (int i = 1; i <= N; i++)
		printf("%c(%3d):%s\n", HT[i].ch, w[i - 1], HC[i]);*/

	Encoding(HC, File, CodeFile);
	puts(CodeFile);
	Decoding(HT, CodeFile, TextFile, N);
	puts(TextFile);

	return 0;
}