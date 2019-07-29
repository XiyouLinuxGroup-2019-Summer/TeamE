#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef struct homework
{
    int ttime;
    int score;
}homework;
bool cmp(homework a,homework b)
{
    return a.score > b.score;
}
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        vector <int > v;
        int n;
        int ans = 0;
        cin >> n;
        homework hk[n];
        int sum = 0;
        for(int i = 0;i<n;i++)
        {
            cin >>hk[i].ttime; 
        }
        for(int i = 0;i<n;i++)
        {
            cin >> hk[i].score;
            sum += hk[i].score;
        }
        sort(hk,hk+n,cmp);
            
        vector<int >::iterator it;
        for(int i = 0;i<n;i++)
        {
           for(int j  = hk[i].ttime;j>0;j--)
           {
               if((it = find(v.begin(),v.end(),j)) == v.end())
               {//找不到到该时间
                    v.push_back(j);
                    ans += hk[i].score;
                    break;
               }
           }
        }
        
        cout << sum - ans << endl;

        


    }
    return 0;
}

