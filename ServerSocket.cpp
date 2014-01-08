#include"ServerSocket.h"
#include"Socket.h"
#include<sys/socket.h>
#include<sys/un.h>
#include<netinet/in.h>


ServerSocket::ServerSocket(int port,int backlog)
{
	this->backlog=backlog;
	this->port=port;
	server_socket=socket(AF_INET,SOCK_STREAM,0);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port=htons(port);
	server_len=sizeof(server_address);
}
int ServerSocket::getPort()
{
	return port;
}
int ServerSocket::bind()
{
	return ::bind(server_socket,(struct sockaddr *)&server_address,server_len);
}
int ServerSocket::listen()
{
	return ::listen(server_socket,backlog);
}
void ServerSocket::close()
{
	::close(server_socket);
}
int ServerSocket::accept()
{
	struct sockaddr_in client_address;
	int client_len=sizeof(client_address);
	int client_socket = ::accept(server_socket,(struct sockaddr*)&client_address,(socklen_t*)&client_len);
	return client_socket;
}
ServerSocket::~ServerSocket()
{
	close();
}
