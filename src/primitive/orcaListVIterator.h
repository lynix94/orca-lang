/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaListIter.h - list type iterator

  Copyright (C) 2009 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_LIST_VITERATOR
#define _DEF_ORCA_LIST_VITERATOR

#include "orcaListIterator.h"

class LIBORCA_API orcaListVIterator : public orcaListIterator
{
public:
	orcaListVIterator(orcaListIter it, orcaListIter begin, orcaListIter end, bool flag_ready=true);

	orcaObject* v_clone();
	virtual ~orcaListVIterator();

	orcaData ex_next(orcaVM* vm, int n);
	orcaData ex_prev(orcaVM* vm, int n);
	orcaData ex_eq(orcaVM* vm, int n);
};
#endif



