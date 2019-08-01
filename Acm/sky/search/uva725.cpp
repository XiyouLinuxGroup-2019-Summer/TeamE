#include <iostream>
#include <cstdio>
using namespace std;
int a,b,c,d,e;
int judge(int another)
{
    int num[6],i = 1;
    if(another/10000 >= 10) return 0;
    while(another)
    {
        num[i++] = another%10;
        another /= 10;
    }
    for(int j = 1;j<6;j++)
    {
        if(num[j] == a || num[j] == b || num[j] == c || num[j] ==d || num[j] == e) return 0;
        for(int k = j+1;k<6;k++)
        {
            if(num[j] == num[k] )
            {
                return 0;
            }
        }
    }
    return 1;
}
int main()
{
    int first = 1;
    int m;
    int n[2];
    while(cin >> m )
    {
        
        if(first)
        {
            if(m == 0) break;

            first = 0;
            n[0] = m;n[1] = m;continue;
        }
        n[0] = n[1];
        n[1] = m;
        int flag = 0;
        for(a = 0;a<10;a++)
        {
            for(b = 0;b<10;b++)
            {
                if(b!= a)
                for(c = 0;c < 10;c++)
                {
                    if(c !=b && c!= a)
                    for(d = 0;d < 10;d++)
                    {
                        if(d!= c && d != b && d != a)
                        for(e = 0;e<10;e++)
                        {
                            if(e != d && e!= c && e != b && e != a)
                            {
                            int res = a*10000+b*1000+c*100+d*10+e;
                            int another = n[0]*res;
                            if(judge(another))
                            {
                                flag = 1;
                                printf("%d / %d%d%d%d%d = %d\n",another,a,b,c,d,e,n[0]);
                            } 
                            
                        }
                    }
                }
            }
        }}

        if(n[1] != 0)
        {
            printf("\n");
        }
        else break;
        if(flag == 0) printf("There are no solutions for %d.\n",n[0]);
    }
    return 0;
}

