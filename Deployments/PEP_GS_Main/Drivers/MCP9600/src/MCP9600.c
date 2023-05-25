#include <stdlib.h> // Defines printf()
#include <stdio.h> // Defines exit()
#include <string.h> // Defines snprintf()
#include <linux/i2c-dev.h> //Defines I2C_SLAVE
#include <sys/ioctl.h> // Defines ioctl()
#include <fcntl.h> // defines O_RDWR & open()
#include <unistd.h> // Includes sleep() write() and read()

#include "MCP9600.h"


static char* mcp_thermocouple_bus_to_string(i2c_thermocouple device) {
   if (device.i2c_bus > 3 || device.i2c_bus < 1) {
        return "";
    } else {
        static char buffer[BUFFER_SIZE];
        snprintf(buffer, BUFFER_SIZE, "/dev/i2c-%d", device.i2c_bus);
        return buffer;
    }
}

static int mcp_access_i2c_bus(i2c_thermocouple device) {
    int file;
    char* bus = mcp_thermocouple_bus_to_string(device);
    file = open(bus, O_RDWR);
    if (file < 0) {
        fprintf(stderr, 
        " ERROR 1: The device \"%s\" was unable to be opened.", 
        bus);
        exit(1);
    }
    if (ioctl(file, I2C_SLAVE, device.i2c_address) < 0) {
        fprintf(stderr, 
        "ERROR 2: The device address \"%d\" was found to be invalid.", 
        device.i2c_address);
        exit(1);
    }
    return file;
}

static void mcp_i2c_device_init(int file) {
    MCP_CONFIGURE(file, THERMOCOUPLE_SENSOR_TYPE, K_TYPE)
    MCP_CONFIGURE(file, DEVICE_CONFIG_REGISTER, NORMAL_MODE)
}

int mcp_thermocouple_enable(i2c_thermocouple device) {
    // Do Stuff
}

int mcp_thermocouple_disable(i2c_thermocouple device) {
    // Do Stuff
}

float mcp_get_temp(i2c_thermocouple device) {
    int file;
    file = mcp_access_i2c_bus(device);
    mcp_i2c_device_init(file);
    return 0.0;
}

int mcp_no_op() {
    return 0;
}
