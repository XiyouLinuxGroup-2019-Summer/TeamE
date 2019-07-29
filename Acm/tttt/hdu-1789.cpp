#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;
struct node
{
	int time;
	int score;
};
struct node a[1005];
int book[1005];
int cmd(struct node x,struct node y)
{
	//if(x.time > y.time)   return x.time < y.time;
	//else if(x.time == y.time)
	//{
		return x.score > y.score;
//	}

	return 0;
}
int main( )
{
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		int sum = 0;
		cin >> n;
		for(int i = 1;i <= n;i++)   cin >> a[i].time;
		for(int i = 1;i <= n;i++)   cin >> a[i].score;
		sort(a+1,a+n+1,cmd);
		
/*		for(int i = 1;i <= n;i++)
		{
			if(a[i].time >= i)
		}

		for(int i = 1;i < n;i++)
		{
			if(a[i].time != a[i+1].time)
			{
				book[i] = 1;
			}
		}
		book[n] = 1;
		int temp;
		for(int i = n;i >= 1;i--)
		{
			if(book[i] == 0)
			{
				for(int j = i-1;j >=1;j--)
				{
					if(book[j] == 1)
						if(a[i].score > a[j].score)	
						{
							book[i] == 1;
							book[j] == 0;
						}
				}

			}
		}
		int sum = 0;
		for(int i = 1;i <= n;i++)
		{
			if(book[i] == 0)  sum += (a[i].score);
		}
		*/
		memset(book,0,sizeof(book));

		int j;
		for(int i = 1;i <= n;i++)
		{
			for(j = a[i].time;j >= 1;j--)
			{
				if(book[j] == 0) 
				{
					book[j] = 1;
					break;
				}
			}

			if(j <= 0)   sum += a[i].score;
		}
		cout << sum << endl;
	}

	return 0;
}
