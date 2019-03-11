#include <stdio.h>
#include <stdlib.h>
void main()
{
    int n;
    printf("n=");
    scanf("%d",&n);
    float *a;
    a=(float *)malloc(sizeof(float)*(n+1));
    for(int i=n;i>=0;i--)
    {
        printf("a%d=",i);
        scanf("%f",a+i);
    }
    float x0;
    printf("x0=");
    scanf("%f",&x0);
    float p=*(a+n);
    for(int j=n-1;j>=0;j--)
    {
        p*=x0;
        p+=*(a+j);
    }
    printf("P%d(x0)=%f\n",n,p);
    free(a);
    a=NULL;
}
