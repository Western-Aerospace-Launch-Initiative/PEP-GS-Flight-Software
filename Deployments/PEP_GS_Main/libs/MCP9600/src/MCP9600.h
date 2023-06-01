#pragma once

#ifndef _MCP_THERMOCOUPLE_H
#define _MCP_THERMOCOUPLE_H

#define BUFFER_SIZE 12 //Buffer size for accessing /dev/i2c-*

#define K_TYPE 0x00 // K-Type Thermocouple with no filter

#define HOT_JUNCTION_TEMPERATURE_REGISTER 0x00
#define STATUS_REGISTER 0x04
#define THERMOCOUPLE_SENSOR_TYPE_REGISTER 0x05
#define DEVICE_CONFIG_REGISTER 0x06

// All modes as are defined as 0.25C resolution 18 bit adc, 1 sample burst
#define NORMAL_MODE 0x00
#define SHUTDOWN_MODE 0x01
#define BURST_MODE 0x02

#define INIT_FILEDES -1
#define LOW_TEMP 0x80

#define HALF_SECOND 500000

#define ERROR_0 "ERROR 0: The device \"%s\" was unable to be opened.\n", bus
#define ERROR_1 "ERROR 1: The device address \"%d\" was found to be invalid.\n", pdevice->i2c_address
#define ERROR_2 "ERROR 2: The device \"%s\" is not enabled. Please enable it before continuing.\n", pdevice->ID
#define ERROR_3 "ERROR 3: Device \"%s\" was unable to close.\n", pdevice->ID
#define ERROR_4 "ERROR 4: Temperature read failed.\n"
#define ERROR_5 "ERROR 5: Device \"%s\" read failed.\n", pdevice->ID
#define ERROR_6 "ERROR_6: Device \"%s\" write failed.\n", pdevice->ID
#define ERROR_7 "ERROR_7: Device ID is larger than %d characters. Please shorten it.\n", BUFFER_SIZE


// Device configuration macro that takes the device handle, access register
// and value to write
#define MCP_CONFIGURE(DEVICE, DEVICE_CONFIG_REGISTER, REGISTER_VALUE) {\
        {\
            char config[2];\
            config[0] = DEVICE_CONFIG_REGISTER;\
            config[1] = REGISTER_VALUE;\
            write(DEVICE, config, 2);\
            }\
        }

typedef struct {
    int i2c_bus_int;
    int i2c_address;
    int filedes;
    char thermocouple_type;
    char enabled;
    char ID[BUFFER_SIZE];
} i2c_thermocouple;

i2c_thermocouple* mcp_thermocouple_init(
    int i2c_bus_int,
    int i2c_address,
    char thermocouple_type,
    char* ID
    );

int mcp_thermocouple_enable(i2c_thermocouple* pdevice);

int mcp_thermocouple_disable(i2c_thermocouple* pdevice);

float mcp_get_temp(i2c_thermocouple* pdevice);

char mcp_get_status(i2c_thermocouple* pdevice);

static int mcp_open_i2c_bus(i2c_thermocouple* pdevice);

static int mcp_close_i2c_bus(i2c_thermocouple* pdevice);

static void mcp_thermocouple_configure(i2c_thermocouple* pdevice);

static char* mcp_thermocouple_bus_to_string(int i2c_bus);

#endif /* _MCP_THERMOCOUPLE_H */
