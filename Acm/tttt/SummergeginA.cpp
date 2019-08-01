#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

int lcm(int a,int b)
{
	return a*b/__gcd(a,b);
}
int main( )
{
	int a,b;
	cin >> a >> b;
	printf( "%d\n",lcm(a,b));
}
