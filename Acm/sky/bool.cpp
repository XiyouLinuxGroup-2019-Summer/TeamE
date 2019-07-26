#include <iostream>
using namespace std;
bool iftrue(int a,int b)
{
    if(a > b) return true;
    else return false;
}
int main()
{
    int a,b;
    cin >> a >> b;
    if(iftrue(a,b))
    {
        cout << "Yes,a is bigger than b!" << endl;
    }
    else 
        cout << "False!\n" << endl;
    return 0;
}

