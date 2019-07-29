#include <iostream>
using namespace std;
int main()
{
    int k;
    cin >> k;
    if(k > 36 ) printf("-1");
    else
    {
        if(k%2 != 0)
        {
            k--;
            printf("9");
        }
        for(int i = 0;i<k;i+=2)
        {
            printf("8");
        }    
    }
    return 0;
}

