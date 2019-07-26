#include <iostream>
#include <algorithm>
using namespace std;
typedef struct aa
{
    int x;
}aa;
bool cmp(int a,int b)
{
    return a > b;
}

int main()
{
    int a[5];
    for(int i = 0;i<5;i++)
        cin >> a[i];
    sort(a,a+5,cmp);
    for(int i = 0;i<5;i++)
        cout << a[i] << endl;
    cout << "------" << endl;
    int size = unique(a,a+5)-a;
    for(int i = 0;i<size;i++)
        cout << a[i] << endl;
    return 0;
}

