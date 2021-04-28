# spiCurrentClient
This program reads current measurements through an SPI interface.

These reads input from an SPI device on /dev/spidev0.0, then depending on the operating mode, sends instantaneous
or RMS current to a specified server.

## Connection Settings
Server IP, and ports can be configured at the top of main.cpp.

## Operating modes
There's 2 operating modes which can be changed in source at main.cpp:16:
* MODE_INST - Instantaneous current
* MODE_RMS - RMS current of 250ms interval

## SPI Connection
You can change the /dev/ path at main.cpp:26.
You can change the baud rate of the connection at main.cpp:39. Default is 1,000,000 Hz.
