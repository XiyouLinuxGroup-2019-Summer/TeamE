#include <iostream>
#include <queue>
#include <cstdio>
#include <map>
#include <sstream>
using namespace std;
int main()
{
    //大队列和小队列
    int t;
    int kase = 0;
    while(cin >> t && t)
    {
        queue <int > q;
        queue <int > qs[t];
        map <int,int> mp;
        printf("Scenario #%d\n",++kase);
        for(int i = 0;i<t;i++)
        {
            int num;
            cin >> num;
            for(int j = 0;j<num;j++)
            {
               int tmp;
               cin >> tmp;
               mp[tmp] = i;//映射到自己所属的小队列
               /* printf("mp[%d] = %d\n",tmp,i); */
            }
        }

        while(1)
        {
            string s;
            cin >> s;
            /* cout << s << endl; */
            if(s[0] == 'S') break;
            else if(s[0] == 'E') 
            {
                int number; 
                cin >> number;
                /* printf("number = %d\n",number); */
                int qsnum = mp[number];
                /* cout << qsnum << endl; */ 
                //小队为空说明小队不在大队中
                if(qs[qsnum].empty()) q.push(qsnum);
                //小队已经在大队中了，直接入小队就可以
                    qs[qsnum].push(number);

                /* printf("front = %d\n",qs[qsnum].front()); */

            }
            else if(s[0] == 'D')
            {
                if(q.empty()) continue;
                int qsnum = q.front();
                /* printf("qsnum = %d\n",qsnum); */
                printf("%d\n",qs[qsnum].front());
                qs[qsnum].pop();
                if(qs[qsnum].empty()) q.pop();//小队空了之后  从大队退出
            }
        
        }
        printf("\n");
        

    }
    return 0;
}

