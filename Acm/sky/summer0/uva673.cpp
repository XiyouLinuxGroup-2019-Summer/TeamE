#include <iostream>
#include <stack>
#define Y "Yes"
#define N "No"
using namespace std;
int judge(string s)
{
    if(s.size()%2 !=  0) return 0;
    stack<char > Stack;
    for(int i = 0;i<(int)s.size();i++)
    {
        if(Stack.empty())
        {
            if(s[i] == '(' || s[i] == '[')
            {
                Stack.push(s[i]);
            }
            else return 0;
        }
        else
        {
            if(s[i] == '(' || s[i] == '[') Stack.push(s[i]);
            else 
            {
                if(s[i] == ')')
                {
                    if(Stack.top() == '(')    Stack.pop();
                    else return 0;
                }
                else
                {
                    if(Stack.top() == '[') Stack.pop();
                    else return 0;
                }
            }
        }
    }
    if(Stack.empty())
        return 1;
    else return 0;
}
int main()
{
    int t;
    cin >> t;
    getchar();
    while(t--)
    {
        string ans;
        string s;
        getline(cin,s);
        if(s.size() == 0)
        {
            ans = Y;
        }
        else
        {
            if(judge(s)) ans = Y;
            else ans = N;
        }
        cout << ans << endl;
        
    }
    return 0;
}

