#include <iostream>
#include <algorithm>
using  namespace std;
int main()
{
    int n,m,z;
    cin >> n >> m >> z;
    int gcd = n*m/__gcd(n,m);
    cout << z/gcd << endl;
    return 0;
}

