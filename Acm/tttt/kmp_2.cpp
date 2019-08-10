#include<stdio.h>
#include<string.h>

int next[10010];
char str1[10010];
char str2[1000010];

void get_next()
{
	int i = 0,j = -1;
	int len = strlen(str1);   //获取str1  的长度
	next[0] = -1;
	while(i < len)
	{
		if(j == -1 || str1[i] == str1[j]) //如果是第一个  或这这俩相等
		{
			i++;
			j++;
			next[i] = j;
		}
		else j = next[j];
	}
}

int kmp()
{
	get_next();

	int i = 0,j = 0;
	int num = 0;

	int len1 = strlen(str1);
	int len2 = strlen(str2);

	while(i < len2)
	{
		if(j == -1 || str2[i] == str1[j])
		{
			i++;
			j++;
		}
		else	j = next[j];

		if(j == len1)   //如果 找到了 一个串
		{
			num++;
			j = next[j];   //回溯
		}

	}


	return num;
}
int main()
{
	int t;
	int sum;
	scanf( "%d",&t);

	while(t--)
	{
		memset(next,0,sizeof(next));
		memset(str1,0,sizeof(str1));
		memset(str2,0,sizeof(str2));
		
		scanf( "%s",str1);
		scanf( "%s",str2);

		sum = kmp();
		printf( "%d\n",sum);
	}

}
