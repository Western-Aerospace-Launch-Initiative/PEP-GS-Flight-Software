#include <gtest/gtest.h>

extern "C"{
        #include "../../MCP9600.h"
}

TEST(MCP9600_Tests, BasicAssertions){
        ASSERT_EQ(0, mcp_no_op());
}


TEST(MCP9600_Tests, mcp_device_enable_function){
    i2c_thermocouple device; // = {2, 0x67, INIT_FILEDES, K_TYPE, 0, };
    device.i2c_bus_int = 2;
    device.i2c_address = 0x76;
    device.thermocouple_type = K_TYPE;
    device.device_enabled = 0;
    device.device_ID = "Device_1";
    ASSERT_EQ(0.0, mcp_get_temp(&device));
}

TEST(MCP9600_Tests, mcp_get_temp_check_valid_i2c_busses){

}
