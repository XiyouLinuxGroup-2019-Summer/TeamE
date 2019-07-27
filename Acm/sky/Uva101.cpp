#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;
vector <int > v[25];
int n;
void find_block(int &block,int &pa,int &ha)
{
    for(int i = 0;i<25;i++)
        for(int j = 0;j<(int)v[i].size();j++)
        {
            if(v[i][j] == block) 
            {
                pa = i;
                ha = j;
                return ;
            }
        }
    return ;
}
void clear_above(int pa,int ha)
{
    /* cout << pa << "\n" << ha << endl; */
    for(int i = ha+1;i<(int)v[pa].size();i++)
    {
        int pos = v[pa][i];
        v[pos].push_back(pos);
    }
    v[pa].resize(ha+1);
    return ;
}
void show_ans()
{
    for(int i = 0;i<n;i++)
    {
        cout << i << ":" ;
        for(int j = 0;j<(int)v[i].size();j++)
        {
            cout << " "<< v[i][j] ; 
        }
        cout << "\n";
    }
}
void pile_on(int pa,int ha,int pb)
{
    for(int i = ha;i<(int)v[pa].size();i++)
    {
        v[pb].push_back(v[pa][i]);
    }
    v[pa].resize(ha);
}
int main()
{
    cin >> n;
    for(int i = 0;i<n;i++)
        v[i].push_back(i);//初始化操作
    /* v[1].push_back(2); */
    /* show_ans(); */
    while(1)
    {
        int a,b,pa,pb,ha,hb;
        string s1,s2;
        cin >> s1;
        if(s1 == "quit" ) break;
        cin >> a >> s2 >> b;

        find_block(a,pa,ha);//获取小块所在的堆 和 堆的信息
        find_block(b,pb,hb);

        if(pa == pb ) continue;
        if(s1 == "move") clear_above(pa,ha);
        if(s2 == "onto") clear_above(pb,hb);
        pile_on(pa,ha,pb);
    }
    show_ans();
    return 0;
}

