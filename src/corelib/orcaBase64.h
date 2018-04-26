/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaBase64.h -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_BASE64
#define _DEF_ORCA_BASE64

#include "base64.h"
#include "porting.h"
#include "orcaObject.h"

class orcaBase64 : public orcaObject 
{
public:
	orcaBase64()
	{
		set_name("base64");
		insert_static_native_function("encoding", (object_fp)&orcaBase64::ex_enc);
		insert_static_native_function("decoding", (object_fp)&orcaBase64::ex_dec);
	}

	orcaData ex_enc(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();

		string s = vm->get_param(0).String();
		return base64_encode((const unsigned char*)s.c_str(), s.length());
	}

	orcaData ex_dec(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();

		return base64_decode(vm->get_param(0).String());
	}
};


#endif

