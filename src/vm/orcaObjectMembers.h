/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaObjectMembers.h - base class of all orca object

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/


#ifndef _DEF_ORCA_OBJECT_MEMBERS
#define _DEF_ORCA_OBJECT_MEMBERS

#include "orcaMap.h"

class orcaObjectMembers : public orcaObject
{
public:
	orcaObjectMembers(orcaData src);
	orcaObjectMembers(void* vp);
	virtual orcaObject* v_clone();
	virtual ~orcaObjectMembers();

	void set_static() { is_static = true; }

	orcaData ex_get_at(orcaVM* vm, int n);
	orcaData ex_set_at(orcaVM* vm, int n);
	orcaData ex_string(orcaVM* vm, int n);
	orcaData ex_has_key(orcaVM* vm, int n);
	orcaData ex_erase_key(orcaVM* vm, int n);

	orcaData ex_keys(orcaVM* vm, int n);
	orcaData ex_values(orcaVM* vm, int n);

	orcaData ex_iter(orcaVM* vm, int n);
/*
	orcaData ex_begin(orcaVM* vm, int n);
	orcaData ex_last(orcaVM* vm, int n);
	orcaData ex_end(orcaVM* vm, int n);
	orcaData ex_find(orcaVM* vm, int n);
*/

private:
	orcaData m_src;
	orcaObject* m_internal;
	bool is_static;
};

#endif


