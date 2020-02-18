#include "polynom.h"

Polynom::Monom::Monom(real _coef, int32_t _pow_coef)
{
	coef = _coef;
	pow_coef = _pow_coef; // Проверка здесь все сломает (у head==-1)
}

Polynom::Monom::Monom(int32_t a, int32_t b, int32_t c, real _coef)
{
	coef = _coef;
	if (a < 0 || b < 0 || c < 0
		|| a >= maxp || b >= maxp || c >= maxp) throw maxp;
	pow_coef = a * maxp * maxp + b * maxp + c;
}

real getDouble(std::string s, size_t* i) { // Отвратительная гадость, лучше переделать обратно под итераторы
	if(((s[*i]=='+' || s[*i]=='-')&& (*i+1)<s.size() && (s[*i+1] >= '0' && s[*i+1] <= '9'))
		||(s[*i] >= '0' && s[*i]<='9')) 
		return std::stod(s, i);
	if (s[*i] == '-' && (*i + 1) < s.size()) { *i = *i + 1; return -1.0; }
	if(s[*i]=='+' && (*i + 1) < s.size()) *i = *i + 1;
	return 1.0;
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
	int32_t a = 0, b = 0, c = 0;
	size_t i = 0;
	coef = getDouble(s, &i);
	s.erase(0, i);
	for (i=0;i<s.size();)
	{
		if ((s[i] == 'x' || s[i] == 'X') && !a)
		{
			++i; //Слишком много действий
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

bool Polynom::Monom::operator==(const Polynom::Monom& b)
{
	return pow_coef == b.pow_coef; //Надо сравнивать только степени
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

std::vector<int32_t> Polynom::Monom::get_deg()
{
	std::vector<int32_t> res;
	res.push_back(pow_coef / maxp / maxp % maxp);
	res.push_back(pow_coef / maxp % maxp);
	res.push_back(pow_coef % maxp);
	return res;
}

int32_t Polynom::Monom::set_deg(int32_t a, int32_t b, int32_t c)
{
	if (a < 0 || b < 0 || c < 0
		|| a >= maxp || b >= maxp || c >= maxp) throw maxp;
	pow_coef = a * maxp * maxp + b * maxp + c;
	return pow_coef;
}

std::string Polynom::Monom::ToString()
{
	std::vector<int> kof = get_deg();
	std::stringstream ans;
	ans << "";
	char vars[] = "xyz";
	if (coef == 0)
		return ans.str();
	if (coef != 1 || (coef == 1 && (kof[0]==0 && kof[1]==0 && kof[2]==0)))
	{
		ans << coef;
	}
	for (size_t i = 0; i < 3; ++i)
	{
		if (kof[i] != 0)
		{
			ans << vars[i];
			if (kof[i] != 1) ans << kof[i];
		}
	}
	return ans.str();
}