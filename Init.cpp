#include"Init.h"
void getport(char * s)
{
	sscanf(s,"%d",&port);
	if(port<=0)
	{
		printf("port error\n");
		exit(0);
	}
}
void getpwd(char * s)
{
	if(s[0]!='/')
		sprintf(pwd,"%s/%s",getenv("PWD"),s);
	else sprintf(pwd,"%s",s);
	File f(pwd);
	if( f.fok && f.rok && f.xok && (!f.isfile)) return;
	strcpy(pwd,getenv("PWD"));
}
void getnotf(char * s)
{
	if(s[0]!='/')
		sprintf(notf,"%s/%s",getenv("PWD"),s);
	else sprintf(notf,"%s",s);
	File f(notf);
	if( f.fok && f.xok && f.isfile) return;
	notf[0]=0;
}
void init(int argc,char ** argv)
{
	port=pwd[0]=notf[0]=0;
	strcpy(pwd,getenv("PWD"));
	if(argv[0][0]!='/')
		sprintf(order,"%s/%s",pwd,argv[0]);
	else sprintf(order,"%s",argv[0]);

	if(argc==1)	{printf("port error\n");exit(0);}
	if(argc>=2)	getport(argv[1]);
	if(argc>=3)	getpwd(argv[2]);
	if(argc>=4)	getnotf(argv[3]);
}
