#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;

typedef pair<int ,int> pii;//时间点,前一个表示时间点的是兼职,后一个表示这个时间点是开始时间还是结束时间
const int N = 1e5 + 10;
pii a[2*N];  //2n 个时间点

int l[N],r[N];  //l  记录机器的开机时间   ,r 机器的关机时间

int main()
{
	int t;
	long long sum = 0;
	scanf( "%d",&t);
	while(t--)
	{
		int n;//一共n 项任务
		scanf( "%d",&n);

		for(int i = 1;i <= n;i++)
		{
			int left,right;
			scanf("%d%d",&left,&right);
			a[2*i - 1] = pii(left,1);
			a[2*i] = pii(right,-1);
		}

		sort(a+1,a+2*n+1);
		memset(l,-1,sizeof(l));
		memset(r,-1,sizeof(r));

		int num = 0,ans = 0;  //num 表示当前运行的机器数量  ans 表示到当前一共开过多少台机器

		for(int i = 1;i <= 2*n;i++)
		{
			if(a[i].second == 1)
			{
				num++;
				if(l[num] == -1)   l[num] = r[num] = a[i].first;//num 是新开的机器
					ans = max(ans,num);
			}
			else
			{
				r[num] = a[i].first;
				num--;
			}
		}
			sum = 0;
			for(int i = 1;i <= ans;i++)
			{
				sum +=(r[i] - l[i]);
			}

		cout << ans << " " << sum << endl;
	}
}
