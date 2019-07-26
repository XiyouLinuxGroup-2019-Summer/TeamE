#include <iostream>
using namespace std;
void swap2(int &a,int &b)
{
    int t = a;
    a = b;
    b = t;
}
int main()
{
    int a,b;
    cin >> a >> b;
    cout << "a = " << a << " b = " << b << endl;

    swap2(a,b);

    cout << "a = " << a << " b = " << b << endl;
    
    return 0;
}

