#include <iostream>
int a1,a2,a3,a4,a5,a6;
using namespace std;
int main()
{
    while(cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6)
    {
        int sum = 0;
        if(!a1 && !a2 && !a3 && !a4 && !a5 && !a6)
            break;

        sum += a6;
        
        if(a5 > 0)
        {
            sum += a5;
            a1 -= 11*a5;
        }

        if(a4 > 0)
        {
            sum += a4;
            int cancontaina2 = 5*a4;
            if(a2 > 0 && a2 == cancontaina2) a2 = 0;
            else if(a2 > 0 && a2 > cancontaina2) a2 -= cancontaina2;
            else if(a2 > 0 && a2 < cancontaina2)
            {//用来填充a2+a1
                a1 -= (a4*36-a4*16-a2*4);
            }
            else if(a2 <= 0) a1 -= (a4*36-a4*16);
        }

        if(a2 < 0) a2 = 0;
        
        if(a3 > 0)
        {
            if(a3%4 == 0) 
            {
                sum += a3/4;
            }
            else //不满
            {
                sum += (a3/4+1);
                int leave3 = a3%4;
                if(leave3 == 3)
                {
                    if(a2 > 0) 
                    {
                        a2--;
                        a1 -= 5;
                    }
                    else a1 -= 9;
                }
                else if(leave3 == 2)
                {
                    if(a2 >= 3)
                    {
                        a2 -= 3;
                        a1 -= 6;
                    }
                    else if(a2 == 2)
                    {
                        a2 -= 2;
                        a1 -= 10;
                    }
                    else if(a2 == 1)
                    {
                        a2 -= 1;
                        a1 -= 14;
                    }
                    else a1 -= 18;
                }
                else if(leave3 == 1)
                {
                    if(a2 >= 5) a2 -= 5;
                    else if(a2 > 0 ) 
                    {
                        a1 -= (27-a2*4);
                        a2 = 0;
                    }
                    else a1 -= 27;
                }
            }
            
        }

        if(a2 < 0) a2 = 0;

        if(a2 > 0 && a2%9 == 0) 
        {
            sum += a2/9;
        }
        else if(a2 > 0 && a2%9 != 0)
        {
            sum += a2/9+1;
            a1 -= (36-a2*4);
        }

        if(a1 >0 && a1%36 == 0)
        {
            sum += a1/36;
        }
        else if(a1>0 && a1%36 != 0)
        {
            sum += 1;
        }

        cout << sum << endl;
        
    }
    return 0;
}

