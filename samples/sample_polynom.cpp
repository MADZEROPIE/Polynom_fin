#include <iostream>
#include "polynom.h"

using std::string;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");

	string inp;
	std::cout << "¬ведите полином a: ";
	std::cin >> inp;
	Polynom a(inp);

	std::cout << "¬ведите полином b: ";
	std::cin >> inp;
	Polynom b(inp);

	std::cout << "a = " << a.ToString() << '\n';
	std::cout << "b = " << b.ToString() << '\n';
	std::cout << "a*b = " << (a*b).ToString() << '\n';
	std::cout << "a+b = " << (a+b).ToString() <<'\n';

	return 0;
}

