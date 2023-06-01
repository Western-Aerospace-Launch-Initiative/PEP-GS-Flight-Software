#include <stdlib.h> // Defines printf()
#include <stdio.h> // Defines exit()
#include <string.h> // Defines snprintf()
#include <linux/i2c-dev.h> //Defines I2C_SLAVE
#include <sys/ioctl.h> // Defines ioctl()
#include <fcntl.h> // defines O_RDWR & open()
#include <unistd.h> // Includes sleep() write() and read() and close()

#include "MCP9600.h"

i2c_thermocouple* mcp_thermocouple_init(
    int i2c_bus_int,
    int i2c_address,
    char thermocouple_type,
    char* ID
    ) {

    if (strlen(ID) > BUFFER_SIZE) {
        fprintf(stderr, ERROR_7);
        return 0;
    }

    static i2c_thermocouple device;
    
    device.i2c_bus_int = i2c_bus_int;
    device.i2c_address = i2c_address;
    device.filedes = INIT_FILEDES;
    device.thermocouple_type = thermocouple_type;
    strcpy(device.ID, ID);
    return &device;
}

int mcp_thermocouple_enable(i2c_thermocouple* pdevice) {
        
    mcp_open_i2c_bus(pdevice);
    pdevice->enabled = 1;
    usleep(HALF_SECOND);
    return 0;
}

int mcp_thermocouple_disable(i2c_thermocouple* pdevice) {
    mcp_close_i2c_bus(pdevice);
    pdevice->enabled = 0;
    return 0;
}

float mcp_get_temp(i2c_thermocouple* pdevice) {
   
    if (!pdevice->enabled) {
        fprintf(stderr, ERROR_2);
        return 0.0;
    }

    char reg[1] = {0x00};
    if (write(pdevice->filedes, reg, 1) < 0) {
        fprintf(stderr, ERROR_6);
        return -1;
    }

    char data[2] = {0};
    if (read(pdevice->filedes, data, 2) != 2) {
        fprintf(stderr, ERROR_4);
        return 0;
    } else {
          if  (data[0] & 0x80) { // if low temp
              return data[0] * 16 + data[1] / 16.0 - 4096;
        } else {
              return data[0] * 16 + data[1] / 16.0;
        }
    }
}

char mcp_get_status(i2c_thermocouple* pdevice) {
    
    if (!pdevice->enabled) {
        fprintf(stderr, ERROR_2);
        return 0xff;
    }

    char reg[1] = {0};
    reg[0] = 0x04;

    if(write(pdevice->filedes, reg, 1) < 0) {
        fprintf(stderr, ERROR_6);
        return -1;
    }

    char data[1] = {0};

    if(read(pdevice->filedes, data, 1) != 1) {
        fprintf(stderr, ERROR_5);
        return 0xff;
    }

    return data[0]; 
}

static int mcp_open_i2c_bus(i2c_thermocouple* pdevice) {
   
    char* bus = mcp_thermocouple_bus_to_string(pdevice->i2c_bus_int);
    if ((pdevice->filedes = open(bus, O_RDWR)) < 0) {
        fprintf(stderr, ERROR_0);
        return -1;
    }
    
    ioctl(pdevice->filedes, I2C_SLAVE, pdevice->i2c_address);

    MCP_CONFIGURE(pdevice->filedes, THERMOCOUPLE_SENSOR_TYPE_REGISTER, K_TYPE)
    MCP_CONFIGURE(pdevice->filedes, DEVICE_CONFIG_REGISTER, NORMAL_MODE)
    return 0;
}

static int mcp_close_i2c_bus(i2c_thermocouple* pdevice) {
    
    MCP_CONFIGURE(pdevice->filedes, DEVICE_CONFIG_REGISTER, SHUTDOWN_MODE)
    if (close(pdevice->filedes) < 0) {
        fprintf(stderr, ERROR_3);
        return -1;
    }
    return 0;
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
