/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaObjectMembersIter.h - orca object members iterator

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/


#ifndef _DEF_ORCA_OBJECT_MEMBERS_ITER
#define _DEF_ORCA_OBJECT_MEMBERS_ITER

#include "orcaMap.h"
#include "orcaObject.h"


class orcaObjectMembersIter : public orcaObject
{
public:
	orcaObjectMembersIter(orcaObject* src, int pos);
	//orcaObjectMembersIter(orcaObject* src, string& name);
	orcaObjectMembersIter(void* vp);
	virtual orcaObject* v_clone();
	virtual ~orcaObjectMembersIter();

	virtual orcaData operator()(orcaVM* vm, int n);

	orcaData ex_key(orcaVM* vm, int n);
	orcaData ex_value(orcaVM* vm, int n);
	orcaData ex_next(orcaVM* vm, int n);
	//orcaData ex_prev(orcaVM* vm, int n);
	//orcaData ex_eq(orcaVM* vm, int n);
	//orcaData ex_lt(orcaVM* vm, int n);
	//orcaData ex_erase(orcaVM* vm, int n);

private:
	orcaObject* m_op;
	cp_map<orcaData>::Type::iterator m_sit;
	cp_map<orcaData>::Type::iterator m_mit;
	bool in_static;
};

#endif

