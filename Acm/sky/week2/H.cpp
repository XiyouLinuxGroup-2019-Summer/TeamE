#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef struct a
{
    int start;
    int end;
}a;
bool cmp(a a1,a b1)
{
    return a1.end < b1.end;
}
int main()
{
    int n;
    while(1){
    cin >> n;
    if(n == 0) break;
    a arr[n];
    for(int i = 0;i<n;i++)
        cin >> arr[i].start >> arr[i].end ;

    /* int zero; */
    /* cin >> zero ; */
    /* cout << endl; */
    sort(arr,arr+n,cmp);
    /* for(int i = 0;i<n;i++) */
        /* cout << arr[i].start << " " << arr[i].end << endl; ; */
    
    int ans = 0;
    
    int ed = -1;
    for(int i = 0;i<n;i++)
    {
        if(arr[i].start >= ed  )
        {
            ans++;
            ed = arr[i].end;
            /* cout << arr[i].start << " " << arr[i].end << endl; ; */
        }
    }
    
    printf("%d\n",ans);
    }
    return 0;
}

