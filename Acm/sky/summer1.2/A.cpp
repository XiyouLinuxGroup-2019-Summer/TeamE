#include <iostream>
#include <cstdio>
#define N 2000100
#define M 20100
using namespace std;
void get_next(int *T,int *next,int len_t)
{
    int i = 1, j = 0;
    next[1] = 0;
    while(i < len_t){
        if(j == 0 || T[i] == T[j]){//T[i]表示前缀单个字符,T[j]表示后缀单个字符
            ++i;
            ++j;
            next[i] = j;
        }
        else j = next[j]; //字符不相同j 值回溯
    }

}
int Index_KMP(int *S,int len_s,int *T,int len_t,int pos)
{
    int i = pos;//i表示主串开始检索的位置
    int j = 1;//标记子串的位置
    int next[M];
    get_next(T,next,len_t); //得到前缀表
    while(i <= len_s && j <= len_t){
       if(j == 0 || S[i] == T[j]) {//两字母相等则继续
           ++i;
           ++j;
       }
       else j = next[j]; //回退的合适位置
    }

    if(j > len_t) return i-len_t;
    else return -1;//表示没有找到
}
int main()
{
    int t;
    int n,m;
    int S[N];//主串
    int T[M]; //待匹配串
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(int i = 1;i<=n;i++)
            scanf("%d",&S[i]);
        for(int i = 1;i<=m;i++)
            scanf("%d",&T[i]);
        cout << Index_KMP(S,n,T,m,1) << endl;
    }
    return 0;
}

