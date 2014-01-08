#include"Request.h"
#include<string.h>
#include<stdio.h>

int Request::getQLine()
{
	int pathftom;
	char data[1024];
	int data_len;
	int ret = client.readLine(data,1023,data_len);
	if(ret<=0) return -1;
	if(data_len<=0) return -1;
	data[data_len]=0;
	if(strncmp("GET ",data,4)!=0
		&&strncmp("POST ",data,5)!=0
		&&strncmp("HEAD ",data,5)!=0) return -1;

	sscanf(data,"%s%s",method,path);
	int i=0;
	while(path[i]!='?'&&path[i]!='#'&&path[i]!=0) ++i;
	if(path[i]!=0)
	{
		sscanf(path+i,"%s",query);
		path[i]=0;
	}
	sprintf(mm,"method=%s",method);
	sprintf(pp,"path=%s",path);
	sprintf(pwdpwd,"pwdpwd=%s",pwd);//传递工作路径
	index[len_index++]=mm;
	index[len_index++]=pp;
	index[len_index++]=pwdpwd;
	return 0;
}
int Request::getHeadField()
{
	int len;
	int sheng=4095;
	int ret;
	while(sheng)
	{
		ret=client.readLine(Data+len_data,sheng,len);
		if(ret<=0) return -1;
		if(len==2) return 0;
		index[len_index++]=Data+len_data;
		
		char * tt=Data+len_data;
		while((*tt)!=':') ++tt;
		(*tt)='=';

		Data[len_data+len]=0;
		++len;
		len_data+=len;
		sheng-=len;
	}
	return -1;
}
int Request::getHead()
{
	memset(index,0,sizeof(index));
	len_data=len_index=method[0]=path[0]=query[0]=Data[0]=0;
	contentlength=body[0]=len_body=0;
	int ret=getQLine();if(ret) return -1;
	ret=getHeadField();if(ret) return -1;
	keepalive=getKeepAlive();
	if(char * p = getField("Content-Length"))
		sscanf(p,"%d",&contentlength);
	ret=parsequery();if(ret) return -1;
	ret=parsecookie();if(ret) return -1;

	if(contentlength)
	{
		ret=getBody();
		if(ret<=0) return -1;
		ret=parsebody();if(ret) return -1;
	}
	////
	//if(char * pa = getField("a"))
	//	printf("a=%s\n",pa);
	//printf("Content-Length: %s cc: %d\n",getField("Content-Length"),contentlength);
	////
	//index[len_index]=0;
	return 0;
}
int Request::parsequery()
{
	if(query[0]==0||query[0]=='#') return 0;
	char * p=query;
	if((*p)=='?') ++p;
	if((*p)==' '||(*p)==0) return 0;
	while(1)
	{
		index[len_index++]=p;
		while((*p)&&(*p)!='&') ++p;
		if((*p)=='&') (*p)=0,++p;
		else return 0;
	}
}
int Request::parsecookie()
{
	char * p=getField("Cookie");
	if(!p) return 0;
	while(1)
	{
		while( (*p) == ' ' ) ++p;
		if(!(*p)) return 0;
		index[len_index++]=p;
		while( (*p) && (*p)!=';' ) ++p;
		if(!(*p)) return 0;
		else (*p)=0;
		++p;
	}
}
int Request::parsebody()
{
	if(strcmp("multipart/form-data",getField("Content-Type"))==0) return 0;
	body[contentlength]=0;
	index[len_index++]=body;
	char * p=body+1;
	while(*p)
	{
		if((*p)=='&')
		{
			(*p)=0;
			index[len_index++]=(p+1);
		}
		++p;
	}
	return 0;
}
int Request::getBody()
{
	if(strcmp("multipart/form-data",getField("Content-Type"))==0) return 0;
	return client.read(body,contentlength);
}
char * Request::getField(const char * name)
{
	int len=strlen(name);
	for(int i=0;i<len_index;++i)
	{
		if(strncmp(index[i],name,len)==0&&index[i][len]=='=')
		{
			++len;
			while(index[i][len]==' ') ++len;
			return &index[i][len];
		}
	}
	return 0;
}
int Request::getKeepAlive()
{
	char* ret=getField("Connection");
	if(!ret) return 0;
	if(strncmp("keep-alive",ret,10)==0) return 1;
	else return 0;
}
Socket & Request::getClient()
{
	return client;
}
