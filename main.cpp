#include <iostream>
#include <stdlib.h>

#include "spi.h"
#include "connection.h"

#define MODE_INST 	0x01
#define MODE_RMS	0x02
const char* SERVER_ADDR = "192.168.1.199";
const int SERVER_PORT = 5942;
const int WEB_PORT = 5000;
const int DEVICE_ID = 37;

int fd;
unsigned char result;
unsigned int operatingMode = MODE_INST;
//unsigned int operatingMode = MODE_RMS;
char commandBuffer[128];

float getRealtimeCurrent();
float getRMSCurrent(unsigned int interval);
int postCurrent(float f);

int main (void) {
	std::cout << "Opening SPI connection..." << std::endl;
	fd = open("/dev/spidev0.0", O_RDWR);

	CommandConnection connection(SERVER_ADDR, SERVER_PORT);
	if(operatingMode == MODE_INST){
		std::cout << "Opening TCP connection.." << std::endl;
		connection.open();

		std::cout << "Sending ID" << std::endl;
		connection.sendIDMessage(DEVICE_ID);
	}


	std::cout << "Aligning SPI stream..." << std::endl;
	unsigned int speed = 1000000;
	ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	alignBuffer(fd);

	float current;
	while(1) {
		if(operatingMode == MODE_INST){
			current = readInstCurrent(fd);
			connection.sendCurrentMessage(current);
			usleep(SPI_TIMEOUT);
		}
		else{
			current = readRMSCurrent(fd, 250);
			postCurrent(current);
		}
	}
}

int postCurrent(float current){
	sprintf(commandBuffer, "curl %s:%d/postData --data '{\"current\":%f, \"id\":\"%d\"}'", SERVER_ADDR, WEB_PORT, current, DEVICE_ID);
	return system(commandBuffer);	
}
