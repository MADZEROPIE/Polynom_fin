#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

typedef double real;

#define maxp 1000
//Полином - это выражение следующего вида 10x3y4z5+5z-y БЕЗ ПРОБЕЛОВ

class Polynom{

public:

	class Monom {
	public:
		real coef;
		int32_t pow_coef;

		Monom(real _coef = 0.0, int32_t _pow_coef = -1);
		Monom(int32_t a, int32_t b, int32_t c, real _coef = 0.0);
		Monom(std::string a);

		bool operator<(const Monom& b);
		bool operator<=(const Monom& b);
		bool operator==(const Polynom::Monom& b);
		
		bool operator==(const real a);
		bool operator>(const real a);
		bool operator<(const real a);

		Monom operator-();
		Monom abs();

		Monom operator+(const Monom& b);
		Monom& operator+=(const Monom& b);
		Monom operator-(const Monom& b);
		Monom& operator-=(const Monom& b);
		Monom& operator*=(const Monom& b);

		std::vector<int32_t> get_deg();
		int32_t set_deg(int32_t a, int32_t b, int32_t c);

		std::string ToString();
	};


public:
	class Node
	{
	public:
		Node* pNext;
		Polynom::Monom mon;
		Node(Polynom::Monom mon = Monom(), Node* pNext = nullptr) { //Выносить один конструктор в другой файл... 
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
	Polynom& operator+=(const Polynom& pol);

	Polynom operator-();
	Polynom operator-(const Polynom& pol);
	Polynom& operator-=(Polynom& pol);
	
	Polynom operator*(const real a);
	Polynom operator*(const Polynom::Monom& mon);
	Polynom operator*(const Polynom& pol);

	Polynom& merge(const Polynom& b);
	Polynom& sort();

	std::string ToString();

	void clear();

	void del_zeros();
};