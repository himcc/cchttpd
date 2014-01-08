#include<unistd.h>
#include"Socket.h"
#include<string.h>
Socket::Socket(int client_socket)
{
	this->client_socket=client_socket;
}
void Socket::close()
{
	::close(client_socket);
}
int Socket::readchar(char &ch)
{
	return my_read(client_socket,&ch,1);
}
int Socket::writechar(char ch)
{
	return my_write(client_socket,&ch,1);
}
int Socket::getfd()
{
	return client_socket;
}
int Socket::write(int len,const char * p)
{
	return my_write(client_socket,(void*)p,len);
}
int Socket::write(const char * p)
{
	return my_write(client_socket,(void*)p,strlen(p));
}
int Socket::readLine(char *data,int len,int & data_len)
{
	data_len=0;
	int R=0,ret;
	while(data_len<len && (ret=my_read(client_socket,data+data_len,1))>0 )
	{
		++data_len;
		if(data[data_len-1]=='\r')
		{
			R=1;
		}else if(data[data_len-1]=='\n'&&R==1)
		{
			return ret;
		}else
		{
			R=0;
		}
	}
	return ret;
}
int Socket::read(char * data,int len)
{
	return my_read(client_socket,data,len);
}
Socket::~Socket()
{
	close();
}

int Socket::my_write(int fd,void * buffer,int length)
{
	int bytes_left;
	int written_bytes;
	char * ptr=(char *)buffer;
	bytes_left=length;
	while(bytes_left>0)
	{
		written_bytes=::write(fd,(void*)ptr,bytes_left);
		if(written_bytes<=0)
		{
			if(errno==EINTR)	written_bytes=0;
			else	return(-1);
		}
		bytes_left-=written_bytes;
		ptr+=written_bytes;
	}
	
	return(length-bytes_left);
}

int Socket::my_read(int fd,void * buffer,int length)
{
	int bytes_left;
	int bytes_read;
	char * ptr=(char *)buffer;
	bytes_left=length;
	while(bytes_left>0)
	{
		bytes_read=::read(fd,(void*)ptr,bytes_left);
		if(bytes_read<0)
		{
			if(errno==EINTR)	bytes_read=0;
			else	return(-1);
		}
		else if(bytes_read==0)	break;
		bytes_left-=bytes_read;
		ptr+=bytes_read;
	}
	return(length-bytes_left);
}
