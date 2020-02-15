#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

typedef double real;

#define maxp 1000
//ѕолином - это выражение следующего вида 10x3y4z5+5z == 10*(x^3)*(y^4)*(z^5)+5*z

class Polynom{

public:

	class Monom {
	public:
		real coef;
		int32_t pow_coef;


		Monom(real _coef = 0.0, int32_t _pow_coef = -1);

		Monom(int a, int b, int c, real _coef = 0.0);

		Monom(std::string a);

		bool operator<(const Monom& b);

		bool operator<=(const Monom& b);

		bool operator==(const real a);

		bool operator>(const real a);

		bool operator<(const real a);

		bool operator==(Polynom::Monom b);

		Monom operator-();
		Monom abs();
		Monom operator+(const Monom& b);
		Monom& operator+=(const Monom& b);
		Monom operator-(const Monom& b);
		Monom& operator-=(const Monom& b);
		Monom& operator*=(const Monom& b);

		std::vector<int> get_deg();
		int set_deg(int a, int b, int c);

		std::string ToString();
	};



public:
	class Node
	{
	public:
		Node* pNext;
		Monom mon;
		Node(Monom mon = Monom(), Node* pNext = nullptr) {
			this->mon = mon;
			this->pNext = pNext;
		}
	};

private:
	Node* head;

public:

	Polynom();

	Polynom(std::string str);

	Polynom(const Polynom& pol);
	~Polynom();

	Polynom& operator=(const Polynom& pol);

	Polynom operator+(const Polynom& pol);

	Polynom operator-();

	Polynom& operator+=(const Polynom& pol);

	Polynom& operator-=(Polynom& pol);

	Polynom operator-(Polynom& pol);

	Polynom operator*(Polynom::Monom& mon);

	Polynom operator*(const Polynom& pol);

	Polynom operator*(const real a);

	Polynom& merge(Polynom& b);
	
	
	std::string ToString();

	void clear();

	void del_zeros();
};