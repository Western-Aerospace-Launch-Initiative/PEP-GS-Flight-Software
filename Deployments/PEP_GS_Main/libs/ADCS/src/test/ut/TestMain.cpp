#include <gtest/gtest.h>

extern "C"{
        #include "../../MCP9600.h"
}

TEST(ADCS_Tests, Basic_Assertions)
{
    ASSERT_EQ(1,1);
}
