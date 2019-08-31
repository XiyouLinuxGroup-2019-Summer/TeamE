#include"tabtenn1.h"
#include<iostream>
										//通过初始化列表初始化
TableTennisPlayer::TableTennisPlayer(const string & fn,const string & ln,bool ht) : firstname(fn),lastname(ln),hasTAble(ht){}
void TableTennisPlayer::Name() const
{
	std::cout << lastname << ", " << firstname;
}
									           //给父类构造函数 传递参数
RatePlayer::RatePlayer(unsigned int r,const string & fn,const string & ln,bool ht) : TableTennisPlayer(fn,ln,ht)
{
	rating = r;
}
RatePlayer::RatePlayer(unsigned int r,const TableTennisPlayer & tp) : TableTennisPlayer(tp),rating(r) {}

