#include "spi.h"

void alignBuffer(int fd){
	while(spiTxRx(fd, 0x00) != 0){}
}

int readValue(int fd){
	usleep(SPI_TIMEOUT);
	int byte0 = spiTxRx(fd, 0x00);
	usleep(SPI_TIMEOUT);
	int byte1 = spiTxRx(fd, 0x00);
	usleep(SPI_TIMEOUT);
	spiTxRx(fd, 0x00);

	int value = byte1 * 256 + byte0;
	
	return value;
}

int spiTxRx(int fd, unsigned char txDat) {
	unsigned char rxDat = 0;

	struct spi_ioc_transfer spi;
	memset (&spi, 0, sizeof (spi));

	spi.tx_buf        = (unsigned long)&txDat;
	spi.rx_buf        = (unsigned long)&rxDat;
	spi.len           = 1;

	ioctl(fd, SPI_IOC_MESSAGE(1), &spi);

	return rxDat;
}

long timeSince(struct timeval* start_time){
	struct timeval current_time;
	gettimeofday(&current_time, NULL);

	long seconds = current_time.tv_sec - start_time->tv_sec;
	long useconds = current_time.tv_usec - start_time->tv_usec;

	return (long)((seconds * 1000) + (useconds / 1000.0));
}

//This is using the 30 A version of the chip, so the scaling factors are according to the following:
//http://henrysbench.capnfatz.com/henrys-bench/arduino-current-measurements/acs712-current-sensor-user-manual/
//Voltage output by the device is 2.5V for 0A
//Because this is AC, this will tend to fluctate and we need to measure over a period of time
//Also, we're using floats because the max precision of the analog reading is only 10 bits
int defaultPollingTime = 500; //Poll voltage for 500ms
float voltsPerAmpere = 0.066f;

float readInstCurrent(int fd){
	int analog = readValue(fd);
	return 60.0 / 1024.0 * analog - 30.0;
}

float readRMSCurrent(int fd, int pollingTime){
	struct timeval start_time;
	gettimeofday(&start_time, NULL);

	float maxCurrent = 0;

	while(timeSince(&start_time) < pollingTime){
		float instCurrent = readInstCurrent(fd);
		if(instCurrent > maxCurrent)
			maxCurrent = instCurrent;
	}

	return maxCurrent * 0.7071;
}
