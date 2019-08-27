#include<iostream>

using namespace std;

int main()
{
	cout << "Enter an integer: ";
	int n;
	cin >> n;

	cout << "n  n*n\n";
	cout << n << "   " << n * n << "(decimal) \n";
	//set to mode 
	cout << hex;
	cout << n << "  ";
	cout << n*n << "  (hexadecimal)\n";
	cout << dec;
	cout << n << endl;
	//set to octal mode 
	cout << oct << n << "  " << n*n << " (octal)\n";

	//alernative way to call a manipulator
	dec(cout);
	cout << n << "  " << n*n << " (decimal)\n";

	return 0;
}
