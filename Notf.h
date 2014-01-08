#ifndef _NOTF_H
#define _NOTF_H
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
#include<dirent.h>
void retError();
void showdir(char *dir,char * ppp);
void redirectToIndex();
void donotf();
void printHead(int len);
#endif
