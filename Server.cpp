#include"Server.h"

void Server::start()
{
	int client_socket;
	server.bind();
	server.listen();
	while(1)
	{
		client_socket = server.accept();
		
		std::thread aworker(worker,client_socket);
		aworker.detach();
	}
}
