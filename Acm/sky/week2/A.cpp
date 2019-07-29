#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    double per = 1000;
    double a,b;
    int n;
    int m;
    cin >> n >> m;
    while(n--)
    {
        cin >> a >> b;
        double tmp = a/b;
        if(tmp < per) per = tmp;
    }
    printf("%.8lf",per*m);
    
    return 0;
}

