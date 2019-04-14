#include<stdio.h>
#include<string.h>

#define SIZE 256
#define MAX 1000

void main()

{
	int arr[SIZE];
	char str[MAX];
	int i, len;
	for (i = 0; i < SIZE; i++)
		arr[i] = 0;
	gets_s(str);
	len = strlen(str);
	for (i = 0; i < len; i++)
		arr[(int)str[i]]++;
	int n = 0;
	for (i = 0; i < SIZE; i++)
		if (arr[i] != 0)
		{
			n++;
			printf("%c:%d\n", i, arr[i]);
		}

	printf("Total:%d\n",n);

}
