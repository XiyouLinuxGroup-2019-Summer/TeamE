#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <cstdio>
using namespace std;
typedef long long LL;//防止超过int 范围
int main()
{
    set <LL > s;//保存该丑数是否出现过
    priority_queue<LL ,vector<LL>, greater<LL > > q;//保存所有生成的丑数

    s.insert(1);//最小的丑数
    q.push(1);

    LL smallist;
    int a[3] = {2,3,5};//用来生成丑数
    for(int i = 1;i <= 1500;i++)
    {
        smallist = q.top();
        q.pop();
        for(int i = 0;i<3;i++)
        {
            LL tmp = smallist*a[i];
            if(s.count(tmp) == 0) 
            {
                s.insert(tmp);
                q.push(tmp);
            }
        }
    }
    printf("The 1500'th ugly number is %lld.\n",smallist);
    return 0;
}

