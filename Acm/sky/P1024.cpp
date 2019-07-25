#include <iostream>
#include <iomanip>
using namespace std;
#define f(x) (a*x*x*x+b*x*x+c*x+d)
int main()
{
    double a,b,c,d;
    cin >> a >> b >> c >> d;
    int cnt = 0;//cnt = 3 剪枝
    for(int i = -100;i<=100;i++)
    {
        double x = i;
        double y = i+1;//枚举区间
        if(!f(x)) 
            {
                cnt++;
                cout << fixed << setprecision(2) << x << " ";
            }

        if(f(x)*f(y) < 0)//这个区间内有根
        {
            double  m ;
            while(y-x >= 0.001)
            {
                m = (x+y)/2;
                /* m = y+(y-x)/2; */
                if(f(m) * f(y) <= 0) x = m;
                else y = m;
            }
                cnt++;
                cout << fixed << setprecision(2) << x << " ";
        }
        if(cnt == 3) break;
    }
    return 0;
}

