#include <iostream>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int flag = 0;
        for(int i = 0;i<n;i++){
            int tmp;
            cin >> tmp;
            flag ^= tmp;
        }

    }
    return 0;
}

