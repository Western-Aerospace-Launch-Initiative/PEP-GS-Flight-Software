#include <gtest/gtest.h>

extern "C"{
        #include "../../MCP9600.h"
}


TEST(MCP9600_Tests, mcp_device_enable_function){
     i2c_thermocouple device; 
    device.i2c_bus_int = 2;
    device.i2c_address = 0x76;
    device.thermocouple_type = K_TYPE;
    device.enabled = 0;
    strcpy(device.device_ID, "Test_Device");  

      
     
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
    
    // Verify no values changed
    {
        std::string i2c_bus = device.i2c_bus_str;
        std::string i2c_bus_reference = "/dev/i2c-2";
        std::string str;
        EXPECT_PRED3([](auto str, auto i2c_bus, auto i2c_bus_reference) {
            return str == i2c_bus || str == i2c_bus_reference;}, 
            str, i2c_bus, i2c_bus_reference);
    }

    EXPECT_EQ(device.i2c_address, 0x76);
    EXPECT_EQ(device.thermocouple_type, K_TYPE);
    EXPECT_EQ(device.enabled, 1); // Only value that should change
   
   {
        std::string i2c_device_ID = device.device_ID;
        std::string i2c_device_ID_reference = "Test_Device";
        std::string str;
        EXPECT_PRED3([](auto str, auto i2c_device_ID, 
            auto i2c_device_ID_reference) {
            return str == i2c_device_ID || str == i2c_device_ID_reference;}, 
            str, i2c_device_ID, i2c_device_ID_reference);
    } 
}

TEST(MCP9600_Tests, mcp_device_disable_function) {
    
}
