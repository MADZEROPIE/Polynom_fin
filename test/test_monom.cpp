#include "polynom.h"

#include <gtest.h>

TEST(Monom, can_create_monom)
{
	ASSERT_NO_THROW(Polynom::Monom());
}

TEST(Monom, can_set_and_get_deg)
{
	Polynom::Monom mon;
	std::vector < int32_t> vec = { 15, 10, 5 };
	mon.set_deg(vec[0], vec[1], vec[2]);
	EXPECT_EQ(true, vec == mon.get_deg());
}

TEST(Monom, cant_set_big_deg)
{
	Polynom::Monom mon;
	ASSERT_ANY_THROW(mon.set_deg(maxp, 2, 5));
}

TEST(Monom, cant_set_neg_deg)
{
	Polynom::Monom mon;
	ASSERT_ANY_THROW(mon.set_deg(-1, -2, 5));
	
}
