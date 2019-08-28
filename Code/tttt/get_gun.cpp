#include<iostream>

using namespace std;


const int Limit = 255;

int main()
{
	char input[Limit];
	cout << "输入一个字符串 用getline 读取程序\n";
	cin.getline(input,Limit,'#');
	cout << " 这是你的输入 " << endl;
	cout << input << "\n 第一部分完成"  << endl;

	char ch;
	cin.get(ch);
	cout << "接下来的输如 字符 是 " <<  ch << endl;

	if(ch != '\n') cin.ignore(Limit,'\n');


	cout << " 输入第二个字符串 " << endl;
	cin.get(input,Limit,'#');
	cout << " 这是你第二次的输入" << endl;
	cout << input << "\n 第二部分完成 "  << endl;
	

	cin.get(ch);

	cout << " 接下来输入的字符 是 " << ch << endl;

	

	return 0;
}
