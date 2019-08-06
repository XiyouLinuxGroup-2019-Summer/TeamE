#include <iostream>
#include <string>
#include <vector>
#include <memory.h>
#define  N 10
using namespace std;
int cnt = 0;
int ans[15];
bool judge(int line,int row,int *a)
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
void dfs(int size,int line,int *a)
{

    if(line == size+1){
        cnt++;
        return ;
    }

    //尝试这一行的每一列
    for(int row = 1;row <= size;row++){
        a[line] = row;
        if(judge(line,row,a)){
            dfs(size,line+1,a);
        }
        else a[line] = 0;//回溯
    }

    return ;
}
int main()
{
    for(int i = 1;i<=10;i++){
        cnt = 0;
        int a[i+10];
        dfs(i,1,a);
        ans[i] = cnt;
    }
    int size;
    while(cin >> size && size){
        cout << ans[size] << endl;
    }
    return 0;
}


