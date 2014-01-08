#ifndef _INIT_H
#define _INIT_H
#include<stdio.h>
#include"ServerSocket.h"
#include"Socket.h"
#include"worker.h"
#include<thread>
#include"Server.h"
#include<string.h>
#include<stdlib.h>
#include"Mime.h"
#include"File.h"
#include"Notf.h"
extern char pwd[];
extern char notf[];
extern char order[];
extern int port;
void getport(char * s);
void getpwd(char * s);
void getnotf(char * s);
void init(int argc,char ** argv);
#endif
