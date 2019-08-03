#include <iostream>
using namespace std;
int main()
{
    int k,a,b;
    cin >> k >> a >> b;
    int ans = a/k + b/k;
    if(a%k > 0 && b/k < 1) ans = -1;
    if(b%k > 0 && a/k < 1) ans = -1;
    cout << ans << endl;
    return 0;
}

