#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef struct a
{
    double a;
    double b;
    double per;
}a;
bool cmp(a x,a y)
{
    return x.per >  y.per;
}
int main()
{
    int n,m;
    while(cin >> m >> n)
    {
        double ans = 0;
        if(n == -1 && m == -1) break;
        a  aa[n];
        for(int i = 0;i < n;i++)
        {
            cin >> aa[i].a >> aa[i].b;
            aa[i].per = aa[i].a/aa[i].b;
        }
        sort(aa,aa+n,cmp);
        /* for(int i = 0;i < n;i++) */
        {
            /* cout <<  aa[i].per << endl; */
        }

        for(int i = 0;i<n;i++)
        {
            if(m >= aa[i].b)  
            {
                ans += aa[i].a;
                m -= (aa[i].b); 
            }
            else 
            {
                ans += (m/aa[i].b)*aa[i].a;
                m = 0;
            } 
        }
        printf("%.3lf\n",ans);

    }
    return 0;
}

