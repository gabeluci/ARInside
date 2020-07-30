#include "ARInsideTest.h"
#include "ARDayStructHelper.h"

TEST(ARDayStructHelperTests, OneDay)
{
	unsigned int interval = 86400;
	
	unsigned int days, hours, minutes, seconds;
	CARDayStructHelper::SplitInterval(interval, days, hours, minutes, seconds);

	ASSERT_EQ(1, days);
	ASSERT_EQ(0, hours);
	ASSERT_EQ(0, minutes);
	ASSERT_EQ(0, seconds);
}

TEST(ARDayStructHelperTests, Int17Hours)
{
	unsigned int interval = 61200;
	
	unsigned int days, hours, minutes, seconds;
	CARDayStructHelper::SplitInterval(interval, days, hours, minutes, seconds);

	ASSERT_EQ(0, days);
	ASSERT_EQ(17, hours);
	ASSERT_EQ(0, minutes);
	ASSERT_EQ(0, seconds);
}

TEST(ARDayStructHelperTests, Int57Mins)
{
	unsigned int interval = 3420;
	
	unsigned int days, hours, minutes, seconds;
	CARDayStructHelper::SplitInterval(interval, days, hours, minutes, seconds);

	ASSERT_EQ(0, days);
	ASSERT_EQ(0, hours);
	ASSERT_EQ(57, minutes);
	ASSERT_EQ(0, seconds);
}

TEST(ARDayStructHelperTests, Int15Sec)
{
	unsigned int interval = 15;
	
	unsigned int days, hours, minutes, seconds;
	CARDayStructHelper::SplitInterval(interval, days, hours, minutes, seconds);

	ASSERT_EQ(0, days);
	ASSERT_EQ(0, hours);
	ASSERT_EQ(0, minutes);
	ASSERT_EQ(15, seconds);
}

TEST(ARDayStructHelperTests, AllMixedInterval)
{
	unsigned int interval = 884725;
	
	unsigned int days, hours, minutes, seconds;
	CARDayStructHelper::SplitInterval(interval, days, hours, minutes, seconds);

	ASSERT_EQ(10, days);
	ASSERT_EQ(5, hours);
	ASSERT_EQ(45, minutes);
	ASSERT_EQ(25, seconds);
}
