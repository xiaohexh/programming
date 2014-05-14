#include "TestTimeStamp.hh"
#include "TimeStamp.hh"

void TestTimeStamp::SetUpTestCase()
{
}

void TestTimeStamp::TearDownTestCase()
{
}

TEST_F(TestTimeStamp, xx)
{
	log4cpp::TimeStamp obj;
	EXPECT_EQ(::time(NULL), obj.getSeconds());
}
