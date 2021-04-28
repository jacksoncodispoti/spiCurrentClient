CC = g++
CFLAGS = -Wall

debug:
	$(CC) $(CFLAGS) -g -O0 spi.cpp connection.cpp main.cpp -o spiClient
release:
	$(CC) $(CFLAGS) -O5 spi.cpp connection.cpp main.cpp -o spiClient

clean:
	rm spiClient
