#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
int main()
{
    int m,j=0;
    int i,ma=0,mb=0;
    int k;
    scanf("%d",&m);
    int max[m];
    for(i=0;i<m;i++)
    {
        max[i]=0;
    }
    while(j!=m)
    {
        ma = 0;
        mb = 0;
        scanf("%d",&k);
        int a[k];
        for(i=0;i<k;i++)
        {
            scanf("%d",&a[i]);
        }
        for(i=0;i<k;i++)
        {
            if(a[i]%3==0)
                max[j]++;
            else if(a[i]%3==1)
                ma++;
            else if(a[i]%3==2)
                mb++;
        }
        /* printf("a0 %d a1%d a2 %d\n",max[j],ma,mb); */
            if(mb>ma)
            {
                max[j]=max[j]+ma;
                max[j]=max[j]+(mb-ma)*2/6;
            }
            else if(ma>mb)
            {
                max[j]=max[j]+mb;
                max[j]=max[j]+(ma-mb)/3;
            }
             else if(ma==mb)
            {
                max[j]=max[j]+ma;
            }
        j++;
    }
for(i=0;i<m;i++)
{
    printf("%d\n",max[i]);
}
return 0;
}
