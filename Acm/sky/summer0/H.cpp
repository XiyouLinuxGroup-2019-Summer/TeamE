#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int a[n];
    for(int i = 0;i<n;i++){
        cin >> a[i];
    }
    sort(a,a+n);
    int _max = *max_element(a,a+n);
    int _min = *min_element(a,a+n);

    int ans = 0;
    for(int i = 0;i<n;i++)
    {
        if(a[i] != _max && a[i] != _min) ans++;
    }

    cout << ans << endl;


    return 0;
}

