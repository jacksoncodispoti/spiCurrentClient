#ifndef CONNECTION_H
#define CONNECTION_H
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#define SA_CMD_NULL 	0x00
#define SA_CMD_OFF	0x01
#define SA_CMD_ON	0x02
#define SA_CMD_INT	0x03

#define AS_CMD_NULL	0x00
#define AS_CMD_CUR	0x01
#define AS_CMD_ID	0x02

class CommandConnection{
public:
	CommandConnection(const char* addr, int port): m_addr(addr), m_port(port) {}
	int open();
	int close();
	int sendIDMessage(unsigned char id);
	int sendCurrentMessage(float current);

private:
	const char* m_addr;
	int m_port;
	int m_sock;	
	int sendPacket(char packet[8]);
	int executeCommand();

	char m_commandBuffer[8];
};

#endif
