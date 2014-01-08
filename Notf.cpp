#include"Notf.h"

void donotf()
{
	char filename[100];
	char * ppp=getenv("path");
	sprintf(filename,"%s%s",getenv("pwdpwd"),ppp);
	
	File f(filename);
	if(f.fok)
	{
		if(!f.isfile)
		{
			showdir(filename,ppp);
		}else
		{
			retError();
		}
	}else
	{
		redirectToIndex();
	}
	return;
}
void showdir(char * dir,char * ppp)
{
	char * ret = new char[1024*1024*2];
	char * p=ret;
	//p+=sprintf(p,"%s<br/>",dir);
	int i=strlen(ppp);
	if(i!=1)
	{
		char ddir[100];
		strcpy(ddir,ppp);
		i-=2;
		while(ddir[i]!='/') --i;
		ddir[i+1]=0;
		p+=sprintf(p,"<a href=\"%s\"><-</a><br/>",ddir);
	}
	int num=0;
	DIR * dp;
	struct dirent *entry;	
	dp=opendir(dir);
	while((entry=readdir(dp))!=NULL)
	{
		char  dname [100];
		strcpy(dname,entry->d_name);
		if(strcmp(".",dname)==0 || strcmp("..",dname)==0) continue;
		++num;
		char name[100];
		sprintf(name,"%s%s",dir,dname);
		File f(name);
		if(f.isfile)
			p+=sprintf(p,"<a href=\"%s\">%s</a><br/>",dname,dname);
		else p+=sprintf(p,"<a href=\"%s/\">%s/</a><br/>",dname,dname);
	}
	p+=sprintf(p,"<br/>totle %d",num);
	closedir(dp);
	printHead(p-ret);
	printf("%s",ret);
}
void redirectToIndex()
{
	return retError();
}
void retError()
{
	printf("HTTP/1.1 200 OK\r\n");
	printf("Content-Type: text/html\r\n");
	printf("Connection: Keep-Alive\r\n");
	printf("Content-Length: 72\r\n");
	printf("\r\n");
	
	printf("<html><head><title>Error</title></head>not found the file or dir.</html>");
	return;
}
void printHead(int len)
{
	printf("HTTP/1.1 200 OK\r\n");
	printf("Content-Type: text/html\r\n");
	printf("Connection: Keep-Alive\r\n");
	printf("Content-Length: %d\r\n",len);
	printf("\r\n");
}
