/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaMapIter.h - map iterator

  Copyright (C) 2009 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_MAPITER
#define _DEF_ORCA_MAPITER

#include "orcaMap.h"

class orcaMap;

class LIBORCA_API orcaMapIter : public orcaObject
{
public:
	orcaMapIter(orcamap_iterator it, orcaMap* mp, bool flag_ready = true, bool is_iter2 = false);
	orcaMapIter(void*) {};
	orcaObject* v_clone();
	virtual ~orcaMapIter();

	virtual orcaData operator()(orcaVM* vm, int n);

	orcaData ex_key(orcaVM* vm, int n);
	orcaData ex_value(orcaVM* vm, int n);
	orcaData ex_next(orcaVM* vm, int n);
	orcaData ex_prev(orcaVM* vm, int n);
	orcaData ex_eq(orcaVM* vm, int n);
	orcaData ex_lt(orcaVM* vm, int n);
	orcaData ex_erase(orcaVM* vm, int n);

protected:
	bool valid();

	orcamap_iterator m_iter;
	orcaMap* m_mp;

	int m_timestamp;
	bool flag_ready;
	bool is_iter2;
};

#endif

