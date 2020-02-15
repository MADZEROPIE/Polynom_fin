#include <iostream>
#include "polynom.h"

using std::string;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");
	Polynom a;
	Polynom b("10x3y4z5+z");
	Polynom c("x3");
	std::cout << b.ToString() << '\n';
	a=b*c;

	std::cout << a.ToString()<<'\n';
	std::cout << c.ToString();


	return 0;
}

