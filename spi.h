#ifndef SPI_H
#define SPI_H

#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <math.h>
#include <sys/time.h>
#include <iostream>

#define SPI_TIMEOUT 10
void alignBuffer(int fd);
int spiTxRx(int fd, unsigned char data);
int readValue(int fd);
float readInstCurrent(int fd);
float readRMSCurrent(int fd, int pollingTime);

#endif
