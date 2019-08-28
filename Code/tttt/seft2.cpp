#include<iostream>
#include<cmath>

using namespace std;

int main()
{
	//左对齐
	cout.setf(ios_base::left,ios_base::adjustfield);
	//在正数前 加上 +
	cout.setf(ios_base::showpos);
	//显示末尾的小数点
	cout.setf(ios_base::showpoint);
	cout.precision(3);
				//返回值是上次的设置
	ios_base::fmtflags old = cout.setf(ios_base::scientific,ios_base::floatfield);
							//科学计数法
	cout << "Left justification" << endl;

	for(long n = 1;n <= 41;n += 10)
	{
		cout.width(4);
		cout << n << "|";
		cout.width(12);
		cout << sqrt(double(n)) << "|" << endl;
	}
	cout << endl;
			//符号或奇数前缀左对齐,值右对齐
	cout.setf(ios_base::internal,ios_base::adjustfield);

	cout.setf(old,ios_base::floatfield);

	cout << "internal justification: " << endl;

	for(long n = 1;n <= 41;n += 10)
	{
		cout.width(4);
		cout << n << "|";
		cout.width(12);
		cout << sqrt(double(n)) << "|" << endl;
	}
	
	cout << endl;
	//右对齐
	cout.setf(ios_base::right,ios_base::adjustfield);
	//顶点计数法
	cout.setf(ios_base::fixed,ios_base::floatfield);

	cout << "Right justification" << endl;

	for(long n = 1;n <= 41;n += 10)
	{
		cout.width(4);
		cout << n << "|";
		cout.width(12);
		cout << sqrt(double(n)) << "|" << endl;
	}

	cout << endl;


	return 0;
}
