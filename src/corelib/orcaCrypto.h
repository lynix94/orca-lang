/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */


#ifndef _DEF_ORCA_CRYPTO
#define _DEF_ORCA_CRYPTO

#include <openssl/sha.h>

#include "orcaObject.h"
#include "orcaException.h"

class orcaSha1 : public orcaObject 
{
public:
	orcaSha1(void* vp)
	{
		flag_init = false;
	}

	orcaSha1()
	{
		set_name("sha1");

		insert_native_function("clear", (object_fp)&orcaSha1::ex_clear);
		insert_native_function("write", (object_fp)&orcaSha1::ex_write);
		insert_native_function("sum", (object_fp)&orcaSha1::ex_sum);

		flag_init = false;
	}

	virtual ~orcaSha1()
	{
	}

	orcaObject* v_clone()
	{
		orcaSha1* fp = new orcaSha1(NULL);
		return fp;
	}

	orcaData ex_clear(orcaVM* vm, int n);
	orcaData ex_write(orcaVM* vm, int n);
	orcaData ex_sum(orcaVM* vm, int n);

private:
	SHA_CTX ctx;
	bool flag_init;
};

class orcaCrypto : public orcaObject 
{
public:
	orcaCrypto(void* vp) { }

	orcaCrypto()
	{
		set_name("crypto");
		insert_member("sha1", new orcaSha1());
	}

	virtual ~orcaCrypto()
	{
	}

	orcaObject* v_clone()
	{
		orcaCrypto* fp = new orcaCrypto(NULL);
		return fp;
	}


private:
};


#endif

