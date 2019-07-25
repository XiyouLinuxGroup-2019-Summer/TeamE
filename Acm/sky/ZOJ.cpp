#include <iostream>
#define N 200100
using namespace std;
int t,n,k;
int judge(int m,char *light)
{
    int cnt = 0;
    for(int i = 0;i<n;)
    {
        if(light[i] == '0')
        {
            i++;
            continue;
        }
        else
        {
            cnt++;
            i += m;
        }

    }
    return cnt;
}
int binsearch(char *light)
{
    int x = 1,y = n;
    int m;
    while(x < y)
    {
        m = (x+y)/2;
        if(judge(m,light) <= k) y = m;
        else  x = m+1;
    }
    return x;
}
int main()
{
    cin >> t;
    while(t--)
    {
        char light[N];
        cin >> n >> k;
        for(int i = 0;i<n;i++)
        {
            cin >> light[i] ;
        }
        cout << binsearch(light) << endl;
    }
    return 0;
}

