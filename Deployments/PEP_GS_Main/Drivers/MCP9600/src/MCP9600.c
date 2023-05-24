#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "MCP9600.h"


int mcp_thermocouple_init(i2c_thermocouple device) {
    // Do Stuff
}

int mcp_thermocouple_enable(i2c_thermocouple device) {
    // Do Stuff
}

int mcp_thermocouple_disable(i2c_thermocouple device) {
    // Do Stuff
}

float mcp_get_temp(i2c_thermocouple device) {
    int file;
    const int BUFFER_SIZE = 12;
    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, "/dev/i2c-%d", device.i2c_bus);
    return 0.0;
}

int mcp_no_op() {
    return 0;
}
