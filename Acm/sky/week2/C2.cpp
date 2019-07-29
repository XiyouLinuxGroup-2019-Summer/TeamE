#include <iostream>
using namespace std;
int main()
{
    int n,d;

    cin >> n >> d;
    int ans = 0;
    int tmp = 0;
    int flag= 0;
    for(int i= 0;i<d;i++)
    {
        flag = 0;
        string s;
        cin >> s;
        for(int i = 0;i<(int)s.size();i++)
        {
            if(s[i] == '0') 
            {
                tmp++;
                if(ans < tmp) ans = tmp;
                flag = 1;
                break;
            }
        }
        if(flag == 0) tmp = 0; 
    }
    cout << ans << endl;
    return 0;
}

