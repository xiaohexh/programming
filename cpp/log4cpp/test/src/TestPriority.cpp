#include "TestPriority.hh"
#include "Priority.hh"

void TestPriority::SetUpTestCase()
{
}

void TestPriority::TearDownTestCase()
{
}

TEST_F(TestPriority, getPriorityName)
{
	log4cpp::Priority obj;
	EXPECT_STREQ("FATAL", obj.getPriorityName(0).c_str());
	EXPECT_STREQ("ALERT", obj.getPriorityName(100).c_str());
	EXPECT_STREQ("NOTSET", obj.getPriorityName(900).c_str());
}

TEST_F(TestPriority, getPriorityValue)
{
	log4cpp::Priority obj;
	EXPECT_EQ(0, obj.getPriorityValue("FATAL"));
	EXPECT_EQ(100, obj.getPriorityValue("ALERT"));
}
