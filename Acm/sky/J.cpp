#include <iostream>
#include <stdlib.h>
using namespace std;
typedef struct rec
{
    int c;
    int k;
}rec;
rec r[4];

int isok(rec r1,rec r2,rec *tmp)
{
    if(r1.c == r2.c)
    {
        tmp->c = r1.c;
        tmp->k = r1.k + r2.k;
        return 1;
    }
    if(r1.c == r2.k)
    {
        tmp->c = r1.c;
        tmp->k = r1.k + r2.c;
        return 1;
    }
    if(r1.k == r2.c)
    {
        tmp->c = r1.k;
        tmp->k = r1.c + r2.k;
        return 1;
    }
    if(r1.k == r2.k) 
    {
        tmp->c = r1.k;
        tmp->k = r1.c + r2.c;
        return 1;
    }
    return 0;
}
int judge(rec r1,rec r2,rec r3)
{
    rec tmp,tmp2;
    if(isok(r1,r2,&tmp))
    {
        
        if(isok(tmp,r3,&tmp2)) return 1;
    }
    else if(isok(r1,r3,&tmp))
    {
        
        if(isok(tmp,r2,&tmp2)) return 1;
    }
    else if(isok(r3,r2,&tmp))
    {
        
        if(isok(tmp,r1,&tmp2)) return 1;
    }
    return 0;



}
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int flag = 0;
        for(int i = 0;i<4;i++)
        {
            cin >> r[i].c >> r[i].k;
        }
        if(judge(r[0],r[1],r[2])) flag = 1;
        
        else if(judge(r[0],r[1],r[3])) flag = 1;
        else if(judge(r[0],r[3],r[2])) flag = 1;
        else if(judge(r[1],r[2],r[3])) flag = 1;
        if(flag) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}

