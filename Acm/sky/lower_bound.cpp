#include <iostream>
using namespace std;

//找到第一个>=key的元素的下标
int lower_bound(int *a,int x,int y,int v)//返回第一个出现的位置，若不存在在此处插入v后仍然有序
{
    int m;
    while(x < y)
    {
        m = x+(y-x)/2;
        if(a[m] >= v) y = m;//出现相等元素继续向前赵
        else x = m + 1;//针対找过了的情况
    }
    return x;
}

int upper_bound(int *a,int x,int y,int v)
{
    int m ;
    while(x < y)
    {
        m = x+(y-x)/2;
        if(a[m] <=  v) x = m+1;
        else y = m;
    }
    return x;
}
int main()
{
    int a[10] = {1,2,2,2,3,3,7,8,9,10};
    int v = 2;
    cout << lower_bound(a,0,9,v) << endl;
    cout << upper_bound(a,0,9,v) << endl;
    return 0;
}

