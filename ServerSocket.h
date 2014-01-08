#ifndef _SERVERSOCKET_H
#define _SERVERSOCKET_H


#include"Socket.h"
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/un.h>
class ServerSocket
{
private:
	int server_socket;
	int port;
	int backlog;
	struct sockaddr_in server_address;
	int server_len;
public:
	ServerSocket(int port,int backlog=5);
	int getPort();
	int bind();
	int listen();
	void close();
	int accept();
	~ServerSocket();
};

#endif
