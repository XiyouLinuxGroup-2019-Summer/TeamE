#include <iostream>
#include <set>
using namespace std;
int f(set <int > x)
{
    x.count(3);
    return 0;
}
int main()
{
    f(set <int > ());
    return 0;
}

