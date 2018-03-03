/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaRoot.h - orcaRoot orcaObject of all modules

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_ROOT
#define _DEF_ORCA_ROOT

#include "orcaObject.h"

class orcaRoot : public orcaObject 
{
public:
	orcaRoot();
	~orcaRoot();

	orcaData ex_string(orcaVM* vm, int n);
	orcaData ex_repr(orcaVM* vm, int n);
	orcaData ex_range(orcaVM* vm, int n);
};


extern orcaRoot* g_root;

#endif

