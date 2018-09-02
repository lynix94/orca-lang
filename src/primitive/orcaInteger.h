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
	orcaData ex_add(orcaVM* vm, int i, int param_n);
	orcaData ex_sub(orcaVM* vm, int i, int param_n);
	orcaData ex_mul(orcaVM* vm, int i, int param_n);
	orcaData ex_div(orcaVM* vm, int i, int param_n);
	orcaData ex_mod(orcaVM* vm, int i, int param_n);
	orcaData ex_gt(orcaVM* vm, int i, int param_n);
	orcaData ex_ge(orcaVM* vm, int i, int param_n);
	orcaData ex_lt(orcaVM* vm, int i, int param_n);
	orcaData ex_le(orcaVM* vm, int i, int param_n);
	orcaData ex_eq(orcaVM* vm, int i, int param_n);
	orcaData ex_neq(orcaVM* vm, int i, int param_n);
	orcaData ex_and(orcaVM* vm, int i, int param_n);
	orcaData ex_or(orcaVM* vm, int i, int param_n);
	orcaData ex_string(orcaVM* vm, int i, int param_n);
	orcaData ex_float(orcaVM* vm, int i, int param_n);
	orcaData ex_integer(orcaVM* vm, int i, int param_n);
};

class LIBORCA_API orcaBigInteger : public orcaObject
{
public:
	orcaBigInteger();
	orcaData ex_add(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_sub(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_mul(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_div(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_mod(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_gt(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_ge(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_lt(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_le(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_eq(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_neq(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_and(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_or(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_string(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_float(orcaVM* vm, mpz_t& bn, int param_n);
	orcaData ex_integer(orcaVM* vm, mpz_t& bn, int param_n);
};


extern orcaInteger g_integer;

extern orcaBigInteger g_big_integer;

#endif
