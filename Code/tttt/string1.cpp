#include<cstring>
#include"string1.h"

using std::cin;
using std::cout;

int String::num_string = 0;

// static method
int String::howmany() { return num_string; }

String::String(const char * s)
{
	len = std::strlen(s);
	str = new char[len + 1];
	std::strcpy(str,s);
	num_string++;
}

String::String()
{
	
	len = 4;
	str = new char[1];
	str[0] = '\0';
	num_string++;

}

String::String(const String & st)
{
	num_string++;
	len = st.len;
	str = new char [len + 1];
	std::strcpy(str,st.str);
}

String::~String()
{
	--num_string;
	delete [] str;

}

String & String::operator=(const String & st)
{
	if(this == &st)   return *this;

	delete [] str;
	
	str = new char [len + 1];
	len = st.len;
	std::strcpy(str,st.str);

	return *this;
}

String & String::operator=(const char * s)
{
	delete [] str;
	
	len = std::strlen(s);

	str = new char [len + 1];
	std::strcpy(str,s);

	return *this;

}


char & String::operator[](int i)
{
	return str[i];
}

const char & String::operator[](int i) const
{
	return str[i];
}

bool operator < (const String & st1,const String & st2)
{
	return (std::strcmp(st1.str,st2.str) < 0);
}

bool operator > (const String & st1,const String & st2)
{
	return (std::strcmp(st1.str,st2.str) > 0);
}

bool operator == (const String & st1,const String & st2)
{
	return (std::strcmp(st1.str,st2.str) == 0);
}
ostream & operator<<( ostream & os,const String & st2)
{
	os << st2.str;
	return os;
}

istream & operator>>(istream & is,String & st2)
{
	char temp[String::CINLIM];
	is.get(temp,String::CINLIM);
	if(is)  st2 = temp;

	while(is && is.get() != '\n') continue;
	
	return is;
}



