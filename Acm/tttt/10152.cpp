#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

char a[210][100];
char b[210][100];
int main()
{
	int t;
	scanf( "%d",&t);
	while(t--)
	{
		int n;
		scanf( "%d",&n);
		getchar( );
		for(int i = 0;i < n;i++)   cin.getline(a[i],100);
		for(int i = 0;i < n;i++)   cin.getline(b[i],100);

		int i = n-1,j = n-1;
		while(i >= 0)
		{
			if(strcmp(a[i],b[j]) == 0)  j--;
			i--;
		}

		for(int k = j;k >= 0;k--)
		{
			puts(b[k]);
		}
		printf( "\n");
	}


	return 0;
}
