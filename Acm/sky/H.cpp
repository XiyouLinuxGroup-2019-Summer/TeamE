#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector <int> v;
int main()
{
    /* int first2[16000000]; */
    int a[4050],b[4050],c[4050],d[4050];
    int t;
    int ans = 0;
    cin >> t;
    for(int i = 0;i<t;i++)
    {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }

    int k = 0;
    for(int i = 0;i<t;i++)
    {
        for(int j = 0;j<t;j++)
        {
            v.push_back(a[i]+b[j]);k++;
        }
    }
    sort(v.begin(),v.end());
    
    /* printf("size = %d\n",(int)v.size()); */
    for(int i = 0;i<t;i++)
    {
        for(int j = 0;j<t;j++)
        {
            int tmp =   -c[i] - d[j];
            int x = lower_bound(v.begin(),v.end(),tmp)-v.begin();
            int y = upper_bound(v.begin(),v.end(),tmp)-v.begin();
            /* if(y-x > 0)printf("y-x = %d ---   %d %d\n",y-x,c[i],d[j]); */
            ans += (y-x);
        }
    }

    cout << ans << endl;
    return 0;
}

