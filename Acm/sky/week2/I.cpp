#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;
typedef struct table
{
    int start;
    int end;
    int last;
    int tag;
}table;
int a[210];
bool cmp(table a,table b)
{
    return a.last < b.last;
}
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        memset(a,0,sizeof(a));
        for(int i = 0;i<n;i++)
        {
            int n,m;
            cin >> n >> m;
            if(n > m) 
            {
                int t = n;
                n  = m;
                m = t;
            }
            if(n%2 == 0 ) n--;
            if(m%2 == 0)    m--;
            for(int j = n;j<=m;j+=2)
            {
                a[j]++;
            }
        }
        cout << *max_element(a,a+210)*10 << endl;



    }
    return 0;
}

