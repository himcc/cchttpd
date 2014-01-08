#include"Response.h"

int Response::response()
{
	sprintf(file,"%s%s",pwd,req.path);
	if(strstr(file,"/../")!=0) return -1;
	File f(file);
	if(f.fok)
	{
		if(f.isfile)
		{
			if(f.xok)
			{
				return exe();
			}else if(f.rok)
			{
				return sendfile(f);
			}else	return notfound();
		}else	return notfound();
	}else	return notfound();
	return -1;
}
int Response::notfound()
{
	if(notf[0]!=0) return exe(notf);
	else return exe(order);
}
int Response::exe(char * p)
{
	if(notf[0]!=0)
	{
		strcpy(file,notf);
	}else if(p&&p[0]!=0)
	{
		strcpy(file,p);
	}
	return forkAndExec();
}
int Response::forkAndExec()
{
	int pid=fork();
	if(pid)
	{
		int s;
		int ret=waitpid(pid,&s,0);
		//printf("         ---------------------\nexe %s\npid=%d ret=%d s=%d\n",file,pid,ret,s);
		if(WIFSIGNALED(s))
		{
			//puts("signal");
			//printf("no. is %d\n",WTERMSIG(s));
		}
		if(WIFEXITED(s)) return 0;
		else return -1;
	}else
	{
		close(0);
		dup(client.getfd());
		close(1);
		dup(client.getfd());

		char * arg[]={0};
		execve(file,arg,req.index);
	}
}
char * Response::getfiletype()
{
	int len = strlen(file);
	int index = len;
	while( index>=0 
		&& file[index]!='.' 
		&& file[index]!='/' ) --index;
	if(index<0 || file[index]=='/') return file+len;
	return file+index+1;
}
int Response::sendfile(File & f)
{
	char tmp[2048];
	if(client.write("HTTP/1.1 200 OK\r\n")<=0) return -1;
	sprintf(tmp,"Content-Type: %s\r\n",mime.gettype( getfiletype()) );
	if(client.write(tmp)<=0) return -1;
	if(req.keepalive)
	{if(client.write("Connection: Keep-Alive\r\n")<=0) return -1;}
	else
	{if(client.write("Connection: close\r\n")<=0) return -1;}
	sprintf(tmp,"Content-Length: %lld\r\n",f.size);
	if(client.write(tmp)<=0) return -1;
	if(client.write("\r\n")<=0) return -1;
	
	int fd=open(file,O_RDONLY),len;
	while( (len=read(fd,tmp,2048))>0 )
	{
		if(client.write(len,tmp)<=0) {close(fd);return -1;}
	}
	close(fd);
	return 0;
}
