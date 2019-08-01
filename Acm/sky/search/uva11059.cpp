#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;
int main()
{
    int first = 1;
    LL n;
    LL cnt = 0;
    while(cin >> n)
    {
        cnt++;
        LL ans = -1;
        int a[n];
        for(int i = 0;i<n;i++)
            cin >> a[i];

        for(int i = 0;i<n;i++)
            for(int j = i;j<n;j++)
            {
                LL sum = 1;
                for(int k = i;k<=j;k++)
                {
                    sum *= a[k];

                }
                if(sum>ans) ans = sum;

            }
        if(ans < 0) ans = 0;
        printf("Case #%lld: The maximum product is %lld.\n\n",cnt,ans); 
    }
    return 0;
}

