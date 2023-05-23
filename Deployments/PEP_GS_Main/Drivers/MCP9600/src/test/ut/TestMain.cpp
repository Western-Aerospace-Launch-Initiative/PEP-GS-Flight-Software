#include <gtest/gtest.h>

extern "C"{
        #include "../../MCP9600.h"
}

TEST(TestTests, BasicAssertions){
        ASSERT_EQ(0, mcp_no_op());
}

