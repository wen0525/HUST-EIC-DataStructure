#include <stdio.h>
void main()
{
    int x,y,z;
    scanf("%d%d%d",&x,&y,&z);
    int temp;
    if(x<y)
    {
        temp=x;
        x=y;
        y=temp;
    }
    if(x<z)
    {
        temp=x;
        x=z;
        z=temp;
    }
    if(y<z)
    {
        temp=y;
        y=z;
        z=temp;
    }
    printf("%d %d %d\n",x,y,z);
}
