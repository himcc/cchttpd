#ifndef _FILE_H
#define _FILE_H
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

class File
{
public:
	int fok,rok,wok,xok,isfile;
	long long size,time;
	File(const char * pathname);
};
#endif
