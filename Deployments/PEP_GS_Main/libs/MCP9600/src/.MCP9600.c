#include <stdlib.h> // Defines printf()
#include <stdio.h> // Defines exit()
#include <string.h> // Defines snprintf()
#include <linux/i2c-dev.h> //Defines I2C_SLAVE
#include <sys/ioctl.h> // Defines ioctl()
#include <fcntl.h> // defines O_RDWR & open()
#include <unistd.h> // Includes sleep() write() and read() and close()

#include "MCP9600.h"

<<<<<<< HEAD


int mcp_thermocouple_enable(i2c_thermocouple* pdevice) { 
    printf("Stating thermocouple enable\n");
    printf("Opening device\n");
    print_all_info(pdevice);

    mcp_open_i2c_bus(pdevice);
    
    printf("Configuring data\n");
    print_all_info(pdevice);

    MCP_CONFIGURE(pdevice->filedes, THERMOCOUPLE_SENSOR_TYPE_REGISTER, 
        pdevice->thermocouple_type)
    MCP_CONFIGURE(pdevice->filedes, DEVICE_CONFIG_REGISTER, NORMAL_MODE)

    printf("closing device\n");
    print_all_info(pdevice);
    
    mcp_close_i2c_bus(pdevice);
    pdevice->enabled = 1;
    
    printf("Returning 0\n");
    print_all_info(pdevice);
    
=======
int main() {
   
    /*
    i2c_thermocouple device;
    device.i2c_bus_int = 2;
    device.i2c_address = 0x60;
    device.filedes = -1;
    device.thermocouple_type = K_TYPE;
    device.enabled = 0;
    strcpy(device.ID, "Test device");
    */

    i2c_thermocouple* device = mcp_thermocouple_init(2, 0x60, K_TYPE, "Test device");

    mcp_thermocouple_enable(device);    

    char status = mcp_get_status(device);
    printf("status: %x\n", status);
    float temp1 = mcp_get_temp(device);
    printf("%f\n", temp1);
    mcp_thermocouple_disable(device);
}

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
>>>>>>> complete-refactor
    return 0;
}

int mcp_thermocouple_disable(i2c_thermocouple* pdevice) {
<<<<<<< HEAD
    printf("opening bus\n");
    print_all_info(pdevice);

    mcp_open_i2c_bus(pdevice);
    
    printf("Assigning filedes and checking enabled\n");
    print_all_info(pdevice);

    int filedes = pdevice->filedes;
    if (pdevice->enabled == 0) {
        fprintf(stderr, ERROR_2);
        exit(1);
    }

    printf("comfigring data\n");
    print_all_info(pdevice);

    MCP_CONFIGURE(filedes, DEVICE_CONFIG_REGISTER, SHUTDOWN_MODE)
    
    printf("closing device\n");
    print_all_info(pdevice);

=======
>>>>>>> complete-refactor
    mcp_close_i2c_bus(pdevice);
    pdevice->enabled = 0;

    printf("device disabled and returning 0\n");
    print_all_info(pdevice);
    return 0;
}

float mcp_get_temp(i2c_thermocouple* pdevice) {
<<<<<<< HEAD
    printf("opening bus\n");
    print_all_info(pdevice);
 
    float temperature = 0.0;
    mcp_open_i2c_bus(pdevice);
    
    printf("Assigning filedes and checking enabled\n");
    print_all_info(pdevice);
 
    int filedes = pdevice->filedes;
    if (pdevice->enabled == 0) {
=======
   
    if (!pdevice->enabled) {
>>>>>>> complete-refactor
        fprintf(stderr, ERROR_2);
        return 0.0;
    }

<<<<<<< HEAD
    printf("getting status\n");
    print_all_info(pdevice);

    mcp_get_status(pdevice);

    printf("writing to hot junction register\n");
    print_all_info(pdevice);

    char data[2];
    char reg[1] = {HOT_JUNCTION_TEMPERATURE_REGISTER};
    write(filedes, reg, 1);
    
    printf("Reading temperature data\n");
    print_all_info(pdevice);

    if (read(filedes, data, 2) != 2) {
        fprintf(stderr, ERROR_4);
    }


    printf("calculating temperature\n");
    print_all_info(pdevice);

    if ((data[0] & LOW_TEMP) == LOW_TEMP) {
        temperature = (data[0] * 16 + data[1] / 16.0) - 4096;
    } else {
        temperature = (data[0] * 16 + data[1] / 16.0);
    }

    printf("closing device\n");
    print_all_info(pdevice);

    mcp_close_i2c_bus(pdevice);

    printf("returning 0\n");
    print_all_info(pdevice);

    return temperature;
}

int mcp_get_status(i2c_thermocouple* pdevice) {
    
    printf("setting filedes\n");
    print_all_info(pdevice);

    int filedes = pdevice->filedes;

    printf("opening bus");
    print_all_info(pdevice);

    mcp_open_i2c_bus(pdevice);

    printf("check device enabled");
    print_all_info(pdevice);

    if (pdevice->enabled == 0) {
=======
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
>>>>>>> complete-refactor
        fprintf(stderr, ERROR_2);
        return 0xff;
    }

<<<<<<< HEAD
    printf("writing to status register");
    print_all_info(pdevice);

    char val[1];
    char data[1];
    val[0] = STATUS_REGISTER;
    write(filedes, val, 1);

    printf("reading status register");
    print_all_info(pdevice);

    if (read(filedes, data, 1) != 1) {
        printf("Closing on failure");
        print_all_info(pdevice);
        mcp_close_i2c_bus(pdevice);
        exit(1);
    } else {

        printf("closing on success");
        print_all_info(pdevice);

        mcp_close_i2c_bus(pdevice);
        
        printf("returning data");
        print_all_info(pdevice);
    
        return data[0];
=======
    char reg[1] = {0};
    reg[0] = 0x04;

    if(write(pdevice->filedes, reg, 1) < 0) {
        fprintf(stderr, ERROR_6);
        return -1;
>>>>>>> complete-refactor
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
<<<<<<< HEAD
    //pdevice->filedes = -1;
=======
    return 0;
>>>>>>> complete-refactor
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

static void print_all_info(i2c_thermocouple* pdevice) {
    printf("\n");
    printf("i2c_bus_int: %d\n", pdevice->i2c_bus_int);
    printf("i2c_address: %d\n", pdevice->i2c_address);
    printf("filedes: %d\n", pdevice->filedes);
    printf("thermocouple type: %x\n", pdevice->thermocouple_type);
    printf("enabled: %d\n", pdevice->enabled);
    printf("device_ID: %s\n", pdevice->ID);
    printf("\n");
}
