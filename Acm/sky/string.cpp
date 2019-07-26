#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int main()
{
    /* string line; */

    /*while(getline(cin,line))
    {
        int sum = 0,x;
        stringstream ss(line);
        while(ss >> x) sum += x;
        cout << sum << endl;
    }*/

    //string 构造函数
    string s1;
    string s2("Hello");
    string s3(4,'k');
    string s4("12345",1,3);

    //使用assign对成员函数赋值
    string s("012345");

    s1.assign(s);
    s2.assign(s,1,2);
    s3.assign(4,'k');
    s4.assign("012345",2,3);

    s3 += s1;
    s4 = s1+s3;

    if(s1 < s2)
        cout << "s1 < s2" << endl;
    string sub = s1.substr(2,4);//从2开始截取长度为3位
    cout << sub << endl;
    cout << s1 << "len = " << s1.length() << endl;
    cout << s2 << endl;
    s3.swap(s4);
    cout << s3 << endl;
    cout << s4 << endl;
    for(int i = 0;i<s4.length();i++)
        cout << s4[i] << endl;
    return 0;
}

