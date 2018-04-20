/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaSocket.h - basic & lowlevel socket operation

  Copyright (C) 2009~ Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_SOCKET
#define _DEF_ORCA_SOCKET

#include "porting.h"

#ifndef WINDOWS
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#endif



#include "orcaObject.h"

class orcaSocketModule : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaSocketModule);

	orcaSocketModule();

	orcaData ex_create(orcaVM* vm, int n);
	orcaData ex_gethostbyname(orcaVM* vm, int n);
		
};


class orcaSocket : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaSocket);

	orcaSocket();

	orcaData ex_send(orcaVM* vm, int n);
	orcaData ex_recv(orcaVM* vm, int n);
	orcaData ex_channel_out(orcaVM* vm, int n);
	orcaData ex_size(orcaVM* vm, int n);
	orcaData ex_recv_all(orcaVM* vm, int n);
	orcaData ex_close(orcaVM* vm, int n);
	orcaData ex_connect(orcaVM* vm, int n);
	orcaData ex_bind(orcaVM* vm, int n);
	orcaData ex_listen(orcaVM* vm, int n);
	orcaData ex_accept(orcaVM* vm, int n);
	orcaData ex_set(orcaVM* vm, int n);
	orcaData ex_get(orcaVM* vm, int n);
	orcaData ex_setsockopt(orcaVM* vm, int n);
	orcaData ex_getsockopt(orcaVM* vm, int n);
	void set_handle(SOCKET handle);
	SOCKET get_handle();
	void set_port(int port);
	void close();
		
private:
	SOCKET m_handle;
	int m_port;
};


#endif

