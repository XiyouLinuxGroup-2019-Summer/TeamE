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

int lower_bound_STL(int *a,int first,int last,int v)
{
    int half; //这个half就是查找区间的一半，就是这个二分的核心
    int len = last - first;//初始时查找区间是整个区间
    int middle;//都是通过first + 区间长度来筛选的
    while(len > 0)//当len = 0的时候就是我们要找的值了
    {
        half = len >> 1;
        middle = first+half;
        if(a[middle] < v)
        {
            first = middle + 1;
            len = len - half -1;//与上面分析类似就是在[m+1,y]中查找
        }
        else len = half;// [x,m]中查找
    }
    return first;
}
int main()
{
    int a[10] =  {1,2,2,2,4,5,6,7,8,9};
    /* int a[10] = {1,2,2,2,3,3,7,8,9,10}; */
    int v = 2;
    cout << lower_bound_STL(a,0,9,2) << endl;
    cout << lower_bound_STL(a,0,9,3) << endl;
    /* cout << upper_bound(a,0,9,v) << endl; */
    return 0;
}

