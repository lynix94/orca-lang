/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaBoolean.h - boolean type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_BOOLEAN
#define _DEF_ORCA_BOOLEAN

#include "orcaObject.h"

class LIBORCA_API orcaBoolean : public orcaObject
{
public:
	orcaBoolean();
	orcaData ex_eq(orcaVM* vm, int i, int param_n);
	orcaData ex_neq(orcaVM* vm, int i, int param_n);
	orcaData ex_and(orcaVM* vm, int i, int param_n);
	orcaData ex_or(orcaVM* vm, int i, int param_n);
	orcaData ex_string(orcaVM* vm, int i, int param_n);
	orcaData ex_float(orcaVM* vm, int i, int param_n);
	orcaData ex_integer(orcaVM* vm, int i, int param_n);
};

extern orcaBoolean g_boolean;
extern orcaData BOOL_TRUE;
extern orcaData BOOL_FALSE;


#endif

