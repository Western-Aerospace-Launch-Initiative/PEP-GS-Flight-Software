#include <gtest/gtest.h>

extern "C"{
        #include "../../MCP9600.h"
}

TEST(MCP9600_Tests, BasicAssertions){
        ASSERT_EQ(0, mcp_no_op());
}


TEST(MCP9600_Tests, mcp_device_enable_function){
    i2c_thermocouple device = {2, 0x67, INIT_FILEDES, K_TYPE, 0, 'A'}; 
    ASSERT_EQ(0.0, mcp_get_temp(&device));
}

TEST(MCP9600_Tests, mcp_get_temp_check_valid_i2c_busses){

}
