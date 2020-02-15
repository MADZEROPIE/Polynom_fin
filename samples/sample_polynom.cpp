#include <iostream>
#include "polynom.h"

using std::string;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");
	Polynom a;
	Polynom b("10x3y4z5+5z-y");
	Polynom c("x3");
	
	a=b*c;

	std::cout <<"a = "<< a.ToString()<<'\n';
	std::cout <<"b = "<< b.ToString()<<'\n';
	std::cout <<"c = "<< c.ToString();


	return 0;
}

