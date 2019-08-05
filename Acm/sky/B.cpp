#include <iostream>
using namespace std;
int main()
{
    int a,b;
    while(cin >> a >> b && a && b)
    {
        if(a < b){
            int t = a; a= b; b = t;
        }//交换保证a大

        int flag = 0;
        while(1){
            if(a%b == 0 || a/b>=2) break;
            flag ^= 1;
            a = a-b;
            if(a < b){
                int t = a;a = b;b = t;
            }
        }

        if(flag == 0) cout << "Stan wins" << endl;
        else cout << "Ollie wins" << endl;

    }
    return 0;
}

