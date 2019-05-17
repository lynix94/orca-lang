/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */


#ifndef _DEF_ORCA_TLS
#define _DEF_ORCA_TLS

#include <openssl/bio.h>
#include <openssl/ssl.h>

#include "orcaObject.h"
#include "orcaException.h"

class orcaTlsModule : public orcaObject 
{
public:
	orcaTlsModule(void* vp) { }

	orcaTlsModule()
	{
		set_name("tls");

		insert_native_function("create", (object_fp)&orcaTlsModule::ex_create);
		init();
	}

	virtual ~orcaTlsModule()
	{
	}

	orcaObject* v_clone()
	{
		orcaTlsModule* fp = new orcaTlsModule(NULL);
		return fp;
	}

	void init();
	orcaData ex_create(orcaVM* vm, int n);

private:
};

class orcaTls : public orcaObject 
{
public:
	orcaTls(void* vp) { }

	orcaTls()
	{
		set_name("tls_socket");

		insert_native_function("connect", (object_fp)&orcaTls::ex_connect);
		insert_native_function("close", (object_fp)&orcaTls::ex_close);
		insert_native_function("read", (object_fp)&orcaTls::ex_read);
		insert_native_function("write", (object_fp)&orcaTls::ex_write);
	}

	virtual ~orcaTls()
	{
	}

	orcaObject* v_clone()
	{
		orcaTls* fp = new orcaTls(NULL);
		return fp;
	}

	void set_fd(int sock)
	{
		server_fd = sock;
	}

	orcaData ex_connect(orcaVM* vm, int n);
	orcaData ex_close(orcaVM* vm, int n);
	orcaData ex_read(orcaVM* vm, int n);
	orcaData ex_write(orcaVM* vm, int n);

private:
	const SSL_METHOD *method;
	SSL_CTX *ctx;
	SSL *ssl;
	X509 *cert;

	int server_fd;
};

#endif

