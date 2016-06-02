/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaSocket.h - basic & lowlevel socket operation

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_SOCKET
#define _DEF_ORCA_SOCKET

#include "porting.h"

#ifndef WINDOWS
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif



#include "orcaObject.h"
#include "orcaException.h"


class orcaSocket : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaSocket);

	orcaSocket()
	{
		set_name("socket");
		m_handle = 0;
		m_port = 0;

		insert_native_function("create", (object_fp)&orcaSocket::ex_create);
		insert_native_function("send", (object_fp)&orcaSocket::ex_send);
		insert_native_function("recv", (object_fp)&orcaSocket::ex_recv);
		insert_native_function("recv_all", (object_fp)&orcaSocket::ex_recv_all);
		insert_native_function("close", (object_fp)&orcaSocket::ex_close);
		insert_native_function("connect", (object_fp)&orcaSocket::ex_connect);
		insert_native_function("bind", (object_fp)&orcaSocket::ex_bind);
		insert_native_function("listen", (object_fp)&orcaSocket::ex_listen);
		insert_native_function("accept", (object_fp)&orcaSocket::ex_accept);
		insert_native_function("set", (object_fp)&orcaSocket::ex_set);
		insert_native_function("get", (object_fp)&orcaSocket::ex_get);
		insert_native_function("gethostbyname", (object_fp)&orcaSocket::ex_gethostbyname);
	}

	orcaData ex_create(orcaVM* vm, int n) {/*{{{*/
		orcaSocket* so = new orcaSocket();
		so->set_handle(socket(PF_INET, SOCK_STREAM, 0));
		return so;
	}
/*}}}*/
	
	orcaData ex_send(orcaVM* vm, int n) {/*{{{*/
		if (n < 1) vm->need_param();

		string& msg = vm->get_param(0).String();

		if (!m_handle) {
			throw orcaException(vm, "io.socket.handle", "invalid handle");
		}

		int ret = ::send(m_handle, msg.c_str(), msg.length(), 0);
		if (ret <= 0) {
			close();
			throw orcaException(vm, "io.socket.disconn", "disconnected");
		}

		return ret;		
	}
/*}}}*/

	orcaData ex_recv(orcaVM* vm, int n) {/*{{{*/
		if (!m_handle) {
			throw orcaException(vm, "io.socket", "invalid handle");
		}

		int tmout = -1;
		int size = 65536;
		char* buff;
		if (n >= 2) {
			tmout = vm->get_param(1).Integer();
		}
		if (n >= 1) {
			size = vm->get_param(0).Integer();
			if (size <= 0) size = 65536;
		}

		buff = new char[size+1];

		int ret;
		if (tmout < 0) {
			ret = ::recv(m_handle, &buff[0], size, 0);
			if (ret <= 0) {
				close();
				delete[] buff;
				throw orcaException(vm, "io.socket.disconn", "disconnected");
			}
		}
		else {
			struct timeval tv;
			fd_set fd_rd;
			FD_ZERO(&fd_rd);
			FD_SET(m_handle, &fd_rd);
			tv.tv_sec = tmout / 1000;
			tv.tv_usec = (tmout % 1000) * 1000;
			ret = select(m_handle+1, &fd_rd, NULL, NULL, &tv);
			if (ret) {
				if (FD_ISSET(m_handle, &fd_rd)) {
					ret = ::recv(m_handle, &buff[0], size, 0);
					if (ret <= 0) {
						close();
						delete buff;
						throw orcaException(vm, "io.socket.disconn", "disconnected");
					}
				}
			}
		}

		buff[ret] = 0;
		string s;
		s.resize(ret);
		copy(&buff[0], &buff[ret], s.begin());
		delete[] buff;

		return s;
	}
/*}}}*/

	orcaData ex_recv_all(orcaVM* vm, int n) {/*{{{*/
		if (!m_handle) {
			throw orcaException(vm, "io.socket", "invalid handle");
		}

		int tmout = -1;
		int size = 0;
		char* buff;
		if (n >= 2) {
			tmout = vm->get_param(1).Integer();
		}
		if (n >= 1) {
			size = vm->get_param(0).Integer();
			if (size <= 0) size = 0;
		}

		if (size == 0) return (char*)"";

		
		int idx = 0;
		buff = new char[size+1];
		int ret;

		do {	
			if (tmout < 0) {
				ret = ::recv(m_handle, &buff[idx], size-idx, 0);
				if (ret <= 0) {
					close();
					delete buff;
					throw orcaException(vm, "io.socket.disconn", "disconnected");
				}
			}
			else {
				struct timeval tv;
				fd_set fd_rd;
				FD_ZERO(&fd_rd);
				FD_SET(m_handle, &fd_rd);
				tv.tv_sec = tmout / 1000;
				tv.tv_usec = (tmout % 1000) * 1000;
				ret = select(m_handle+1, &fd_rd, NULL, NULL, &tv);
				if (ret) {
					if (FD_ISSET(m_handle, &fd_rd)) {
						ret = ::recv(m_handle, &buff[idx], size-idx, 0);
						if (ret <= 0) {
							close();
							delete buff;
							throw orcaException(vm, "io.socket.disconn", "disconnected");
						}
					}
				}
				else {
					idx = 0;
					break;
				}
			}

			idx += ret;
		} while(idx < size);

		buff[idx] = 0;
		string s = buff;
		delete[] buff;

		return s;
	}
/*}}}*/

	orcaData ex_close(orcaVM* vm, int n) {/*{{{*/
		close();
		return NIL;
	}
/*}}}*/

	orcaData ex_connect(orcaVM* vm, int n) {/*{{{*/
		if (n < 2) vm->need_param();

		string& addr = vm->get_param(0).String();
		m_port = vm->get_param(1).Integer();

		SOCKADDR_IN servAddr;
		memset(&servAddr, 0, sizeof(servAddr));
		servAddr.sin_family=AF_INET;
		servAddr.sin_addr.s_addr=inet_addr(addr.c_str());
		servAddr.sin_port=htons(m_port);

		if(::connect(m_handle, (SOCKADDR*)&servAddr, sizeof(servAddr))==SOCKET_ERROR) {
			close();
			throw orcaException(vm, "io.socket.conn", "connection error");
		}
	
		return NIL;
	}
/*}}}*/

	orcaData ex_bind(orcaVM* vm, int n) {/*{{{*/
		if (n < 1) vm->need_param();

		m_port = vm->get_param(0).Integer();

		SOCKADDR_IN servAddr;
		memset(&servAddr, 0, sizeof(servAddr));
		servAddr.sin_family=AF_INET;
		servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
		servAddr.sin_port=htons(m_port);

		if( ::bind(m_handle, (SOCKADDR*) &servAddr, sizeof(servAddr))==SOCKET_ERROR ) {
			throw orcaException(vm, "io.socket.bind", "bind error");
		}

		return NIL;
	}
/*}}}*/

	orcaData ex_listen(orcaVM* vm, int n) {/*{{{*/
		if( ::listen(m_handle, 5)==SOCKET_ERROR) {
			throw orcaException(vm, "io.socket.listen", "listen error");
		}

		return NIL;
	}
/*}}}*/

	orcaData ex_accept(orcaVM* vm, int n) {/*{{{*/
		SOCKADDR_IN clntAddr;
		socklen_t clntLen=sizeof(clntAddr);	
		SOCKET sock = (SOCKET)::accept(m_handle, (SOCKADDR*)&clntAddr, &clntLen);
		if(sock==INVALID_SOCKET) {
			throw orcaException(vm, "io.socket.accept", "accept error");
		}

		orcaSocket* so = new orcaSocket();
		so->set_handle(sock);

		return so;
	}
	/*}}}*/

	orcaData ex_set(orcaVM* vm, int n) {/*{{{*/
		if (n < 1) vm->need_param();

		set_handle(vm->get_param(0).Integer());
		return NIL;
	}
/*}}}*/

	orcaData ex_get(orcaVM* vm, int n) {/*{{{*/
		return (int)get_handle();
	}
/*}}}*/

	orcaData ex_gethostbyname(orcaVM* vm, int n) {/*{{{*/
		if (n < 1) vm->need_param();

		struct hostent  *myent;
		struct in_addr  myen;
		long int *add;

		myent = gethostbyname(vm->get_param(0).String().c_str());
		if (myent == NULL) {
			throw orcaException(vm, "io.socket", "gethostbyname failed");
		}

		orcaList* lp = new orcaList();
		while(*myent->h_addr_list != NULL) {
			add = (long int *)*myent->h_addr_list;
			myen.s_addr = *add;
			lp->push_back(inet_ntoa(myen));
			myent->h_addr_list++;
		}

		return lp;
	}
/*}}}*/

	void set_handle(SOCKET handle) {
		m_handle = handle;
	}

	SOCKET get_handle() {
		return m_handle;
	}

	void set_port(int port) {
		m_port = port;
	}

	void close() {
		if (m_handle) {
			port_closesocket(m_handle);
			m_handle = 0;
		}
	}
		
private:
	SOCKET m_handle;
	int m_port;
};


#endif
