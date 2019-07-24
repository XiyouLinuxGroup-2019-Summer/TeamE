#include <iostream>
#include <memory.h>
using namespace std;
int type[100+1000];
int main()
{
    int cnt = 0;
    int a[1000+100];
    int n,k;
    cin >> n >> k;
    memset(type,0,sizeof(type));
    for(int i= 0;i<n;i++)
    {
        cin >> a[i];
        type[a[i]]++;
    }
    for(int i = 1 ;i<=1000;i++)
    {
        cnt += (type[i]%2);
        /* cout << cnt << i << endl; */
    }
    if(cnt%2!=0) cnt--;
    cnt /= 2;
    cout << n-cnt << endl;
    return 0;
}

