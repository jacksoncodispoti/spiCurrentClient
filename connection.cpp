#include "connection.h"

int CommandConnection::open(){
	struct sockaddr_in serv_addr;

	if((m_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		std::cout << "Socket creation error" << std::endl;
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(m_port);

	if(inet_pton(AF_INET, m_addr, &serv_addr.sin_addr) <= 0){
		std::cout << "Invalid address" << std::endl;
		return -1;
	}
	
	if(connect(m_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
		std::cout << "Failed to connect" << std::endl;
		return -1;
	}

	return 0;
}

int CommandConnection::close(){
	//close(m_sock);
	m_sock = -1;
	return 0;
}

int CommandConnection::sendIDMessage(unsigned char id){
	char packet[8] = { AS_CMD_ID, 0, id, 0, 0, 0, 0, 0 };
	sendPacket(packet);
	return 0;
}

int CommandConnection::sendCurrentMessage(float current){
	char data[4];
	memcpy(data, &current, sizeof(float));

	char packet[8] = {AS_CMD_CUR, 0, 0x22, data[1], data[2], data[3], 0, 0 };

	sendPacket(packet);
	return 0;
}

int CommandConnection::sendPacket(char packet[8]){
	send(m_sock, packet, 8, 0);

	read(m_sock, m_commandBuffer, 8);
	executeCommand();
	return 0;
}

int CommandConnection::executeCommand(){
	char cmd = m_commandBuffer[0];

	unsigned short data = m_commandBuffer[1];
	data = data << 8;
	data = data | m_commandBuffer[2];

	switch(cmd){
		case SA_CMD_NULL:
			break;
		case SA_CMD_OFF:
			break;
		case SA_CMD_ON:
			break;
		case SA_CMD_INT:
			break;
		default:
			break;
	}

	return 0;
}
