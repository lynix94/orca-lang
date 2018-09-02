/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaFloat.h - real number type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_FLOAT
#define _DEF_ORCA_FLOAT

#include "orcaObject.h"

class LIBORCA_API orcaFloat : public orcaObject
{
public:
	orcaFloat();
	orcaData ex_add(orcaVM* vm, double f, int param_n);
	orcaData ex_sub(orcaVM* vm, double f, int param_n);
	orcaData ex_mul(orcaVM* vm, double f, int param_n);
	orcaData ex_div(orcaVM* vm, double f, int param_n);
	orcaData ex_mod(orcaVM* vm, double f, int param_n);
	orcaData ex_gt(orcaVM* vm, double f, int param_n);
	orcaData ex_ge(orcaVM* vm, double f, int param_n);
	orcaData ex_lt(orcaVM* vm, double f, int param_n);
	orcaData ex_le(orcaVM* vm, double f, int param_n);
	orcaData ex_eq(orcaVM* vm, double f, int param_n);
	orcaData ex_neq(orcaVM* vm, double f, int param_n);
	orcaData ex_and(orcaVM* vm, double f, int param_n);
	orcaData ex_or(orcaVM* vm, double f, int param_n);
	orcaData ex_string(orcaVM* vm, double f, int param_n);
	orcaData ex_float(orcaVM* vm, double f, int param_n);
	orcaData ex_integer(orcaVM* vm, double f, int param_n);
};


extern orcaFloat g_float;

#endif

