
CC=g++
CPPFLAGS+= -std=c++11
CPPFLAGS+= -lpthread
LDLIBS=$(CPPFLAGS)

all:app
	@echo $(CPPFLAGS)

app:app.o ServerSocket.o Socket.o worker.o Server.o Request.o Response.o File.o Mime.o Init.o Notf.o

app.o:app.cpp

ServerSocket.o:ServerSocket.h

Socket.o:Socket.h

worker.o:worker.h

Server.o:Server.h

Request.o:Request.h

Response.o:Response.h

File.o:File.h

Mime.o:Mime.h

Init.o:Init.h

Notf.o:Notf.h

clean:
	-rm -f *.o app
