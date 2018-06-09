/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaTupleVIter.h - tuple iterator

  Copyright (C) 2009 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_TUPLEVITER
#define _DEF_ORCA_TUPLEVITER

#include "orcaTupleIter.h"


class LIBORCA_API orcaTupleVIter : public orcaTupleIter
{
public:
	orcaTupleVIter(orcatuple_iterator begin, orcaTuple* tp, bool flag_ready = true);
	orcaObject* v_clone();
	virtual ~orcaTupleVIter();

	orcaData ex_next(orcaVM* vm, int n);
	orcaData ex_prev(orcaVM* vm, int n);
	orcaData ex_eq(orcaVM* vm, int n);
};

#endif

