#include <gtest/gtest.h>

extern "C"{
        #include "../../MCP9600.h"
}

TEST(MCP9600_Tests, BasicAssertions){
        ASSERT_EQ(0, mcp_no_op());
}


TEST(MCP9600_Tests, GetTempAssertion){
    i2c_thermocouple device = {2, 0x67}; 
    ASSERT_EQ(0.0, mcp_get_temp(device));
}
