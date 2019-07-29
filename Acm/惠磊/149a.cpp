#include<iostream>
#include<algorithm>

using namespace std;
int cmp(int a,int b)
{
	return a>b;
}
int a[17];
int main( )
{
	int sum;
	cin >> sum;
	for(int i = 1;i <= 12;i++)   cin >> a[i];
	sort(a+1,a+12+1,cmp);

	int cnt = 0;
	int i = 1;
	while(sum > 0)
	{
		sum -= a[i];
		i++;
		cnt++;
		if(i > 12)  break;
	}
	if(sum <= 0)
		cout << cnt << endl;
	else cout << -1 << endl;
}
