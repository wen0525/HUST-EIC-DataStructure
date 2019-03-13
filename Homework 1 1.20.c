#include <stdio.h>
#include <stdlib.h>
void main()
{
    int n;
    printf("n=");
    scanf("%d",&n);
    float x0;
    printf("x0=");
    scanf("%f",&x0);
    float *a;
    a=(float *)malloc(sizeof(float)*(n+1));
    printf("a%d=",n);
    scanf("%f",a+n);
    float p=*(a+n);
    for(int i=n-1;i>=0;i--)
    {
        printf("a%d=",i);
        scanf("%f",a+i);
        p*=x0;
        p+=*(a+i);
    }
    printf("P%d(x0)=%f\n",n,p);
    free(a);
    a=NULL;
}
