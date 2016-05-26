/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaRandom.h - RNG

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_RANDOM
#define _DEF_ORCA_RANDOM

#include <stdlib.h>

#include "base64.h"
#include "porting.h"
#include "orcaStack.h"
#include "orcaObject.h"

class orcaRandom : public orcaObject 
{
public:
	orcaRandom()
	{
		set_name("random");
		insert_static_native_function("seed", (object_fp)&orcaRandom::ex_seed);
		insert_static_native_function("integer", (object_fp)&orcaRandom::ex_integer);
		insert_static_native_function("string", (object_fp)&orcaRandom::ex_string);
		insert_static_native_function("real", (object_fp)&orcaRandom::ex_real);
	}

	orcaData ex_seed(orcaVM* vm, int n) 
	{
		int seed;
		if (n == 1) {
			seed = vm->get_param(0).Integer();
		}
		else {
			seed = (int)time(NULL);
		}

		srand(seed);
		return NIL;
	}

	orcaData ex_integer(orcaVM* vm, int n) 
	{
		int mod=0;
		if (n == 1) {
			mod = vm->get_param(0).Integer();
		}

		int r = rand();
		if (mod > 0) r %= mod;
		return r;
	}

	orcaData ex_real(orcaVM* vm, int n) 
	{
		int r = rand();
		int cut = 100000000;
		r %= cut;
		double d = (double)r/(double)cut;
		return d;
	}

	orcaData ex_string(orcaVM* vm, int n) 
	{
		int mod=0;
		if (n == 1) {
			mod = vm->get_param(0).Integer();
		}

		if (mod < 1) mod = 1;

		string s;
		s.resize(mod*2 + 10);
		for (int i=0; i<mod; i++) {
			s[i] = rand()%256;
		}

		string ret = base64_encode((const unsigned char*)s.c_str(), mod);
		return ret.substr(0, mod);
	}
};

#endif

