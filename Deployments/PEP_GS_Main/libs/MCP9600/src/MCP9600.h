#pragma once

#ifndef _MCP_THERMOCOUPLE_H
#define _MCP_THERMOCOUPLE_H

#define BUFFER_SIZE 12 //Buffer size for accessing /dev/i2c-*

#define THERMOCOUPLE_SENSOR_TYPE_REGISTER 0x05
#define K_TYPE 0x00 // K-Type Thermocouple with no filter

#define DEVICE_CONFIG_REGISTER 0x06

// All modes as are defined as 0.25C resolution 18 bit adc, 1 sample burst
#define NORMAL_MODE 0x80
#define SHUTDOWN_MODE 0x81
#define BURST_MODE 0x82

#define INIT_FILEDES -1

// Device configuration macro that takes the device handle, access register 
// and value to write
#define MCP_CONFIGURE(DEVICE, DEVICE_CONFIG_REGISTER, REGISTER_VALUE) {\
        {\
            char config[2];\
            config[0] = DEVICE_CONFIG_REGISTER;\
            config[1] = REGISTER_VALUE;\
            write(DEVICE, config, 4);\
            }\
        }

typedef struct {
    union {
        int i2c_bus_int;
        char i2c_bus_str[BUFFER_SIZE];
    };
    //int i2c_bus;
    int i2c_address;
    int filedes;
    char thermocouple_type;
    char enabled;
    char device_ID[BUFFER_SIZE];
} i2c_thermocouple;

static char* mcp_thermocouple_bus_to_string(int i2c_bus);

static void mcp_open_i2c_bus(i2c_thermocouple* pdevice);

static void mcp_i2c_device_init(i2c_thermocouple* pdevice);

int mcp_thermocouple_enable(i2c_thermocouple* pdevice);

int mcp_thermcouple_disable(i2c_thermocouple* pdevice);

float mcp_get_temp(i2c_thermocouple* pdevice);

int mcp_no_op();

#endif /* _MCP_THERMOCOUPLE_H */
