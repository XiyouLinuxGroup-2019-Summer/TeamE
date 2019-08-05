#include <iostream>
using namespace std;
typedef long long LL;
int main()
{
    LL n,k;
    cin >> n >> k;
    if((n/k)%2 == 0) cout << "NO" << endl;
    else cout << "YES" << endl;
    return 0;
}

