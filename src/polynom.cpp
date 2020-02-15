#include "polynom.h"

Polynom::Polynom()
{
	head = new Node;
	head->pNext = head;
}

Polynom::Polynom(std::string s)//¬се просто и компактно (автомат получаетс€ в 2 раза больше и некрасивее, но работает быстрее (?) )
{
	head = new Node;
	Node* pNode = head;
	for (; s.size(); ) {
		int i = 1;
		while (i < s.size() && s[i] != '+' && s[i] != '-' ) ++i;
		std::string mon_str = s.substr(0, i);
		Monom tmp(mon_str);
		s.erase(0, i);
		pNode->pNext = new Node(tmp,head);
		pNode = pNode->pNext;
	}

}

Polynom::Polynom(const Polynom& pol)
{
	head = new Node(pol.head->mon);
	Node* p1 = head;
	Node* p2 = pol.head->pNext;
	while (p2 != pol.head) {
		p1->pNext = new Node(p2->mon, head);
		p2 = p2->pNext;
		p1 = p1->pNext;
	}
	p1->pNext = head;

}

Polynom::~Polynom()
{
	clear();
	delete head;
}

Polynom& Polynom::operator=(const Polynom& pol)
{
	if (head == pol.head) return *this;
	clear();
	Node* p2 = pol.head->pNext;
	Node* p1 = head;
	while (p2 != pol.head) {
		p1->pNext = new Node(p2->mon, head);
		p2 = p2->pNext;
		p1 = p1->pNext;
	}
	return *this;
}

Polynom Polynom::operator+(const Polynom& pol)
{
	Polynom res(*this);
	return res += pol;
}

Polynom Polynom::operator-()
{
	Polynom res(*this);
	Node* tmp = res.head->pNext;
	while (tmp != res.head) {
		tmp->mon = -tmp->mon;
		tmp = tmp->pNext;
	}
	return res;
}

Polynom& Polynom::operator+=(const Polynom& pol)
{
	Polynom b = pol; //—лишком много действий
	return this->merge(b);
}

Polynom& Polynom::operator-=(Polynom& pol)
{
	return this->merge(-pol); 
}

Polynom Polynom::operator-(Polynom& pol)
{
	Polynom res = -pol;
	return res += *this;
}

Polynom Polynom::operator*(Polynom::Monom& mon)
{
	Polynom res(*this);
	Node* p = res.head->pNext;
	while (p != res.head) {
		p->mon *= mon;
		p = p->pNext;
	}
	res.del_zeros();
	return res;
}

Polynom Polynom::operator*(const Polynom& pol)
{
	Polynom res;
	Node* p = pol.head->pNext;
	while (p != pol.head) {
		res.merge((*this) * p->mon); //Travis'у это не нравитс€, мне тоже...
		p = p->pNext;
	}
	return res;
}

Polynom Polynom::operator*(const real a)
{
	Polynom res(*this);
	Node* tmp = res.head->pNext;
	if (a == 0.0) res.clear();
	else {
		while (tmp != res.head) {
			tmp->mon *= a;
			tmp = tmp->pNext;
		}
	}
	return res;
}

Polynom& Polynom::merge(Polynom& b)
{
	Node* head0 = new Node;
	Node* p1 = head->pNext, * p2 = b.head->pNext, * p0 = head0;
	while (p1 != head || p2 != b.head) {
		if (p1->mon <= p2->mon) {
			if (p2->mon == p0->mon)
			{
				p0->mon += p2->mon;
				Node* tmp = p2;
				p2 = p2->pNext;
				delete tmp;
			}
			else {
				p0->pNext = p2;
				p0 = p2;
				p2 = p2->pNext;
			}
		}
		else {
			if (p1->mon == p0->mon)
			{
				p0->mon += p1->mon;
				Node* tmp = p1;
				p1 = p1->pNext;
				delete tmp;
			}
			else {
				p0->pNext = p1;
				p0 = p1;
				p1 = p1->pNext;
			}
		}
	}
	head = head0;
	p0->pNext = head;
	b.head->pNext = b.head;
	del_zeros(); //ћожно в этом же проходе провер€ть на 0, но мне лень
	return *this;
}

std::string Polynom::ToString()
{
	Node* p = head;
	std::string ans = "";
	if (p->pNext == head)
		return "0";
	if (p->pNext->mon > 0.0)
		ans += p->pNext->mon.ToString();
	else
		ans += "-" + p->pNext->mon.abs().ToString();
	p = p->pNext;
	while (p->pNext != head)
	{
		if (p->pNext->mon < 0.0)
			ans += " - ";
		else
			ans += " + ";
		ans += (p->pNext->mon).abs().ToString();
		p = p->pNext;
	}
	return ans;
}


void Polynom::clear()
{
	Node* tmp = head->pNext;
	while (tmp != head) {
		Node* tmp2 = tmp;
		tmp = tmp->pNext;
		delete tmp2;
	}
	head->pNext = head;
}

void Polynom::del_zeros()
{
	Node* tmp = head;
	while (tmp->pNext != head) {
		if (tmp->pNext->mon == 0.0) {
			Node* tmp2 = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;
			tmp = tmp->pNext;
			delete tmp2;
		}
		else tmp = tmp->pNext;
	}
}