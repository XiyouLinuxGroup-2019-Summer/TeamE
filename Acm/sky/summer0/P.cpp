#include <iostream>
#include <string>
#include <algorithm>
#include <set>
using namespace std;
int main()
{
    int flag = 1;
    string s;
    cin >> s;
    set <char > Set;
    /* sort(s.begin(),s.end()); */
    /* int len  =  unique(s.begin(),s.end())-s.begin(); */
    /* string ans(s,0,len); */
    /* /1* cout << ans << endl; *1/ */
    /* for(int i = 1;i<len;i++) */
    /* { */
    /*     if(s[i] != s[i-1]+1){ */
    /*         flag = 0; */
    /*         break; */
    /*     } */
    /* } */
    char key = 'a';
    for(int i = 0;i<(int)s.size();i++)
    {
        if(Set.count(s[i]) != 0) continue;
        else{
            if(s[i] == key){
                Set.insert(s[i]);
                key++;

            }
            else{
                flag = 0;break;
            }
        }
    }
    if(flag) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}

