#include<iostream>

using namespace std;

char b[105];

int main( )
{
	char a[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	int num = 0;
	int n,k;
	cin >> n >> k;
	for(int i = num;i < k;i++)
	{
		b[num] = a[i];
		num++;
	}
	int temp = n-k;
	if(temp == 0)	printf( "%s\n",b);
	else 
	{
		int temp2 = temp/k;
		if(temp2 > 0)
		{
			for(int i = 0;i < temp2;i++)
			{
				for(int j = 0;j < k;j++)
				{
					b[num] = a[j];
					num++;
				}
			}
			int temp3 = temp%k;
			if(temp3)
			{
				for(int i = 0;i < temp3;i++)
				{
					b[num] = a[i];
					num++;
				}
				printf( "%s\n",b);
			}
			else 	printf( "%s\n",b);
		}
		else 
		{
			int temp3 = temp%k;
			if(temp3)
			{
				for(int i = 0;i < temp3;i++)
				{
					b[num] = a[i];
					num++;
				}
				printf( "%s\n",b);
			}
			else 	printf( "%s\n",b);
		}
	}
	return 0;

}
