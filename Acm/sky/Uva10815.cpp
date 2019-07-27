#include <iostream>
#include <string>
#include <sstream>
#include <set>
using namespace std;
int main()
{
    set <string> dict;
    string s,ss,buf;
    
    dict.insert("abc");
    while(cin >> s)
    {
        for(int i = 0;i<(int)s.length();i++) 
            if(isalpha(s[i])) s[i] = tolower(s[i]);
            else s[i] = ' ';
        stringstream ss(s);
        while(ss >> buf)
        {
            dict.insert(buf);
        }
    }
    set<string>::iterator it = dict.begin();
    dict.erase("came");
    for(;it != dict.end();it++)
    {
        cout << *it << endl;
    }
    return 0;
}

