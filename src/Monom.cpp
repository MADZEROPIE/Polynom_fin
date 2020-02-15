#include "polynom.h"

Polynom::Monom::Monom(real _coef, int32_t _pow_coef)
{
	coef = _coef;
	pow_coef = _pow_coef;
}

Polynom::Monom::Monom(int a, int b, int c, real _coef)
{
	coef = _coef;
	pow_coef = a * maxp * maxp + b * maxp + c;
}

float getFloat(std::string s, size_t* i) { // Отвратительная гадость
	if((s[*i]=='+' || s[*i]=='-')&& (*i+1)<s.size()&& (s[*i+1] >= '0' && s[*i+1] <= '9')
		||(s[*i] >= '0' && s[*i]<='9')) 
		return std::stof(s, i);
	if (s[*i] == '-') { *i = *i + 1; return -1.0f; }
	if(s[*i]=='+') *i = *i + 1;
	return 1.0f;
}

int getInt(std::string s, size_t* j) {
	int res=0;
	int i = *j;
	while (i < s.size() && s[i] >= '0' && s[i] <= '9') { res = res * 10 + s[i] - '0'; ++i; }
	
	if (i == *j) return 1;

	*j = i;
	return res;
}

Polynom::Monom::Monom(std::string s)
{
	int a = 0, b = 0, c = 0;
	size_t i = 0;
	coef = getFloat(s, &i);
	coef = getFloat(s, &i);
	s.erase(0, i);
	for (i=0;i<s.size();)
	{
		if ((s[i] == 'x' || s[i] == 'X')&& !a)
		{
			++i;
			a = getInt(s, &i);
			s.erase(0, i);
			i = 0;
		}
		else if ((s[i] == 'y' || s[i] == 'Y') && !b)
		{
			++i;
			b += getInt(s, &i);
			s.erase(0, i);
			i = 0;
		}
		else if ((s[i] == 'z' || s[i] == 'Z') && !c)
		{
			++i;
			c += getInt(s, &i);
			s.erase(0, i);
			i = 0;
		}
		else
			throw 1;
	}
	pow_coef = a * maxp * maxp + b * maxp + c;
}

bool Polynom::Monom::operator<(const Monom& b)
{
	return pow_coef < b.pow_coef; //Надо сравнивать только степени
}

bool Polynom::Monom::operator<=(const Monom& b)
{
	return pow_coef <= b.pow_coef; //Надо сравнивать только степени
}

bool Polynom::Monom::operator==(const real a)
{
	return coef == a;
}

bool Polynom::Monom::operator>(const real a)
{
	return coef > a;
}

bool Polynom::Monom::operator<(const real a)
{
	return coef < a;
}

bool Polynom::Monom::operator==(Polynom::Monom b)
{
	return pow_coef == b.pow_coef; //Надо сравнивать только степени
}

Polynom::Monom Polynom::Monom::operator-()
{
	Monom res(*this);
	res.coef = -res.coef;
	return res;
}

Polynom::Monom Polynom::Monom::abs()
{
	Monom res(*this);
	if (res.coef < 0.0) res.coef = -res.coef;
	return res;
}

Polynom::Monom Polynom::Monom::operator+(const Monom& b)
{
	if (b.pow_coef != pow_coef) throw b.pow_coef;
	else {
		Monom res(*this);
		res.coef += b.coef;
		return res;
	}
}

Polynom::Monom& Polynom::Monom::operator+=(const Polynom::Monom& b)
{
	if (b.pow_coef != pow_coef) throw b.pow_coef;
	else coef += b.coef;
	return *this;
}

Polynom::Monom Polynom::Monom::operator-(const Monom& b)
{
	if (b.pow_coef != pow_coef) throw b.pow_coef;
	else {
		Monom res(*this);
		res.coef -= b.coef;
		return res;
	}
}

Polynom::Monom& Polynom::Monom::operator-=(const Polynom::Monom& b)
{
	if (b.pow_coef != pow_coef) throw b.pow_coef;
	else coef -= b.coef;
	return *this;
}

Polynom::Monom& Polynom::Monom::operator*=(const Monom& b)
{
	if (b.pow_coef % maxp + pow_coef % maxp >= maxp ||
		b.pow_coef / maxp % maxp + pow_coef / maxp % maxp >= maxp ||
		b.pow_coef / maxp / maxp % maxp + pow_coef / maxp / maxp % maxp >= maxp)
		throw 1;
	pow_coef += b.pow_coef;
	coef *= b.coef;
	return *this;
}

std::vector<int> Polynom::Monom::get_deg()
{
	std::vector<int> res;
	res.push_back(pow_coef / maxp / maxp % maxp);
	res.push_back(pow_coef / maxp % maxp);
	res.push_back(pow_coef % maxp);
	return res;
}

int Polynom::Monom::set_deg(int a, int b, int c)
{
	pow_coef = a * maxp * maxp + b * maxp + c;
	return pow_coef;
}

std::string Polynom::Monom::ToString()
{
	std::vector<int> kof = get_deg();
	std::stringstream ans;
	ans << "";
	std::string vars = "xyz";
	if (coef == 0)
		return ans.str();
	std::stringstream out;
	if (coef != 1)
	{
		out << coef;
		ans << out.str();
	}
	for (size_t i = 0; i < 3; ++i)
	{
		if (kof[i] != 0)
		{
			if (kof[i] == 1)
			{
				ans << vars[i];
			}
			else
			{
				ans << vars[i];
				ans << kof[i];
			}
		}
	}
	return ans.str();
}