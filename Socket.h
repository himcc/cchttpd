#ifndef _SOCKET_H
#define _SOCKET_H

#include<unistd.h>
#include<errno.h>
class Socket
{
private:
	int client_socket;
public:
	Socket(int client_socket);
	void close();
	int readchar(char &ch);
	int writechar(char ch);
	int getfd();
	int write(int len,const char * p);
	int write(const char * p);
	int readLine(char *data,int len,int & data_len);
	int read(char * data,int len);
	int my_read(int fd,void * buffer,int length);
	int my_write(int fd,void * buffer,int length);
	~Socket();
};

#endif
