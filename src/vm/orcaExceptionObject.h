/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaExceptionObject.h - orcaException Object 

  Copyright (C) 2018-2018 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_EXCEPTION_OBJECT
#define _DEF_ORCA_EXCEPTION_OBJECT

#include <list>

#include "orcaObject.h"
#include "orcaException.h"

using namespace std;

class orcaExceptionObject : public orcaObject 
{
public:
	orcaExceptionObject(void*) {}
	virtual ~orcaExceptionObject();
	orcaObject* v_clone();

	orcaExceptionObject();

	orcaData ex_who(orcaVM* vm, int n);
	orcaData ex_what(orcaVM* vm, int n);
	orcaData ex_trace(orcaVM* vm, int n);
	orcaData ex_print_trace(orcaVM* vm, int n);
	orcaData ex_channel_out(orcaVM* vm, int n);
	orcaData ex_rethrow(orcaVM* vm, int n);

	orcaException e;
};

#endif

