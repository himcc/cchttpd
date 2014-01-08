#include"File.h"

File::File(const char * pathname)
{
	fok=rok=wok=xok=isfile=size=time=0;
	if(access(pathname,F_OK)==0) fok=1;
	else return;
	if(access(pathname,R_OK)==0) rok=1;
	if(access(pathname,W_OK)==0) wok=1;
	if(access(pathname,X_OK)==0) xok=1;
	struct stat st;
	stat(pathname,&st);
	if(S_ISREG(st.st_mode)) isfile=1;
	size=st.st_size;
	time=st.st_mtime;
}
