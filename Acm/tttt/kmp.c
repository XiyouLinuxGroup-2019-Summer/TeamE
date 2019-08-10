#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char text[1000005];
char pattern[10005];
int prefix[10005];

int n,m;

void prefix_table(char pattern[],int prefix[],int n)    //获取 next 数组
{
	prefix[0] = 0;   //第一位永远等于 0
	int len = 0;     //
	int i = 1;    //从第一个字母开始比较
	while(i < n)   // n 是
	{
		if(pattern[i] == pattern[len])
		{
			len++;
			prefix[i] = len;
			i++;
		}
		else
		{
			if(len > 0)
			{
				len = prefix[len - 1];   //斜 对应
			}
			else
			{
				prefix[i] = 0;  //此时 len  = 0,
				i++;
			}
		}
	}

	//for(int i = 0 ;i < n;i++)  printf( "%d\n",prefix[i]);
}

void move_prefix_table(int prefix[],int n)
{
	int i;
	for(i = n-1;i > 0;i--)
	{
		prefix[i] = prefix[i-1];
	}
	prefix[0] = -1;
}

void kmp_search(char text[],char pattern[])
{
	int flag = 0;
	int i = 0,j = 0;
	int num = 0;
	
	m = strlen(text);
	n = strlen(pattern);

	prefix_table(pattern,prefix,n);    //找到 next 数组
	move_prefix_table(prefix,n);     //将其前移 一位
	// i 代表 text  的下标,j 代表 pattern 数组的下表
	// m 是总个数,  n 是要查找的个数
	while(i < m)    //一直找到结束
	{
		if(j == n-1 && text[i] == pattern[j])
		{
			num++;
			flag = 1;
			j = prefix[j];
	//		break;
		}
		if(text[i] == pattern[j])
		{
			i++;
			j++;
		}
		else  //如果不相等,j 就等于 prefix[j]
		{
			j = prefix[j];  
			if(j == -1)
			{
				i++;
				j++;
			}
		}
	}

//	if(flag == 0)   printf( "-1\n");
	printf( "%d\n",num);
}

int main( )
{

//	char text[] = "ABABCABAAAAABBBAAABB";
//	char pattern[] = "ABABCABAA";
	int t;
	scanf( "%d",&t);
	while(t--)
	{
		memset(text,0,sizeof(text));
		memset(pattern,0,sizeof(pattern));
		memset(prefix,0,sizeof(prefix));
		scanf( "%s",pattern);
		scanf( "%s",text);

	//	printf( "%s\n",pattern);
	//	printf( "%s\n",text);


		kmp_search(text,pattern);
	}
	
	/*	int prefix[9];
	int n = 9;
	prefix_table(pattern,prefix,n);
*/
	return 0;
}
