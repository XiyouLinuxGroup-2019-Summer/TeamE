#include <iostream>
#define _MAX(a,b) a > b? a : b
using namespace std;
typedef long long LL;
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        LL ans ;
        LL a,b;
        LL p,q,x,y;
        cin >> x >> y >> p >> q;
        if(p != 0)
        {
            if(x%p == 0)
            {
                a = x/p;
            }
            else a = x/p+1;
        }
        if(p != q)
        {
            if((y-x)%(q-p) == 0)
            {
                b = (y-x)/(q-p);
            }
            else b = (y-x)/(q-p)+1;
        }
        if(p == q && x == y) ans = 0;
        else if(p == q && x != y) ans = -1;
        else if(p == 0 && x == 0) ans = 0;
        else if(p == 0 && x != 0) ans = -1;
        else ans = (_MAX(a,b))*q-y;

        cout << ans << endl;
    }
    return 0;
}

