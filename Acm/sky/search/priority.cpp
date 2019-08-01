#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct node
{
    int x,y;
    node(int x,int y):x(x),y(y){}
};

bool operator < (node a,node b)
{
    return a.x < b.x;
}
int main()
{
    priority_queue<int> q;
    priority_queue<node > q2;
    struct node x;
    x.x = 10;x.y = 1;
    node y;
    q.push(5);
    q.push(99);
    q.push(-1);
    q.push(10);
    q.push(5);

    cout << "size = " << q.size() << endl;
    while(!q.empty())
    {
        cout << q.top() << endl;
        q.pop();
    }
    return 0;
}

