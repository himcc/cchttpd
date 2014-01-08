#ifndef _SERVER_H

#define _SERVER_H

#include<stdio.h>
#include"ServerSocket.h"
#include"Socket.h"
#include"worker.h"
#include<thread>
class Server
{
private:
	ServerSocket server;
public:
	Server(int port):server(port){};
	void start();
};

#endif
