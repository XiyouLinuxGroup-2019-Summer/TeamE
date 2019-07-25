#include <iostream>
using namespace std;
int v = 8;
int big(int x,int y,int *a)
{
    int m;
    while(x < y)
    {
        m = x+(y-x+1)/2;
        if(a[m] <= v) x = m;
        else y = m-1;
    }
    return x;
}
int main()
{
    int a[10] = {0,1,2,3,4,5,8,8,8,9};
    int ans = big(0,9,a);
    cout << ans << endl;
    return 0;
}

