//并查集


#include<iostream>
#include<algorithm>
#include<stdio.h>

using namespace std;

int co[100005];
int pre[100005];

void join(int a,int b);
int find(int a);

int main()
{

	int n,m;
	long long sum = 0;
	cin >> n >> m;
	for(int i = 1;i <= n;i++)
	{
		pre[i] = i;
		cin >> co[i];
	}
	int a,b;
	for(int i = 1;i <= m;i++)
	{
		cin >> a >> b;
		join(a,b);
	}

	for(int i = 1;i <= n;i++)
	{
		if(pre[i] == i)   sum += co[i];
	}

	cout << sum << endl;
}

void join(int a,int b)
{
	int x = find(a);
	int y = find(b);

	if(x == y)   return ;
	if(co[x] > co[y])   pre[x] = y;   //让 花费 小的做上级    x 的上级 是 y
	else  pre[y] = x;
}

int find(int a)
{

	if(pre[a] == a)   return a;
	else 
	{
		return pre[a] = find(pre[a]);   //递归寻找上级
	}
}
