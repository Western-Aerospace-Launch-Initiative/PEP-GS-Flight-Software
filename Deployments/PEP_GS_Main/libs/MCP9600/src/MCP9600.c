#include <stdlib.h> // Defines printf()
#include <stdio.h> // Defines exit()
#include <string.h> // Defines snprintf()
#include <linux/i2c-dev.h> //Defines I2C_SLAVE
#include <sys/ioctl.h> // Defines ioctl()
#include <fcntl.h> // defines O_RDWR & open()
#include <unistd.h> // Includes sleep() write() and read() and close()

#include "MCP9600.h"


static void mcp_thermocouple_bus_to_string(i2c_thermocouple* pdevice) {
   if (pdevice->i2c_bus_int >= 3 || pdevice->i2c_bus < 1) {
        pdevice->i2c_bus_str = "";
    } else {
        static char buffer[BUFFER_SIZE];
        snprintf(buffer, BUFFER_SIZE, "/dev/i2c-%d", i2c_bus);
        pdevice->i2c_bus_str =  buffer;
    }
}

static void mcp_open_i2c_bus(i2c_thermocouple* pdevice) {
    int filedes;
    char* bus = mcp_thermocouple_bus_to_string(pdevice->i2c_bus);
    filedes = open(bus, O_RDWR);
    if (filedes < 0) {
        fprintf(stderr, 
        " ERROR 1: The device \"%s\" was unable to be opened.\n", 
        bus);
        exit(1);
    }
    pdevice->filedes = filedes;
    if (ioctl(filedes, I2C_SLAVE, pdevice->i2c_address) < 0) {
        fprintf(stderr, 
        "ERROR 2: The device address \"%d\" was found to be invalid.\n", 
        pdevice->i2c_address);
        exit(1);
    }
}

static void mcp_close_i2c_bus(i2c_thermocouple* pdevice) {
    if (close(pdevice->filedes) < 0) {
        fprintf(stderr, "ERROR 4: I2C bus %d was unable to close.\n", pdevice->i2c_bus);
    }
    pdevice->filedes = -1;
}

/*
static void mcp_i2c_device_init(i2c_thermocouple* pdevice) {
    MCP_CONFIGURE(pdevice->file_ref, THERMOCOUPLE_SENSOR_TYPE_REGISTER, pdevice->thermocouple_type)
    MCP_CONFIGURE(pdevice->file_ref, DEVICE_CONFIG_REGISTER, NORMAL_MODE)
}
*/

int mcp_thermocouple_enable(i2c_thermocouple* pdevice) { 
    mcp_open_i2c_bus(pdevice); 
    MCP_CONFIGURE(pdevice->filedes, THERMOCOUPLE_SENSOR_TYPE_REGISTER, pdevice->thermocouple_type)
    MCP_CONFIGURE(pdevice->filedes, DEVICE_CONFIG_REGISTER, NORMAL_MODE)
    mcp_close_i2c_bus(pdevice);
    pdevice->device_enabled = 1;
    return 0;
}

int mcp_thermocouple_disable(i2c_thermocouple* pdevice) {
    mcp_open_i2c_bus(pdevice);
    MCP_CONFIGURE(pdevice->filedes, DEVICE_CONFIG_REGISTER, SHUTDOWN_MODE)
    mcp_close_i2c_bus(pdevice);
    pdevice->device_enabled = 0;
    return 0;
}

float mcp_get_temp(i2c_thermocouple* pdevice) {
    float temp = 0.0;
    if (pdevice->device_enabled == 0) {
        fprintf(stderr, "ERROR 3: The device \"%s\" is not enabled. Please enable it before continuing.\n", pdevice->device_ID);
        exit(1);
    }
    mcp_open_i2c_bus(pdevice);
    // Get temp
    mcp_close_i2c_bus(pdevice);
    return temp;
}

int mcp_no_op() {
    return 0;
}
