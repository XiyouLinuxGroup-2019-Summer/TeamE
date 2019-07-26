#include <iostream>
#include <vector>
using namespace std;
vector <int > v;
int main()
{
    for(int i = 0;i<5;i++)
    {
        int t;
        cin >> t;
        v.push_back(t);
    }
    /* v.clear(); */
    for(int i = 0;i<v.size();i++)
    {
        cout << v[i] << endl;
    }
    if(!v.empty()) printf("...\n");
    return 0;
}

