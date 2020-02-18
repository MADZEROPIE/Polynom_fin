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

TEST(Monom, can_summ_monoms_with_equal_deg)
{
	Polynom::Monom mon1(1, 5, 7, 2.8);
	Polynom::Monom mon2(1, 5, 7, 2.512);
	Polynom::Monom exp_res(1,5,7, 2.8 + 2.512);
	Polynom::Monom act_res;
	EXPECT_NO_THROW(act_res=mon1 + mon2);
	EXPECT_EQ(exp_res.coef, act_res.coef);
}

TEST(Monom, can_sub_monoms_with_equal_deg)
{
	Polynom::Monom mon1(1, 5, 7, 2.8);
	Polynom::Monom mon2(1, 5, 7, 2.512);
	Polynom::Monom exp_res(1, 5, 7, 2.8 - 2.512);
	Polynom::Monom act_res;
	EXPECT_NO_THROW(act_res = mon1 - mon2);
	EXPECT_EQ(exp_res.coef, act_res.coef);
}

TEST(Monom, cant_summ_monoms_with_different_deg)
{
	Polynom::Monom mon1(1,5,7,2.8);
	Polynom::Monom mon2(12, 1, 134, 2.512);
	ASSERT_ANY_THROW(mon1+mon2);
}

TEST(Monom, can_mult_monoms)
{
	Polynom::Monom mon1(1, 5, 7, 2.8);
	Polynom::Monom mon2(1, 2, 17, 2.512);
	Polynom::Monom exp_res(2, 7, 7+17, 2.8 * 2.512);
	Polynom::Monom act_res=mon1;
	EXPECT_NO_THROW(act_res *= mon2);
	EXPECT_EQ(exp_res.coef, act_res.coef);
	EXPECT_EQ(exp_res.get_deg(), act_res.get_deg());
}

TEST(Monom, cant_mult_monoms_if_deg_is_too_big)
{
	Polynom::Monom mon1(500, 5, 7, 2.8);
	Polynom::Monom mon2(501, 2, 17, 2.512);
	ASSERT_ANY_THROW(mon1 *= mon2);
}

TEST(Monom, correct_comp_deg)
{
	Polynom::Monom mon1(500, 5, 7, 2.8);
	Polynom::Monom mon2(501, 2, 17, 2.512);
	EXPECT_EQ(mon1.pow_coef < mon2.pow_coef, mon1 < mon2);
	EXPECT_EQ(mon1.pow_coef <= mon2.pow_coef, mon1 <= mon2);
}

TEST(Monom, correct_comp_coef)
{
	Polynom::Monom mon(500, 5, 7, 2.8);
	real a = 2.5, b=2.8;
	EXPECT_EQ(mon.coef<=a,mon<=a);
	EXPECT_EQ(mon.coef==b,mon==b);
}
