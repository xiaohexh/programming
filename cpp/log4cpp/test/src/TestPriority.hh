#ifndef __LOG4CPP_TEST_PRIORITY_HH
#define __LOG4CPP_TEST_PRIORITY_HH

#include <gtest/gtest.h>

class TestPriority : public testing::Test
{
protected:
	static void SetUpTestCase();
	static void TearDownTestCase();
};

#endif // __LOG4CPP_TEST_PRIORITY_HH
