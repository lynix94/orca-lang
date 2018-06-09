/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaObjectParentsIter.h - orca object parents iterator

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/


#ifndef _DEF_ORCA_OBJECT_PARENTS_ITER
#define _DEF_ORCA_OBJECT_PARENTS_ITER

#include "orcaObject.h"

class orcaObjectParentsIter : public orcaObject
{
public:
	orcaObjectParentsIter(orcaObject* src, int pos);
//	orcaObjectParentsIter(orcaObject* src, orcaData p);
	orcaObjectParentsIter(void* vp);
	virtual orcaObject* v_clone();
	virtual ~orcaObjectParentsIter();

	virtual orcaData operator()(orcaVM* vm, int n);

	orcaData ex_next(orcaVM* vm, int n);
	orcaData ex_erase(orcaVM* vm, int n);
/*
	orcaData ex_prev(orcaVM* vm, int n);
	orcaData ex_eq(orcaVM* vm, int n);
*/

private:
	orcaObject* m_op;
	list<orcaObject*>::iterator m_it;
};

#endif

