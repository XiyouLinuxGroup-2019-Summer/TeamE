#include <iostream>
#include <math.h>
using namespace std;
typedef long long LL;
LL n,k;
LL ans(LL b,LL c)
{
    /* LL sum = (n)*(n-1)/2; */
    LL q = b*b-4*c;
    /* cout << q << endl; */
    /* cout << sqrt(q) << endl; */
    LL ans1 = (-b-sqrt(q))/2;
    /* LL ans2 = (-b+sqrt(q))/2; */
    /* cout << ans1 << endl << ans2 << endl << sum << endl; */
    /* if(ans1 < n) return ans1; */
    /* else return ans2; */
    return ans1;
}
LL f(int n)
{
    return n*(n+1)/2;
}
int main()
{
    cin >> n >> k;
    LL b = -(2*n+3),c = n+n*n-2*k;
    /* int i; */
    /* int sum = f(n); */
    /* for(i = n;i>=0;i--) */
    /* { */
    /*     if(sum == k ) */
    /*     { */
    /*         break; */
    /*     } */
    /*     sum -= i;sum--; */

    /* } */
    /* cout << n-i << endl; */
    
    /* cout << b << "sssss" << c <<endl; */
    cout << ans(b,c) <<endl;
    return 0;
}

