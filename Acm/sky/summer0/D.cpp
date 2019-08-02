#include <iostream>
#include <vector>
#include <string>
#include <queue>
#define N 60
using namespace std;
vector <string> v;
int a[60];
int main()
{
    int n,k;
    cin >> n >> k;
    //先生成50个名字
    for(int i = 0;i < 25 ;i++)
    {
        for(int j = 0;j < 25;j++)
        {
            string s  = "ABC"; 
            s[0] = 'A';
            s[1] = char(98+j);
            s[2] = char(98+i);
            v.push_back(s);
        }
    }

    int key = 0;
    for(int i = 1;i<=k-1;i++){
        key = i;
        a[i] = i;
    }

    for(int i = k;i<=n;i++){
        string input;
        cin >> input;
        if(input == "YES") a[i]=++key;
        else a[i] = a[i-k+1];
    }

    for(int i = 1;i<=n;i++)
    {
        cout << v[a[i]] << " ";
    }


    return 0;
}

