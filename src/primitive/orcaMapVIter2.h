/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaMapIter.h - map iterator

  Copyright (C) 2009 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_VMAPITER2
#define _DEF_ORCA_VMAPITER2

#include "orcaMapIter.h"

class orcaMap;

class LIBORCA_API orcaMapVIter2 : public orcaMapIter
{
public:
	orcaMapVIter2(orcamap_iterator it, orcaMap* mp, bool flag_ready = true);
	orcaObject* v_clone();
	virtual ~orcaMapVIter2();

	orcaData ex_next(orcaVM* vm, int n);
	orcaData ex_prev(orcaVM* vm, int n);
	orcaData ex_eq(orcaVM* vm, int n);
	orcaData ex_lt(orcaVM* vm, int n);
};

#endif

