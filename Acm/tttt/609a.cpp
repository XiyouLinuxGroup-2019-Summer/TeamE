#include<iostream>
#include<algorithm>

using namespace std;
int cmp(int a,int b)
{
	return a>b;
}
int a[105];
int main( )
{
	int n;
	cin >> n;
	int sum;
	cin >> sum;
	for(int i = 1;i <= n;i++)   cin >> a[i];

	sort(a+1,a+1+n,cmp);
	int cnt = 0;
	int i = 1;
	while(sum > 0)
	{
		sum -= a[i];
		i++;
		cnt++;
	}

	cout << cnt <<endl;
}
