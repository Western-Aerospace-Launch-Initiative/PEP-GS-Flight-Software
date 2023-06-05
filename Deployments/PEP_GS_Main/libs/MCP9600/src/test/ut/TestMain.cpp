#include <gtest/gtest.h>

extern "C"{
        #include "../../MCP9600.h"
}

TEST(MCP9600_Tests, mcp_thermocouple_init_function){
    i2c_thermocouple device;
    mcp_thermocouple_init(1, 0x67, K_TYPE, "Init Device");

    ASSERT_EQ(device.i2c_address, 1);
    ASSERT_EQ(device.i2c_address, 0x67);
    ASSERT_STREQT_EQ(device.filedes, -1);
    ASSERT_STREQT_EQ(device.thermocouple_type, K_TYPE);
    ASSERT_EQ(device.enabled, 0);
    ASSERT_STREQ(device.id, "Init Device");
}

TEST(MCP9600_Tests, mcp_device_enable_function){
    i2c_thermocouple* device; 
    device = mcp_thermocouple_init(2, 0x70, K_TYPE, "enable_device");
     
    mcp_thermocouple_enable(device);

    {
        testing::internal::CaptureStderr();
        std::string CapturedError = testing::internal::GetCapturedStderr();
        std::string ExpectedError = ERROR_8;
        std::string str;
        EXPECT_PRED3([](auto str, auto CapturedError, auto ExpectedError) {
            return str == CapturedError || str == ExpectedError;}, 
            str, CapturedError, ExpectedError);
    }

    // Fix error
    device.enabled = 0;

    // Check device is enabled
    ASSERT_EQ(mcp_thermocouple_enable(device), 0);
    
    // Verify Correct Values
    ASSERT_EQ(device.i2c_address, 0x70);
    ASSERT_EQ(device.thermocouple_type, K_TYPE);
    ASSERT_EQ(device.enabled, 1); // Only value that should change
    ASSERT_STREQ(device.ID, "enable_device");
    close(device.filedes);

}

TEST(MCP9600_Tests, mcp_device_disable_function) {
    i2c_thermocouple* device;
    device = mcp_thermocouple_init(2, 0x69, K_TYPE, "diable_test");
    
    mcp_thermocouple_disable(&device);

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

    mcp_thermocouple_enable(&device);

    EXPECT_EQ(mcp_thermocouple_disable(&device), 0);  
    
    // Verify values
    EXPECT_EQ(device.i2c_bus_int, 2);
    EXPECT_EQ(device.i2c_address, 0x69);
    EXPECT_EQ(device.filedes, -1);
    EXPECT_EQ(device.thermocouple_type, K_TYPE);
    EXPECT_EQ(device.enabled, 0);
    EXPECT_STREQ(device.ID, "disable_test");
    
}

TEST(MCP9600_Tests, mcp_get_temp_function) {
    i2c_thermocouple* device; 

    device = mcp_thermocouple_init(2, 0x60, K_TYPE, "temp_test");
    mcp_thermocouple_enable(device);
    EXPECT_GT(mcp_get_temperature(device), 10.0); //Terrible tests find a better way to do it
    EXPECT_LT(mcp_get_temperature(device), 40.0);
    mcp_thermocouple_disable(device);
}

TEST(MCP9600_Tests, mcp_get_status_function){
    i2c_thermocouple* device;
    device = mcp_thermocouple_init(2, 0x60, K_TYPE, "status_test");
    EXPECT_EQ(mcp_get_status(device), 0xff);

    {
        testing::internal::CaptureStderr();
        std::string CapturedError = testing::internal::GetCapturedStderr();
        std::string ExpectedError = ERROR_2;
        std::string str;
        EXPECT_PRED3([](auto str, auto CapturedError, auto ExpectedError) {
            return str == CapturedError || str == ExpectedError;}, 
            str, CapturedError, ExpectedError);
    }

}
