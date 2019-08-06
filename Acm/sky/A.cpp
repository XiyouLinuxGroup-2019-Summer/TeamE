#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int t;
    cin >> t;
    char *ans;
    for(int i = 1;i<=t;i++){
        int n,k;
        cin >> n >> k;
        if(k == 1){
            if(n%2 == 0) ans = "second";
            else ans = "first";
        }
        else if(k>=n) ans = "first";
        else ans = "second";
        printf("Case %d: %s\n",i,ans);
    }
    return 0;
}

