#include "polynom.h"

#include <gtest.h>

TEST(Polynom, can_create_polynom)
{
	ASSERT_NO_THROW(Polynom());
}

TEST(Polynom, can_create_polynom_from_string)
{
	ASSERT_NO_THROW(Polynom("10x3y4z5+5z-y"));
}

TEST(Polynom, can_create_polynom_from_string_2)
{
	ASSERT_NO_THROW(Polynom("10x3y4z5+5z-y+2xz"));
}

TEST(Polynom, can_create_polynom_from_string_and_check)
{
	std::string s = "10x3y4z5+5z-y";
	Polynom a(s);
	std::string res = "10x3y4z5-y+5z";//Отсортирован в правильном порядке
	ASSERT_EQ(res, a.ToString());
}

TEST(Polynom, can_create_polynom_from_string_2_and_check)
{
	std::string s = "10x3y4z5+5z-y+2xz";
	Polynom a(s);
	std::string res = "10x3y4z5+2xz-y+5z";
	ASSERT_EQ(res, a.ToString());
}

TEST(Polynom, can_summ_polynoms)
{
	std::string s1 = "10x3y4z5+5z-y+2xz";
	std::string s2 = "x-y";
	Polynom a(s1);
	Polynom b(s2);
	Polynom res(s1 +'+'+ s2);
	ASSERT_EQ(res.ToString(), (a+b).ToString());
}

TEST(Polynom, can_mult_polynoms)
{
	std::string s1 = "10x3y4z5+5z";
	std::string s2 = "x-y";
	Polynom a(s1);
	Polynom b(s2);
	Polynom res("10x4y4z5+5xz-10x3y5z5-5yz");
	ASSERT_EQ(res.ToString(), (a * b).ToString());
}