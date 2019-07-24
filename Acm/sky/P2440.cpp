#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector <int> v;
int n,k;
int woodnum(int m)
{
    int num = 0;
    for(int i = 0;i<(int)v.size();i++)
    {
       num += v[i]/m;
    }
    return num;
}
int binsearch(int x,int y)
{
    int m;
    while(x < y)
    {
        m = x+(y-x+1)/2;
        if(woodnum(m) >= k) x = m;
        else y = m-1;
    }
    return x;
}
int main()
{
    cin >> n >> k;
    for(int i = 0;i<n;i++)
    {
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }
    cout << binsearch(0,*max_element(v.begin(),v.end())) << endl;
    return 0;
}

