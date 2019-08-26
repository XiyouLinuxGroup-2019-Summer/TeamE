#include<cmath>
#include"vect.h"

using namespace std;

namespace VECTOR
{
	//计算一个弧度的度数
	const double Rad_to_deg = 45.0 / atan(1.0);


	void Vector::set_mag()
	{
		mag = sqrt(x*x + y*y);
	}

	void Vector::set_ang()
	{
		if(x == 0.0 && y == 0.0)   ang = 0.0;
		else ang = atan2(y,x);        //以弧度表示的 y/x 的反正切  比 atan 稳定
	}

	void Vector::set_x()
	{
		x = mag * cos(ang);
	}


}
