#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;

struct node
{
	int kilos;
	int money;
	double effect;
};
struct node a[5005];

int cmp(struct node a , struct node b)
{
	return a.effect < b.effect;
}
int main( )
{
		int sum,n;
		cin >> n >> sum;
		long double get = 0;
		for(int i = 1;i <= n;i++)
		{
			cin >> a[i].money >> a[i].kilos;
			a[i].effect = (1.0*a[i].money) / (1.0*a[i].kilos);
		}

		sort(a+1,a+1+n,cmp);
		get = a[1].effect * sum;

		printf( "%.8llf\n",get);


}
