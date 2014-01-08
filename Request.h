#ifndef _REQUEST_H

#define _REQUEST_H

#include"Socket.h"
extern char pwd[];
class Request
{
private:
	Socket & client;
public:
	char method[10];
	char mm[20];
	char pp[100];
	char pwdpwd[100];
	char path[512];
	char query[512];
	char Data[4096];
	char body[4096];
	int len_body;
	int len_data;
	int len_index;
	char * index[512];
	int keepalive;
	int contentlength;
	Request(Socket & c):client(c),keepalive(1){};
	int getQLine();
	int getHeadField();
	int getHead();
	int getBody();
	int parsequery();
	int parsecookie();
	int parsebody();
	char * getField(const char * name);
	int getKeepAlive();
	Socket & getClient();
};

#endif
