#pragma once

#ifndef BUFFER_SIZE
#define BUFFERSIZE 12
#endif



typedef struct {
    int i2c_bus;
    int i2c_address;
} i2c_thermocouple;

static char* mcp_thermocouple_bus_to_string(i2c_thermocouple device);

static int mcp_access_i2c_bus(i2c_thermocouple device);

static void mcp_i2c_device_init(int file);

int mcp_thermocouple_enable(i2c_thermocouple device);

int mcp_thermcouple_disable(i2c_thermocouple device);

float mcp_get_temp(i2c_thermocouple device);

int mcp_no_op();
