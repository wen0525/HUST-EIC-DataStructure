#include<stdio.h>

#define MAX_SIZE 10
typedef int datatype;

void reverse(datatype *a, int l, int r)
{
	int temp;
	while (l<r)
	{
		temp = a[l];
		a[l] = a[r];
		a[r] = temp;
		l++;
		r--;
	}
}

void move(datatype* a, int n,int k)
{
	k %= n;
	reverse(a, 0, n - 1 - k);
	reverse(a, n - k, n - 1);
	reverse(a, 0, n - 1);
}

void print_array(datatype* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%5d", *(a + i));
	}
	printf("\n");
}

int main()
{
	datatype a[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++)
	{
		a[i] = (i + 1)*i;
	}
	print_array(a, MAX_SIZE);
	int k = 3;
	move(a, MAX_SIZE, k);
	print_array(a, MAX_SIZE);
}