#include"worker.h"
#include<stdio.h>
#include"Request.h"
#include<string.h>
#include"Response.h"
extern char pwd[];
void worker(int socket)
{

	Socket client(socket);
	Request request(client);
	Response res(request);
	while(request.keepalive && request.getHead()==0 )
	{
		
		int ret=res.response();
		if(ret)
		{
			printf("ERROR %s %s %s%s\n",request.keepalive?"keepalive":"close    ",pwd,request.path,request.query);
			return;
		}else
		{
			printf(" OK   %s %s %s%s\n",request.keepalive?"keepalive":"close    ",pwd,request.path,request.query);
		}
	}
}
