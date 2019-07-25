#include <stdio.h>

int max(int a,int b)
{
    if(a>=b) return a;
    else return b;
}
int main()
{
    int (*p)(int,int) = max;//定义函数指针指向max
    int a,b,c;
    scanf("%d %d",&a,&b);
    c = (*p)(a,b); //通过函数指针调用max函数
    printf("a = %d b = %d max = %d",a,b,c);
    return 0;
}

