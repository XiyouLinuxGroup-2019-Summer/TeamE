#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    vector <int > v;
    int n,m;
    cin  >> n >> m;
    for(int i = 0;i<n;i++)
    {
        int tmp; cin >> tmp;
        if(tmp < 0) v.push_back(tmp); 
    }
    sort(v.begin(),v.end());
    int cnt = 0,ans = 0;
    for(int i = 0;i<(int)v.size() && cnt < m;i++)
    {
        ans += (-v[i]);
        cnt++;
    }

    cout << ans << endl;
    return 0;
}

