/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaInteger.h - integer type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_INTEGER
#define _DEF_ORCA_INTEGER

#include "orcaObject.h"

class LIBORCA_API orcaInteger : public orcaObject
{
public:
	orcaInteger();
	orcaData string_(orcaVM* vm, int i);
	orcaData float_(orcaVM* vm, int i);
	orcaData integer(orcaVM* vm, int i);
};

class LIBORCA_API orcaBigInteger : public orcaObject
{
public:
	orcaBigInteger();
	orcaData string_(orcaVM* vm, mpz_t& bn);
	orcaData float_(orcaVM* vm, mpz_t& bn);
	orcaData integer(orcaVM* vm, mpz_t& bn);
};


extern orcaInteger g_integer;

extern orcaBigInteger g_big_integer;

#endif
