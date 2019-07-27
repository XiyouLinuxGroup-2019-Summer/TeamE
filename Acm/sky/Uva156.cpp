#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
void change(string &s)
{
    for(int i = 0;i<(int)s.size();i++)
    {
        s[i] = tolower(s[i]); 
    }
    sort(s.begin(),s.end());
}
int main()
{
    string s;
    vector <string > word;
    vector <string > ans;
    map<string,int > mp;
    while(cin >> s)
    {
        if(s[0] == '#') break;
        word.push_back(s);
        change(s);
        if(mp.count(s) == 0) mp[s] = 0;
        mp[s]++;
    }

    //遍历word提取ans
    for(int i = 0;i<(int)word.size();i++)
    {
        string tmp = word[i];
        change(tmp);
        if(mp[tmp] == 1) ans.push_back(word[i]);
    }

    sort(ans.begin(),ans.end());

    for(int i = 0;i<(int)ans.size();i++)
    {
        cout << ans[i] << endl;
    }
    return 0;
}

