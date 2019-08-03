#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int a[n+10];
    for(int i = 1;i<=n;i++){
        cin >> a[i];
    }
    for(int i = 1;i<=n/2;i++){
        if(i%2 == 0) continue;
        int t = a[i];
        a[i] = a[n-i+1];
        a[n-i+1] = t;
    }
    for(int i = 1;i<=n;i++){
        cout << a[i] <<  " ";
    }
    return 0;
}

