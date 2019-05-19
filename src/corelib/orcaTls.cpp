/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

#include "orcaTls.h"

#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>

#include <boost/lexical_cast.hpp>

#include "kyString.h"

void orcaTlsModule::init()
{
	OpenSSL_add_all_algorithms();
	ERR_load_BIO_strings();
	ERR_load_crypto_strings();
	SSL_load_error_strings();

	int ret = SSL_library_init();
	if (ret < 0) {
		printf("[ERROR] Could not initialize the OpenSSL library\n");
	}
}

orcaData orcaTlsModule::ex_create(orcaVM* vm, int n) 
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	orcaTls* op = new orcaTls();
	op->set_fd(sockfd);
	return op;
}



orcaData orcaTls::ex_connect(orcaVM* vm, int n) 
{
	if (n < 1) {
		return NIL;
	}

	string host;
	int port;
	if (n == 1) {
		string& addr = vm->get_param(0).String();
		vector<string> toks = kyString::split(addr, ":");
		if (toks.size() != 2) {
			throw orcaException(vm, "orca.param", "invalid parameter, host:port or host, port");
		}

		host = toks[0];
		port = boost::lexical_cast<int>(toks[1]);
	}
	else {
		host = vm->get_param(0).String();
		port = vm->get_param(1).Integer();
	}


	method = SSLv23_client_method();

	ctx = SSL_CTX_new(method);
	if (ctx == NULL) {
		throw orcaException(vm, "io.tls.conn", "Unable to create a new SSL context structure.");
	}

	SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);
	ssl = SSL_new(ctx);

	struct hostent *host_e = gethostbyname(host.c_str());
	if (host_e == NULL) {
		throw orcaException(vm, "io.net.dns", "Cannot resolve hostname");
	}

	SOCKADDR_IN servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(port);
	servAddr.sin_addr.s_addr = *(long*)(host_e->h_addr);
	int ret = connect(server_fd, (SOCKADDR*) &servAddr, sizeof(servAddr));
	if (ret == -1) {
		throw orcaException(vm, "io.socket.conn", "connection error");
	}

	SSL_set_fd(ssl, server_fd);

	ret = SSL_connect(ssl);
	if (ret != 1) {
		throw orcaException(vm, "io.tls.conn", "Could not build a SSL session");
	}

	cert = SSL_get_peer_certificate(ssl);
	if (cert == NULL) {
		throw orcaException(vm, "io.tls.conn", "Could not get a certificate");
	}

	return NIL;
}

orcaData orcaTls::ex_close(orcaVM* vm, int n) 
{
	SSL_free(ssl);
	close(server_fd);
	X509_free(cert);
	SSL_CTX_free(ctx);

	return NIL;
}

orcaData orcaTls::ex_read(orcaVM* vm, int n) 
{
	if (ssl == NULL) {
		return NIL;
	}

	int size = 65535;
	double timeout = -1;
	if (n > 0) {
		size = vm->get_param(0).Integer();
		if (size <= 0) size = 65536;
	}
	if (n >= 2) {
		timeout = vm->get_param(1).Double();
	}

	if (timeout >= 0) {
		struct timeval tv;
		tv.tv_sec = int(timeout);
		tv.tv_usec = (long long)(timeout * 1000000) % 1000000;

		fd_set fd_rd;
		FD_ZERO(&fd_rd);
		FD_SET(server_fd, &fd_rd);
		int ret = select(server_fd+1, &fd_rd, NULL, NULL, &tv);
		if (ret < 0) {
			throw orcaException(vm, "io.select", "select failed");
		}
		else if (ret == 0) {
			return "";
		}
	}

	string s;
	s.resize(size);
	int ret = SSL_read(ssl, &s[0], size);
	s.resize(ret);
	return s;
}

orcaData orcaTls::ex_write(orcaVM* vm, int n) 
{
	string& in = vm->get_param(0).String();

	if (ssl == NULL) {
		return NIL;
	}

	return SSL_write(ssl, in.c_str(), in.size());
}

