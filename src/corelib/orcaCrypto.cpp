/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

#include "orcaCrypto.h"

#include <openssl/sha.h>

orcaData orcaSha1::ex_clear(orcaVM* vm, int n) 
{
	SHA1_Init(&ctx);
	flag_init = true;

	return NIL;
}



orcaData orcaSha1::ex_write(orcaVM* vm, int n) 
{
	if (n < 1) {
		vm->need_param(1);
	}
	
	if (flag_init == false) {
		SHA1_Init(&ctx);
		flag_init = true;
	}

	string str = vm->get_param(0).String();
	SHA1_Update(&ctx, str.c_str(), str.length());
	return NIL;
}



orcaData orcaSha1::ex_sum(orcaVM* vm, int n) 
{
	unsigned char digest[SHA_DIGEST_LENGTH];
	SHA1_Final(digest, &ctx);

	char mdString[SHA_DIGEST_LENGTH*2+1];

	for (int i=0; i<SHA_DIGEST_LENGTH; i++) {
		sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
	}

	return mdString;
}

