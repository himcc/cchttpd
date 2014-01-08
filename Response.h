#ifndef _RESPONSE_H
#define _RESPONSE_H
#include"Request.h"
#include<string.h>
#include<stdio.h>
#include"File.h"
#include"Mime.h"
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
extern Mime mime;
extern char pwd[];
extern char order[];
extern char notf[];
class Response
{
private:
	Request & req;
	Socket & client;
	char file[100];
public:
	Response(Request & r):req(r),client(req.getClient()){};
	int response();
	int notfound();
	int exe(char * p=NULL);
	int sendfile(File & f);
	char * getfiletype();
	int forkAndExec();
};

#endif
