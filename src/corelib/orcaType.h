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
#include "orcaList.h"
#include "orcaTuple.h"
#include "orcaMap.h"

class orcaLimits : public orcaObject 
{
public:
	orcaLimits() 
	{
		set_name("limits");
		orcaData d;

		d.i_set(CHAR_MAX);
		insert_static("int8_max", d);
		d.i_set(CHAR_MIN);
		insert_static("int8_min", d);
		d.i_set(UCHAR_MAX);
		insert_static("uint8_max", d);

		d.i_set(SHRT_MAX);
		insert_static("int16_max", d);
		d.i_set(SHRT_MIN);
		insert_static("int16_min", d);
		d.i_set(USHRT_MAX);
		insert_static("uint16_max", d);

		d.i_set(INT_MAX);
		insert_static("int32_max", d);
		d.i_set(INT_MIN);
		insert_static("int32_min", d);
		d.bn_set((long long)UINT_MAX);
		insert_static("uint32_max", d);

		d.bn_set(LLONG_MAX);
		insert_static("int64_max", d);
		d.bn_set(LLONG_MIN);
		insert_static("int64_min", d);
		d.bn_set(ULLONG_MAX);
		insert_static("uint64_max", d);

		d.r_set(FLT_MAX);
		insert_static("float32_max", d);
		d.r_set(FLT_MIN);
		insert_static("float32_max", d);

		d.r_set(DBL_MAX);
		insert_static("float64_max", d);
		d.r_set(DBL_MIN);
		insert_static("float64_max", d);
	}
};

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

		insert_static("limits", new orcaLimits());

		insert_static_native_function("is_iterable", (object_fp)&orcaTypes::ex_iterable);
		insert_static_native_function("is_indexable", (object_fp)&orcaTypes::ex_indexable);
	}

	~orcaTypes()
	{
		delete m_lp;
		delete m_tp;
		delete m_mp;
	}

	orcaData ex_iterable(orcaVM* vm, int n) 
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
	orcaLimits* m_limits;
};

#endif


