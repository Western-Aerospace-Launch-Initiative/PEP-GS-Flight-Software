//
// File Name: MCP9600.c
// Creation Date: 2/7/2023
// Author: Nathan Snyder
//
//***********************************************
//
// Revision 001
// Revision Date: 5/3/2023
// Revision Author: Noah Braasch
//
//***********************************************
//
// Software acts as a driver for the MCP9600
// thermocouple board. Driver uses I2C 
//
//***********************************************

#include <stdio.h> // io interface. Might not need it anymore
#include <stdlib.h> // Stdlibrary. Probably need it
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef I2C_BUS_ADDRESS
#define I2C_BUS_ADDRESS 0x60
#endif

float getTemp(int file, int address);


int main(int argc, char** argv) {
	
    int file;
	char *bus = "/dev/i2c-2"; // Path to bus

	if ((file = open(bus, O_RDWR)) < 0) { // If cant open bus
        exit(1);
	}
    	printf("%f", getTemp(file, I2C_BUS_ADDRESS));
        return 0;
}

float getTemp(int file, int address) {

	ioctl(file, I2C_SLAVE, address);

	char config[2] = {0};
	config[0] = 0x05;
	config[1] = 0x00;
	write(file, config, 2);
	config[0] = 0x06;
	config[1] = 0x00;
	write(file, config, 2);

	// check status flag
	char reg1[1] = {0};
	reg1[1] = 0x04;
	write(file, reg1, 1);

	//char stat[1] = {0};
	char data1[1] = {0};

	if(read(file, data1, 1) != 1) {
    	return 0;
	} else {
		char stat = (data1[1]);
	/*	
        printf("Stat   ");
		printf("%x",stat);
		printf("   \n");
	*/
    }
	char reg[1] = {0x00};
	write(file, reg, 1);
	char data[2] = {0};

	if(read(file, data, 2) != 2) {
    	printf("Erorr : Input/output Erorr \n");
	} else {
        int low_temp = data[0] & 0x80;
		float r;
		if (low_temp) {
            // printf("Low temp\n");
         	r = data[0] * 16 + data[1] / 16 - 4096;
            return r;
        } else {
			// printf("High temp\n");
			r = data[0] * 16 + data[1] * 0.0625;
           	return r;
           	sleep(1);
        }
    }
}
