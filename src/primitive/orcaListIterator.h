/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaListIter.h - list type iterator

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_LIST_ITERATOR
#define _DEF_ORCA_LIST_ITERATOR

#include "orcaObject.h"
#include "orcaListIter.h"

class LIBORCA_API orcaListIterator : public orcaObject
{
public:
	orcaListIterator(orcaListIter it, orcaListIter begin, orcaListIter end);
	orcaListIterator(orcaList* lp, list<orcaData>::iterator it);
	orcaObject* v_clone();
	virtual ~orcaListIterator();

	virtual orcaData operator()(orcaVM* vm, int n);
	orcaData ex_next(orcaVM* vm, int n);
	orcaData ex_prev(orcaVM* vm, int n);
	orcaData ex_eq(orcaVM* vm, int n);

	// modify operation
	orcaData ex_erase(orcaVM* vm, int n);
	orcaData ex_insert(orcaVM* vm, int n);

	orcaListIter& get_iter()
	{
		return m_iter;
	}

private:
	orcaListIter m_iter;
	orcaListIter m_begin;
	orcaListIter m_end;
};
#endif



