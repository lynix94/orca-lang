/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaSocket.cpp - basic & lowlevel socket operation

  Copyright (C) 2009~ Lee, Ki-Yeul

**********************************************************************/

#include "orcaSocket.h"
#include "orcaException.h"
#include "orcaList.h"
#include "kyString.h"

orcaSocketModule::orcaSocketModule()
{
	set_name("socket");

	insert_native_function("create", (object_fp)&orcaSocketModule::ex_create);
	insert_native_function("gethostbyname", (object_fp)&orcaSocketModule::ex_gethostbyname);

	insert_static("SOL_SOCKET", SOL_SOCKET);
	insert_static("IPPROTO_TCP", IPPROTO_TCP);
	insert_static("SO_BROADCAST", SO_BROADCAST);
	insert_static("SO_DEBUG", SO_DEBUG);
	insert_static("SO_DONTROUTE", SO_DONTROUTE);
	insert_static("SO_OOBINLINE", SO_OOBINLINE);
	insert_static("SO_KEEPALIVE", SO_KEEPALIVE);
	insert_static("SO_RCVBUF", SO_RCVBUF);
	insert_static("SO_REUSEADDR", SO_REUSEADDR);
	insert_static("SO_SNDBUF", SO_SNDBUF);
	insert_static("TCP_NODELAY", TCP_NODELAY);
}

orcaData orcaSocketModule::ex_create(orcaVM* vm, int n) {
	orcaSocket* so = new orcaSocket();
	so->set_handle(socket(PF_INET, SOCK_STREAM, 0));
	return so;
}

orcaData orcaSocketModule::ex_gethostbyname(orcaVM* vm, int n) {
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





orcaSocket::orcaSocket()
{
	set_name("socket");
	m_handle = 0;
	m_port = 0;

	insert_native_function("send", (object_fp)&orcaSocket::ex_send);
	insert_native_function("recv", (object_fp)&orcaSocket::ex_recv);
	insert_native_function("write", (object_fp)&orcaSocket::ex_send);
	insert_native_function("read", (object_fp)&orcaSocket::ex_recv);
	insert_native_function("->", (object_fp)&orcaSocket::ex_channel_out);
	insert_native_function("size", (object_fp)&orcaSocket::ex_size);
	insert_native_function("recv_all", (object_fp)&orcaSocket::ex_recv_all);
	insert_native_function("close", (object_fp)&orcaSocket::ex_close);
	insert_native_function("connect", (object_fp)&orcaSocket::ex_connect);
	insert_native_function("bind", (object_fp)&orcaSocket::ex_bind);
	insert_native_function("listen", (object_fp)&orcaSocket::ex_listen);
	insert_native_function("accept", (object_fp)&orcaSocket::ex_accept);
	insert_native_function("set", (object_fp)&orcaSocket::ex_set);
	insert_native_function("get", (object_fp)&orcaSocket::ex_get);
	insert_native_function("setsockopt", (object_fp)&orcaSocket::ex_setsockopt);
	insert_native_function("getsockopt", (object_fp)&orcaSocket::ex_getsockopt);
}


orcaData orcaSocket::ex_send(orcaVM* vm, int n) {
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


orcaData orcaSocket::ex_recv(orcaVM* vm, int n) {
	if (!m_handle) {
		throw orcaException(vm, "io.socket", "invalid handle");
	}

	double timeout = -1;
	int size = 65536;
	if (n >= 2) {
		timeout = vm->get_param(1).Double();
	}
	if (n >= 1) {
		size = vm->get_param(0).Integer();
		if (size <= 0) size = 65536;
	}

	if (timeout >= 0) {
		struct timeval tv;
		tv.tv_sec = int(timeout);
		tv.tv_usec = (long long)(timeout * 1000000) % 1000000;

		fd_set fd_rd;
		FD_ZERO(&fd_rd);
		FD_SET(m_handle, &fd_rd);
		int ret = select(m_handle+1, &fd_rd, NULL, NULL, &tv);
		if (ret < 0) {
			throw orcaException(vm, "io.select", "select failed");
		}
		else if (ret == 0) {
			return "";
		}
	}

	string s;
	s.resize(size);
	int ret = ::recv(m_handle, &s[0], size, 0);
	if (ret <= 0) {
		close();
		throw orcaException(vm, "io.socket.disconn", "disconnected");
	}
	s.resize(ret);
	return s;
}


orcaData orcaSocket::ex_channel_out(orcaVM* vm, int n) {
	if (n<1) vm->need_param();

	if (!m_handle) {
		throw orcaException(vm, "io.socket", "invalid handle");
	}

	int size = 65536;
	char* buff = new char[size+1];

	int ret = ::recv(m_handle, &buff[0], size, 0);
	if (ret <= 0) {
		close();
		delete[] buff;
		throw orcaException(vm, "io.socket.disconn", "disconnected");
	}

	buff[ret] = 0;
	string s;
	s.resize(ret);
	copy(&buff[0], &buff[ret], s.begin());
	delete[] buff;

	orcaTuple* tp = new orcaTuple();
	tp->push_back(s);

	return tp;
}


orcaData orcaSocket::ex_size(orcaVM* vm, int n) {
	if (!m_handle) {
		throw orcaException(vm, "io.socket", "invalid handle");
	}

	struct timeval tv;
	fd_set fd_rd;
	FD_ZERO(&fd_rd);
	FD_SET(m_handle, &fd_rd);
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	int ret = select(m_handle+1, &fd_rd, NULL, NULL, &tv);
	if (ret) {
		if (FD_ISSET(m_handle, &fd_rd)) {
			return 1;
		}
	}

	return 0;
}


orcaData orcaSocket::ex_recv_all(orcaVM* vm, int n) {
	if (!m_handle) {
		throw orcaException(vm, "io.socket", "invalid handle");
	}

	double tmout = -1;
	int size = 0;
	char* buff;
	if (n >= 2) {
		tmout = vm->get_param(1).Double();
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
			tv.tv_sec = int(tmout);
			tv.tv_usec = (long long)(tmout * 1000000) % 1000000;
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

orcaData orcaSocket::ex_close(orcaVM* vm, int n) {
	close();
	return NIL;
}

orcaData orcaSocket::ex_connect(orcaVM* vm, int n) {
	if (n < 1) {
		return NIL;
	}

	string host;
	if (n == 1) {
		string& addr = vm->get_param(0).String();
		vector<string> toks = kyString::split(addr, ":");
		if (toks.size() != 2) {
			throw orcaException(vm, "orca.param", "invalid parameter, host:port or host, port");
		}

		host = toks[0];
		m_port = boost::lexical_cast<int>(toks[1]);
	}
	else {
		host = vm->get_param(0).String();
		m_port = vm->get_param(1).Integer();
	}

	struct hostent *host_e = gethostbyname(host.c_str());
	if (host_e == NULL) {
		throw orcaException(vm, "io.net.dns", "Cannot resolve hostname");
	}

	SOCKADDR_IN servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(m_port);
	servAddr.sin_addr.s_addr = *(long*)(host_e->h_addr);

	if(::connect(m_handle, (SOCKADDR*)&servAddr, sizeof(servAddr))==SOCKET_ERROR) {
		close();
		throw orcaException(vm, "io.socket.conn", "connection error");
	}

	return NIL;
}


orcaData orcaSocket::ex_bind(orcaVM* vm, int n) {
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


orcaData orcaSocket::ex_listen(orcaVM* vm, int n) {
	if( ::listen(m_handle, 5)==SOCKET_ERROR) {
		throw orcaException(vm, "io.socket.listen", "listen error");
	}

	return NIL;
}


orcaData orcaSocket::ex_accept(orcaVM* vm, int n) {
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


orcaData orcaSocket::ex_set(orcaVM* vm, int n) {
	if (n < 1) vm->need_param();

	set_handle(vm->get_param(0).Integer());
	return NIL;
}


orcaData orcaSocket::ex_get(orcaVM* vm, int n) {
	return (int)get_handle();
}


orcaData orcaSocket::ex_setsockopt(orcaVM* vm, int n) {
	if (n < 3) vm->need_param();

	int p1 = vm->get_param(0).Integer();
	int p2 = vm->get_param(1).Integer();
	int p3 = vm->get_param(2).Integer();

	return setsockopt(m_handle, p1, p2, &p3, sizeof(int));
}


orcaData orcaSocket::ex_getsockopt(orcaVM* vm, int n) {
	if (n < 1) vm->need_param();

	int p1 = vm->get_param(0).Integer();
	int p2 = vm->get_param(1).Integer();

	int out;
	int len = sizeof(int);
	getsockopt(m_handle, p1, p2, &out, (socklen_t*)&len);
	return out;
}


void orcaSocket::set_handle(SOCKET handle) {
	m_handle = handle;
}

SOCKET orcaSocket::get_handle() {
	return m_handle;
}

void orcaSocket::set_port(int port) {
	m_port = port;
}

void orcaSocket::close() {
	if (m_handle) {
		port_closesocket(m_handle);
		m_handle = 0;
	}
}
		

