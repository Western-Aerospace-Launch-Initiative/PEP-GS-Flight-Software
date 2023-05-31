#include <stdlib.h> // Defines printf()
#include <stdio.h> // Defines exit()
#include <string.h> // Defines snprintf()
#include <linux/i2c-dev.h> //Defines I2C_SLAVE
#include <sys/ioctl.h> // Defines ioctl()
#include <fcntl.h> // defines O_RDWR & open()
#include <unistd.h> // Includes sleep() write() and read() and close()

#include "MCP9600.h"

int mcp_thermocouple_enable(i2c_thermocouple* pdevice) { 
    mcp_open_i2c_bus(pdevice); 
    MCP_CONFIGURE(pdevice->filedes, THERMOCOUPLE_SENSOR_TYPE_REGISTER, 
        pdevice->thermocouple_type)
    MCP_CONFIGURE(pdevice->filedes, DEVICE_CONFIG_REGISTER, NORMAL_MODE)
    mcp_close_i2c_bus(pdevice);
    pdevice->enabled = 1;
    return 0;
}

int mcp_thermocouple_disable(i2c_thermocouple* pdevice) {
    mcp_open_i2c_bus(pdevice);
    int filedes = pdevice->filedes;
    if (pdevice->enabled == 0) {
        fprintf(stderr, ERROR_2);
        exit(1);
    } 
    MCP_CONFIGURE(filedes, DEVICE_CONFIG_REGISTER, SHUTDOWN_MODE)
    mcp_close_i2c_bus(pdevice);
    pdevice->enabled = 0;
    return 0;
}

float mcp_get_temp(i2c_thermocouple* pdevice) {
    float temperature = 0.0;
    int filedes = pdevice->filedes;
    if (pdevice->enabled == 0) {
        fprintf(stderr, ERROR_2);
        exit(1);
    }
    mcp_open_i2c_bus(pdevice);
    char val[1];
    char data[2];
    write(filedes, HOT_JUNCTION_TEMPERATURE_REGISTER, 1);
    if (read(filedes, data, 2) != 2) {
        fprintf(stderr, ERROR_4);
    }
    if (data[0] & LOW_TEMP) {
        temperature = (data[0] * 16 + data[1] / 16) - 4096;
    } else {
        temperature = (data[0] * 16 + data[1] / 16);
    }
    mcp_close_i2c_bus(pdevice);
    return temperature;
}

int mcp_get_status(i2c_thermocouple* pdevice) {
    int filedes = pdevice->filedes;
    if (pdevice->enabled == 0) {
        fprintf(stderr, ERROR_2);
        exit(1);
    }
    mcp_open_i2c_bus(pdevice);
    char val[1];
    char data[1];
    val[0] = STATUS_REGISTER;
    write(filedes, val, 1);
    if (read(filedes, data, 1) != 1) {
        mcp_close_i2c_bus(pdevice);
        exit(1);
    } else {
        mcp_close_i2c_bus(pdevice);
        return data[1];
    }
}

static void mcp_open_i2c_bus(i2c_thermocouple* pdevice) {
    int filedes;
    int i2c_bus = pdevice->i2c_bus_int;
    strcpy(pdevice->i2c_bus_str, mcp_thermocouple_bus_to_string(i2c_bus));
    char* bus = pdevice->i2c_bus_str;
    filedes = open(bus, O_RDWR);
    if (filedes < 0) {
        fprintf(stderr, ERROR_0);
        exit(1);
    }
    pdevice->filedes = filedes;
    if (ioctl(filedes, I2C_SLAVE, pdevice->i2c_address) < 0) {
        fprintf(stderr, ERROR_1);
        exit(1);
    }
}

static void mcp_close_i2c_bus(i2c_thermocouple* pdevice) {
    if (close(pdevice->filedes) < 0) {
        fprintf(stderr, ERROR_3);
    }
    pdevice->filedes = -1;
}

static char* mcp_thermocouple_bus_to_string(int i2c_bus) {
   if (i2c_bus >= 3 || i2c_bus < 1) {
        return "";
    } else {
        static char buffer[BUFFER_SIZE];
        snprintf(buffer, BUFFER_SIZE, "/dev/i2c-%d", i2c_bus);
        return buffer;
    }
}
