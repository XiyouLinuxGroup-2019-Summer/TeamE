#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int main()
{
    int cnt = 0;
    int n,t;
    while(1)
    {
        cin >> n >> t;
        if(!n && !t) break;
        cnt++;
        cout << "CASE# " << cnt << ":" << endl;
        int a[n],ask;
        for(int i = 0;i<n;i++)
            cin >> a[i];
        sort(a,a+n);
        /* for(int i = 0;i<n;i++) */
            /* cout <<  a[i]; */
        for(int i = 0;i<t;i++)
        {
            cin >> ask ;
            int p = lower_bound(a,a+n,ask)-a;
            /* cout << p << endl; */
            /* cout << a[p] << endl; */
            if(a[p] == ask) 
            {
                cout << ask << " found at " << p+1  <<endl;
            }
            else 
            {
                cout << ask << " not found" <<endl;
            }
        }
    }
    return 0;
}

