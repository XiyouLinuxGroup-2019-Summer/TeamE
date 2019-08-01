#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n,k;
    cin >> n >> k;
    string sstd = "abcdefghijklmnopqrstuvwxyz";
    string mmin = "ab";
    string ans;
    int times = n/2+1;
    for(int i = 0;i<times;i++)
    {
        ans += mmin;
    }
    int kinds = k - 2;
    if(kinds == 0)
    {
        ans = ans.substr(0,n);
    }
    else 
    {//两种以上 长度肯定大于2
        ans = ans.substr(0,n-kinds)+sstd.substr(2,kinds);
        ans = ans.substr(0,n);
    }

    cout << ans << endl;
    /* cout << ans.size() << endl; */
    return 0;
}

