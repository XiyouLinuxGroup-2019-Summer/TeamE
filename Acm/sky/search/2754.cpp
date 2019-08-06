#include <iostream>
#include <string>
#include <vector>
#include <memory.h>
#define  N 10
using namespace std;
int ans[100][N];
int a[N];//用来记录位置 a[i] = j 第i行放在第j列
int cnt = 1;
bool judge(int line,int row)
{
    //判断这一列有没有皇后
    for(int i = 1;i<line;i++){
        if(a[i] == row) return false;
    }

    //判断对角线上有没有皇后,主对角线方向差相等，副对角线上和相等
    for(int i = 1;i<line;i++){
        if((i - a[i]) == (line - row) || (i+a[i] == line + row)){
            return false;
        }
    }

    return true;
}
void dfs(int line)
{

    if(line == 9){
        memcpy(ans[cnt++],a,sizeof(a));
        return ;
    }

    //尝试这一行的每一列
    for(int row = 1;row <= 8;row++){
        a[line] = row;
        if(judge(line,row)){
            dfs(line+1);
        }
        else a[line] = 0;//回溯
    }

    return ;
}
int main()
{
    int n;
    cin >> n;
    dfs(1);
    for(int i = 0;i<n;i++)
    {
        int t;
        cin >> t;
        for(int j = 1;j<=8;j++){
            cout << ans[t][j];
        }
        cout << endl;
    }
    return 0;
}

