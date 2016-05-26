/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaMapIter.h - map iterator

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_MAPITER
#define _DEF_ORCA_MAPITER

#include "orcaMap.h"

class orcaMap;

class LIBORCA_API orcaMapIter : public orcaObject
{
public:
	orcaMapIter(orcamap_iterator it, orcaMap* mp);
	orcaObject* v_clone();
	virtual ~orcaMapIter();

	virtual orcaData operator()(orcaVM* vm, int n);

	orcaData ex_first(orcaVM* vm, int n);
	orcaData ex_second(orcaVM* vm, int n);
	orcaData ex_next(orcaVM* vm, int n);
	orcaData ex_prev(orcaVM* vm, int n);
	orcaData ex_eq(orcaVM* vm, int n);
	orcaData ex_lt(orcaVM* vm, int n);
	orcaData ex_erase(orcaVM* vm, int n);

private:
	bool valid();

private:
	orcamap_iterator m_iter;
	orcaMap* m_mp;

	int m_timestamp;
};

#endif

