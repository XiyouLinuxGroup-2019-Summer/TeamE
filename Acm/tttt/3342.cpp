/*
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>


using namespace std;

queue<int> q;
vector<int> ans;   //保存拓扑排序
vector<int> v[105];


int in[10005];  //保存点的入度

int edge[1005][1005];  //保存边
int vis[105];
int main( )
{
	int n,m;
	while(cin >> n >> m && n)
	{
		for(int i = 0;i < 105;i++)    ans.clear();
		for(int i=0; i<103; i++)      v[i].clear();

		memset(in,0,sizeof(in));
		memset(edge,0,sizeof(edge));
		
		int a,b;
		for(int i = 0;i < m;i++)
		{
			cin >> a >>b;
			//edge[a][b] = 1;
			v[a].push_back(b);
			in[b]++;   //保存每个点的入度
		}
		
		for(int i = 0;i < n;i++)	if(in[i] == 0)
						{
							q.push(i);
							vis[i] = 1;
						}

		while(!q.empty())
		{
			int p = q.front();
			q.pop();
			ans.push_back(p);

			for(int i = 0;i < v[p].size();i++)
			{
				int x = v[p][i];
				in[x]--;

				if(in[x] == 0 && !vis[x])
				{
					q.push(x);
					vis[x] = 1;
				}
				*/
/*				if(edge[p][i])
				{
				//	temp = i;
					in[i]--;
					if(in[i] == 0) q.push(i);
				}
*/
/*				//if(in[temp] == 0)  q.push(temp);
			}

		}

		if(ans.size() == n)  cout << "YES" << endl;
		else  cout << "NO" << endl;
	}
}


*/


#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>

using namespace std;

vector<int> v[105];
queue<int> q;
int indeg[105];
int n,m;
int cnt;

int toposort()
{
	while(!q.empty())  q.pop();
	for(int i = 0;i < n;i++)   if(!indeg[i]) q.push(i);

	while(!q.empty())
	{
		int temp = q.front();
		cnt++;
		q.pop();
		
		for(int i = 0;i < v[temp].size();i++)
		{
			int x = v[temp][i];
			indeg[x]--;
			if(!indeg[x]) q.push(x);
		}
	}

	if(cnt == n)   return 1;
	else return 0;

}
int main( )
{
	while(cin >> n >> m && n)
	{
		cnt = 0;
		memset(indeg,0,sizeof(indeg));
		for(int i = 0;i < n;i++)  v[i].clear();

		int a,b;
		for(int i = 0;i < m;i++)
		{
			cin >> a >> b;
			v[a].push_back(b);
			indeg[b]++;
		}

		if(toposort())  cout << "YES" << endl;
		else cout << "NO" << endl;
	}

}
