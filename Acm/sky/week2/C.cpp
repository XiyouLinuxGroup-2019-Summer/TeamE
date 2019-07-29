#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 1000+100;
int main()
{
    int n = 0;
    int a[MAX];
    while(1)
    {
        char ch;
        cin >> a[n++];
        scanf("%c",&ch);
        /* cout << ch << endl; */
        if(ch == '\n') break;
    }

    sort(a,a+n);
    int ans = 0;
    int num = unique(a,a+n)-a;
    int l ,r ;
    for(int i = 0;i<num;i++)
    {
        int cnt = 0;
        l = i;
        for(int j = i+1;j<num;j++)
        {
            r = j;
            if(r - l == 1)
            {
                cnt++;
                continue;
            }
            else 
            {
                if(cnt == 0)
                {
                    if(ans == 0)
                    {
                        printf("%d",l);
                        ans++;
                        break;
                    }
                    
                }
            }

        }
    }
    return 0;
}

