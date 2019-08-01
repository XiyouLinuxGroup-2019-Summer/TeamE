#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
using namespace std;
typedef struct node 
{
    int x;
    int y;
}node;
int main()
{
    int k;
    vector<node> v;
    while(cin >> k)
    {
        v.clear();
        for(int y = k;y <= 2*k;y++)
        {
            if(y-k != 0 &&(y*k)%(y-k) == 0)
            {
                int res = (y*k)/(y-k);
                node tmp;
                tmp.x = y;
                tmp.y = res;
                v.push_back(tmp);
            }
        }

        cout << v.size() << endl;
        for(int i = 0;i<(int)v.size();i++)
            printf("1/%d = 1/%d + 1/%d\n",k,v[i].y,v[i].x);
            
    }

    return 0;
}

