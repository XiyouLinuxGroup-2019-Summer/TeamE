#include<iostream>

using namespace std;

const int SLEN = 10;
inline void eatline(){ while(std::cin.get() != '\n') continue; }

int main()
{
	char name[SLEN];
	char title[SLEN];

	cout << "输入你的名字:";
	cin.get(name,SLEN);
	if(cin.peek() != '\n')   cout << "不好意思我们只有足够的房间给 " << name << endl;

	eatline();
	cout << "Dear " << name << "请输入你的标题 " << endl;
	cin.get(title,SLEN);

	if (cin.peek() != '\n')   cout << " we are forced to truncate your titke.\n";
	eatline();

	cout << "name:" << name << endl
		<<"Title :" << title << endl;


	return 0;
}
