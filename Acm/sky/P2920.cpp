#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef  struct thing
{
    int last;
    int deadline;
}thing;
vector <thing > v;
int t;
bool cmp(thing a,thing b)
{
    return a.deadline<b.deadline;
}
int judge(int m)
{
    int cur_time = m;
    for(int i = 0;i<(int)v.size();i++)
    {
        if(cur_time+v[i].last > v[i].deadline) return 0;
        cur_time += v[i].last;
    }
    return 1;
}
int binsearch(int x,int y)
{
    int m;
    while(x < y)
    {
        m = x+(y-x+1)/2;
        if(judge(m) == 0) y = m-1;
        else x = m;
    }
    return x;
}
int main()
{
    cin >> t;
    for(int i = 0;i<t;i++)
    {
        thing tmp;
        cin >> tmp.last >> tmp.deadline;
        v.push_back(tmp);
    }

    sort(v.begin(),v.end(),cmp);

    /* for(int i = 0;i<(int)v.size();i++) */
    /*     cout << v[i].deadline << endl; */

    cout << binsearch(-1,v[0].deadline-1) << endl;
    return 0;
}

