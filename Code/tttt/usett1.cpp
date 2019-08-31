#include<iostream>
#include"tabtenn1.h"

int main()
{
	using std::cout;
	using std::endl;

	TableTennisPlayer player1("Tara","boomdea",false); //初始化 一个 父类
	RatePlayer rplayer1(1140,"mallory","duck",true);  // 初始化一个 子类

	rplayer1.Name();

	if(rplayer1.HasTable())   cout << " : has a table.\n";
	else cout << ": hasn't a table.\n";
	
	player1.Name();

	if(player1.HasTable()) cout << ": has a table.\n";
	else cout << ": has't a table.\n";

	cout << "Name: ";
	rplayer1.Name();
	cout <<"; Rating: " << rplayer1.Rating() << endl;
	RatePlayer rplayer2(1212,player1);    //初始化 用一个子类
	cout << "Name: ";
	rplayer2.Name();
	cout << "; Rating: " << rplayer2.Rating() << endl;


	return 0;
}
