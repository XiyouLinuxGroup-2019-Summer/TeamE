#include<iostream>
#include<algorithm>

using namespace std;
int a[5];

int main()
{
	int n;
	cin >> n;
	int temp;
	for(int i = 1;i <= n;i++)
	{
		cin >> temp;
		a[temp]++;
	}
	int max1 = max(a[1],a[2]);
	max1 = max(max1,a[3]);

	cout << n - max1 << endl;
}
