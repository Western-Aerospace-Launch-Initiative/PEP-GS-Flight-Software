#pragma once

typedef struct {
    int i2c_bus;
    int i2c_address;
} i2c_thermocouple;

int mcp_thermocouple_init(i2c_thermocouple device);

int mcp_thermocouple_enable(i2c_thermocouple device);

int mcp_thermcouple_disable(i2c_thermocouple device);

float mcp_get_temp(i2c_thermocouple device);

int mcp_no_op();
