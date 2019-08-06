#include <iostream>
#define N 10
using namespace std;
int map[N][N];
int judge(int line,int row)
{
    for(int i )
}
void dfs(int line)
{
    if(line == 10)
    {
        cout << "Yes" << endl;
        return ;
    }
    int a[10]={0,0,0,0,0,0,0,0,0,0};
    for(int row =1;row<=9;row++){
        if(map[line][row] != 0){//这一行中有
            a[map[line][row]] = 1;
        }
    }

    for(int row = 1;row <=9;row++){
        if(map[line][row] == 0){
            for(int i = 1;i<=9;i++){
                if(a[i] == 0) map[line][row] = i;
                if(judge(line,row)){
                    dfs(line+1);
                }
                else{
                    map[line][row] = 0;
                }
            }
        } 
    }
    return ;
}

int main()
{

    for(int i = 1;i<=9;i++)
        for(int j = 1;j<=9;j++){
            char tmp;
            cin >> tmp;
            if(tmp == '?') continue;
            else map[i][j] = (int)tmp-48;
        }


    dfs(1);
    cout << endl;
    for(int i = 1;i<=9;i++){
        for(int j = 1;j<=9;j++){
            cout << map[i][j] << " "; 
        }
        cout << endl;
    }
    return 0;
}

