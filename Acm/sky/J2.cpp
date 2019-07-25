#include <iostream>
#define LL long long 
using namespace std;
#define cal(x) (x)*(x+1)/2
LL binsearch(LL x,LL y,LL key)
{
    LL m;
    while(x < y)
    {
        m = x+(y-x+1)/2;
        LL res = cal(m);
        if(res == key) return res;
        else if(res > key) y = m-1;
        else if(res < key) x = m;
    }
    return (cal(x));
}
int main()
{
    int t;
    cin >> t;
    int i = 1;
    while(t--)
    {
        /* Case #3: 3 */
       LL num;
       cin >> num;
        LL ans = binsearch(1,2e9,num);
        cout << "Case #" << i++ << ": " << ans << endl;
    }
    return 0;
}

