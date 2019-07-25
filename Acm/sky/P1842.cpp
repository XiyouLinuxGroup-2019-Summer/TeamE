#include <iostream>
#include <algorithm>
#define N 100000+100
using namespace std;
int n,c;
int a[N];
int judge(int m)
{
    int cnt = 1;
    int key = a[0];
    for(int i = 0;i < n;i++)
    {
        if(a[i] >= key+m) 
        {
            key = a[i];
            cnt++;
        }
    }
    return cnt;
}
int binsearch(int x,int y)
{
    int m;
    while(x < y)
    {
        m = x+(y-x+1)/2;
        if(judge(m) >= c) x = m;
        else y = m-1;
    }
    return x;
}
int main()
{
    cin >> n >> c;
    for(int i = 0;i<n;i++)
    {
        cin >> a[i] ;
    }
    sort(a,a+n);

    cout << binsearch(1,*max_element(a,a+n) - *min_element(a,a+n)) << endl;
    return 0;
}

