#include <iostream>
#include <map>
#include <vector>
#include <cstdio>
#define _MIN(a,b) a>b?b:a
using namespace std;
int judge(int m)
{
    int cnt = 0;
    while(m)
    {
        cnt += m/5;
        m /= 5;
    }
    return cnt;
}
int bisearch(int num)
{
    int x = 5;
    int y = 500000000;
    int num2;
    while(x < y)
    {
        int m = (x+y)/2;
        num2 = judge(m);
        if(num2 >= num ) y = m;
        else  x = m+1;
    }
    if(judge(x) == num) return x;
    else return -1;
}
int main()
{
    int t;
    cin >> t;
    for(int i = 1;i<=t;i++)
    {
        int num ;
        cin >> num;
        int ans = bisearch(num);
        if(ans > 0)
            printf("Case %d: %d\n",i,ans);
        else printf("Case %d: impossible\n",i);
    }
    return 0;
}

