/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaOrca.h - language specific

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_ORCA
#define _DEF_ORCA_ORCA

#include "porting.h"
#include "orcaObject.h"
#include "orcaGlobal.h"

class orcaOrca : public orcaObject 
{
public:
	orcaOrca()
	{
		set_name("orca");
		insert_static_native_function("load", (object_fp)&orcaOrca::ex_load);
		insert_static_native_function("unload", (object_fp)&orcaOrca::ex_unload);
		insert_static_native_function("trace", (object_fp)&orcaOrca::ex_trace);
	}

	orcaData ex_load(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();

		orcaObject* op = g_root;
		if (n == 2) {
			op = vm->get_param(1).Object();
		}

		string mod = vm->get_param(0).String();
		return vm->load(mod, op);
	}

	orcaData ex_unload(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();

		orcaObject* op = g_root;
		if (n == 2) {
			op = vm->get_param(1).Object();
		}

		string mod = vm->get_param(0).String();
		orcaData out;
		if (op->has_member(mod.c_str(), out) == false) {
			throw orcaException(vm, "orca.lang", "unload failsed");
		}

		if (is<TYPE_OBJ>(out)) {
			g_codes->remove_code(mod);
			g_codes->remove_define(mod);
		}

		return NIL;
	}

	orcaData ex_trace(orcaVM* vm, int n) 
	{
		return vm->m_last_trace_info;
	}
};


#endif

