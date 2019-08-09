#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#define N 2000100
#define M 20100

using namespace std;
int ans = 0;
void get_next(string S,int *next,int len_t)
{
    int i = 0,j = -1;
    while(i < len_t){
        if(j == -1 || S[i] == S[j]){
            next[i] = j;
            ++i;
            ++j;
        }
        else j = next[j];
    }

   /* for(int i = 0;i<len_t;i++){ */
   /*      cout << i << " " << next[i] << endl; */
   /*  } */

}
int Index_KMP(string S,int len_s,string T,int len_t,int pos)
{
    int i = pos;//i表示主串开始检索的位置
    int j = 0;//标记子串的位置
    int next[M];
    get_next(T,next,len_t); //得到前缀表
    
    
    while(i < len_s){
        while(j >= 0 && T[j] != S[i]) j = next[j];
        if(j == len_t-1){
            ans++;
            j = next[j];
        }
        i++,
        j++;
    }
    return ans;
}
int main()
{
    int t;
    string S;//主串
    string T; //待匹配串
    cin >> t;
    while(t--)
    {
        ans = 0;
        cin >> S;
        cin >> T;
        cout << Index_KMP(S,S.size(),T,T.size(),0) << endl;
    }
    return 0;
}
