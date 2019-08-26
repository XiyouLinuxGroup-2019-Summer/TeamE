#ifndef VECTOR_H_
#define VECTOR_H_

#include<iostream>

//    using namespace std;

namespace VECTOR
{
	class Vector
	{
		public:
			enum Mode {RECT,POL};
		private:
			double x;
			double y;
			double mag;
			double ang;
			Mode mode;    //RECT or POL
			void set_mag();
			void set_ang();
			void set_x();
			void set_y();
		public:
			Vector();   //无参构造
			Vector(double n1,double n2,Mode form = RECT);
			~Vector();    //析构函数

			double xval() const {return x;}    // const   表明 该 函数不 修改 class 的成员
			double yval() const {return y;}
			double magval() const {return mag;}
			double angval() const {return ang;}
			void polar_mode();   //set mode to POL
			void rect_mode();    // set mode to RECT

			// operator   
			Vector operator+(const Vector &b) const;
			Vector operator-(const Vector &b) const;
			Vector operator-()   const;
			Vector operator*(double n)  const;

			//friend

			friend Vector operator*(double n,const Vector & a);
			friend std::ostream &
				operator << (std::ostream & os,const Vector & v);


	};
}

#endif
