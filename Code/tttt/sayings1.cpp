#include<iostream>
#include"string1.h"

const int ArSize = 10;
const int MaxLen = 81;

int main()
{
	using std::cout;
	using std::cin;
	using std::endl;

	String name;
	cout << "Hi,你的名字?\n >> ";
	cin >> name;

	cout << name << ", 最多输入 " << ArSize << " 简短 (输入空行结束)" << endl;

	String sayings[ArSize];
	char temp[MaxLen];
	int i;
	for(i = 0;i < ArSize;i++)
	{
		cout << i+1 <<": ";
		cin.get(temp,MaxLen);
		
		while(cin && cin.get() != '\n') continue;
		
		if(!cin || temp[0] == '\0') break;
		else sayings[i] = temp;
	}

	int total = i;
	if(total > 0)
	{
		cout << "这是你说的话: " << endl;
		for(i = 0;i < total;i++)   cout << sayings[i][0] << ": " << sayings[i] << endl;

		int shortest = 0;
		int first = 0;

		for(i = 1;i < total;i++)
		{
			if(sayings[i].length() < sayings[shortest].length())  shortest = i;

			if(sayings[i] < sayings[first])  first = i;
		}

		cout << "最短的话:\n" << sayings[shortest] << endl;
		cout << "First alphabetuclally:\n" << sayings[first] << endl;
		cout << "This program used " << String::howmany() << "string object.  bye" << endl;


	}
	else
		cout << "No input!bye\n";

	return 0;
}
