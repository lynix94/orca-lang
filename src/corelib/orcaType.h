/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaType.h - for functional programming

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_TYPE
#define _DEF_ORCA_TYPE

#include "porting.h"
#include "orcaStack.h"
#include "orcaObject.h"
#include "orcaMap.h"

class orcaTypes : public orcaObject 
{
public:
	orcaTypes() 
	{
		m_lp = new orcaList();
		m_tp = new orcaTuple();
		m_mp = new orcaMap();

		set_name("type");
		orcaData d;
		d.t = TYPE_TYPE;

		d.v.type.t = TYPE_NIL;
		insert_static("nil", d);

		d.v.type.t = TYPE_BOOL;
		insert_static("bool", d);

		d.v.type.t = TYPE_BOOL;
		insert_static("boolean", d);

		d.v.type.t = TYPE_INT;
		insert_static("int", d);

		d.v.type.t = TYPE_INT;
		insert_static("integer", d);

		d.v.type.t = TYPE_REAL;
		insert_static("float", d);

		d.v.type.t = TYPE_STR;
		insert_static("str", d);

		d.v.type.t = TYPE_STR;
		insert_static("string", d);

		d.v.type.t = TYPE_REGEX;
		insert_static("regex", d);

		d.v.type.t = TYPE_OBJ;
		d.v.type.vp = m_lp;
		insert_static("list", d);

		d.v.type.t = TYPE_OBJ;
		d.v.type.vp = m_tp;
		insert_static("tuple", d);

		d.v.type.t = TYPE_OBJ;
		d.v.type.vp = m_mp;
		insert_static("map", d);

		insert_static_native_function("is_iteratable", (object_fp)&orcaTypes::ex_iteratable);
		insert_static_native_function("is_indexable", (object_fp)&orcaTypes::ex_indexable);
	}

	~orcaTypes()
	{
		delete m_lp;
		delete m_tp;
		delete m_mp;
	}

	orcaData ex_iteratable(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();

		orcaData p = vm->get_param(0);
		if (!is<TYPE_OBJ>(p)) {
			return false;
		}

		if (isobj<orcaTuple>(p) || isobj<orcaList>(p) || isobj<orcaMap>(p)) {
			return true;
		}

		orcaObject* o = p.o();
		if (o->has_member("next")) {
			return true;
		}

		return false;
	}
	
	orcaData ex_indexable(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();

		orcaData p = vm->get_param(0);
		if (!is<TYPE_OBJ>(p)) {
			return false;
		}

		if (isobj<orcaTuple>(p) || isobj<orcaList>(p) || isobj<orcaMap>(p)) {
			return true;
		}

		orcaObject* o = p.o();
		if (o->has_member("[]")) {
			return true;
		}

		return false;
	}
	

	orcaList* m_lp;
	orcaTuple* m_tp;
	orcaMap* m_mp;
};

#endif


