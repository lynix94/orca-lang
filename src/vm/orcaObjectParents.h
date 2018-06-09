/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaObjectParents.h - orca object parents

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/


#ifndef _DEF_ORCA_OBJECT_PARENTS
#define _DEF_ORCA_OBJECT_PARENTS


#include "orcaObject.h"
         
using namespace std;


class orcaObjectParents : public orcaObject
{
public:
	orcaObjectParents(orcaData src);
	orcaObjectParents(void* vp);

	virtual orcaObject* v_clone();
	virtual ~orcaObjectParents();

	orcaData ex_get_at(orcaVM* vm, int n);
	orcaData ex_set_at(orcaVM* vm, int n);
	orcaData ex_string(orcaVM* vm, int n);
	orcaData ex_push_back(orcaVM* vm, int n);
	orcaData ex_pop_back(orcaVM* vm, int n);
	orcaData ex_push_front(orcaVM* vm, int n);
	orcaData ex_pop_front(orcaVM* vm, int n);

	orcaData ex_iter(orcaVM* vm, int n);

private:
	orcaData m_src;
	orcaObject* m_internal;
};

#endif



