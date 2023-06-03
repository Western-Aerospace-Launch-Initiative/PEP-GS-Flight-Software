#include <gtest/gtest.h>

extern "C"{
        #include "../../MCP9600.h"
}


TEST(MCP9600_Tests, mcp_device_enable_function){
    i2c_thermocouple device; 
    device.i2c_bus_int = 2;
    device.i2c_address = 0x70;
    device.thermocouple_type = K_TYPE;
    device.enabled = 0;
    strcpy(device.ID, "Test_Device");  

      
     
    {
        testing::internal::CaptureStderr();
        std::string CapturedError = testing::internal::GetCapturedStderr();
        std::string ExpectedError = "ERROR 3: The device \"Test_Device\" \
        is not enabled. Please enable it before continuing.";
        std::string str;
        EXPECT_PRED3([](auto str, auto CapturedError, auto ExpectedError) {
            return str == CapturedError || str == ExpectedError;}, 
            str, CapturedError, ExpectedError);
    }
    
    // Check device was enabled
    EXPECT_EQ(mcp_thermocouple_enable(&device), 0);
    
    // Verify Correct Values
    //EXPECT_STREQ(device.i2c_bus_str, "/dev/i2c-2");
    EXPECT_EQ(device.i2c_address, 0x70);
    EXPECT_EQ(device.thermocouple_type, K_TYPE);
    EXPECT_EQ(device.enabled, 1); // Only value that should change
    EXPECT_STREQ(device.ID, "Test_Device");
}

TEST(MCP9600_Tests, mcp_device_disable_function) {
    
}
