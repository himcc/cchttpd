#include<stdio.h>
#include"ServerSocket.h"
#include"Socket.h"
#include"worker.h"
#include<thread>
#include"Server.h"
#include<string.h>
#include<stdlib.h>
#include"Mime.h"
#include"File.h"
#include"Init.h"
#include"Notf.h"
char pwd[100];
char notf[100];
char order[100];
Mime mime;
int port;
int main(int argc,char ** argv)
{
	if(char *p=getenv("method")) {donotf();return 0;}
	init(argc,argv);

	printf("port:%d\n",port);
	printf("pwd:%s\n",pwd);
	printf("notf:%s\n",notf);
	printf("order:%s\n",order);

	Server server(port);
	server.start();
	return 0;
}
