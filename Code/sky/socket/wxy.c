#include<stdio.h>                                       
#include<stdlib.h>
#define N 200000+100
int comp(const void*a,const void*b)//用来做比较的函数。
{
    return *(int*)a-*(int*)b;
}
int main()
{
    int a[N];
    int i,t,n;
    int temp=1;
   scanf("%d",&n);
   {
     temp=1;
     for(i=0;i<n;i++)
        scanf("%d",&a[i]);
     qsort(a,n,sizeof(int),comp);//调用qsort排序
     /* for(i=0;i<n;i++) */
        /* printf("%d",a[i]); */

     for(i=0;i<n;i++)
     {
        if(a[i]>=temp)
        {
            temp++;
        }
     }
     printf("%d\n",temp-1);
   }
}
