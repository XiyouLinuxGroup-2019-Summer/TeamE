#include<iostream>
#include<cstdio>
using namespace std;

int main( )
{
	int a1,a2,a3,a4,a5,a6;
	while(cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6)
	{
		int sum = 0;
		sum = a4 + a5 + a6;
		if( !a1 && !a2 && !a3 && !a4 && !a5 && !a6)	break;

		if(a5)	a1 = a1 - (11*a5);
		if(a4)
		{
			int temp = a4*20;
			if(a2*4 >= temp)
			{
				a2 = a2 - (a4*5);
			}
			else
			{
				a1 = a1 - (temp - (a2*4));
				a2 = 0;
			}
		}

		int temp = a3/4;
		sum += temp;
		temp = a3%4;

		if(temp)
		{
			sum += 1;
			int leve = 36 - 9*temp;
			if(temp == 1)
			{
				int temp1 = min(a2,5);
				leve = leve - (temp1*4) ;
				a2 -= temp1;
				a1 -= leve;
			}
			else if(temp == 2)
			{
				int temp1 = min(a2,3);
				leve = leve - (temp1*4);
				a2 -= temp1;
				a1 -= leve;
			}
			else if(temp == 3)
			{
				int temp1 = min(a2,1);
				leve = leve - (temp1*4);
				a2 -= temp1;
				a1 -= leve; 
			}
		}
		if(a2 > 0)
		{
			temp = a2/9;
			sum += temp;
			temp  = a2%9;
			if(temp)
			{
				sum += 1;
				int temp1 = 36 - 4*temp;
				a1 -= temp1;
			}
		}
		if(a1 > 0)
		{
			temp = a1/36;
			sum += temp;
			temp = a1%36;
			if(temp)
			{
				sum += 1;
			}
		}

		cout << sum << endl;
	}

	return 0;
}


