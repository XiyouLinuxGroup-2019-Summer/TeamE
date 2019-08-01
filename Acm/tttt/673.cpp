#include<iostream>
#include<string.h>
#include<stack>

using namespace std;

stack<char> q;
char a[130];
int main()
{
	int t;
	cin >> t;
	getchar( );
	while(t--)
	{
		cin.getline(a,130);
		int len = strlen(a);
		if(len == 0)
		{
			puts("Yes");
			continue;
		}
		if(len%2 == 1)
		{
			puts("No");
			continue;
		}
		int flag = 0;
		for(int i = 0;i < len;i++)
		{
			if(a[i] == '[' || a[i] == '(')
			{
				q.push(a[i]);
			}
			else if(a[i] == ']' && !q.empty( ))
			{
				if(q.top() != '[')
				{
					flag = 1;
					break;
				}
				q.pop();
			}
			else if(a[i] == ')' && !q.empty( ))
			{
				if(q.top() != '(')
				{
					flag = 1;
					break;
				}
				q.pop();
			}
			else 
			{
				flag = 1;
				break;
			}
		}

		if(flag == 0 && q.empty())  puts( "Yes");
		else puts("No");

		while(!q.empty())  q.pop( );
	}
}
