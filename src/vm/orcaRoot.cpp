/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaRoot.cpp - orcaRoot orcaObject of all modules

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/


#include <iostream>

#include "orcaRoot.h"
#include "orcaIO.h"
#include "orcaOS.h"
#include "orcaFile.h"
#include "orcaDL.h"
#include "orcaThread.h"
#include "orcaSocket.h"
#include "orcaIPC.h"
#include "orcaSelect.h"
#include "orcaDatetime.h"
#include "orcaDate.h"
#include "orcaTime.h"
#include "orcaPack.h"
#include "orcaStopWatch.h"
#include "orcaBase64.h"
#include "orcaType.h"
#include "orcaOrca.h"
#include "orcaRandom.h"
#include "orcaUtil.h"
#include "orcaMath.h"
#include "orcaOperator.h"
#include "orcaSort.h"
#include "orcaCPP.h"
#include "orcaSystem.h"
#include "orcaQueue.h"
#include "orcaSqlite3.h"
#include "orcaStrings.h"


#define USE_GTK

#if defined(LINUX)
#if defined(USE_GTK)
	#include "orcaGtk.h"
#endif
#endif

using namespace std;


orcaRoot s_root;
orcaRoot* g_root = &s_root;


orcaRoot::orcaRoot() 
{
	set_name("root");
	rc_inc(); // for permanant life

	insert_static("io", new orcaIO());
	insert_static("file", new orcaFile());
	insert_static("os", new orcaOS());
	insert_static("dl", new orcaDL());
	insert_static("thread", new orcaThread());
	insert_static("socket", new orcaSocket());
	insert_static("fdselect", new orcaSelect());
	insert_static("ipc", new orcaIPC());
	insert_static("time", new orcaTime());
	insert_static("date", new orcaDate());
	insert_static("datetime", new orcaDatetime());
	insert_static("pack", g_pack = new orcaPack());
	insert_static("stopwatch", new orcaStopWatch());
	insert_static("base64", new orcaBase64());
	insert_static("type", new orcaTypes());
	insert_static("orca", new orcaOrca());
	insert_static("random", new orcaRandom());
	insert_static("cutil", new orcaUtil());
	insert_static("math", new orcaMath());
	insert_static("operator", new orcaOperator());
	insert_static("sort", new orcaSort());
	insert_static("cpp", new orcaCPP());
	insert_static("system", new orcaSystem());
	insert_static("queue", new orcaQueue());
	insert_static("sqlite3", new orcaSqlite3());
	insert_static("strings", new orcaStrings());
	insert_native_function("string", (object_fp)&orcaRoot::ex_string);
	insert_native_function("repr", (object_fp)&orcaRoot::ex_repr);
	insert_native_function("range", (object_fp)&orcaRoot::ex_range);

#if defined(LINUX)
#if defined(USE_GTK)
	if (gtk_init_check(NULL, NULL) == false) {
		printf("[WARNING] Can't open gtk display.\n");
	} else {
		insert_static("gtk", new orcaGtk());
	}
#endif

#endif
}

orcaRoot::~orcaRoot() { }

orcaData orcaRoot::ex_string(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param();
	orcaData d = vm->get_param(0);

	if (is<TYPE_OBJ>(d)) {
		orcaData out;
		if (d.o()->has_member("string", out)) {
			vm->push_stack(out);
			vm->call(0);
			return vm->m_stack->pop().String();
		}
	}

	return d.string_(vm);
}

orcaData orcaRoot::ex_repr(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param();
	orcaData d = vm->get_param(0);

	if (is<TYPE_OBJ>(d)) {
		orcaData out;
		if (d.o()->has_member("repr", out)) {
			vm->push_stack(out);
			vm->call(0);
			return vm->m_stack->pop().String();
		}
	}

	return d.repr(vm);
}

class orcaRange : public orcaObject
{
public:
	DEFAULT_NATIVE_DEFINE(orcaRange);

	orcaRange()
	{
		set_name("range");
		from = 0;
		to = 0;
		curr = 0;
		interval = 1;

		insert_native_function("next", (object_fp)&orcaRange::ex_next);
	}

	orcaData ex_next(orcaVM* vm, int n)
	{
		curr += interval;

		if (to >= from) {
			if (curr >= to) {
				throw orcaException(vm, "orca.iter", "out of range");
			}
		}
		else { // descending
			if (curr <= to) {
				throw orcaException(vm, "orca.iter", "out of range");
			}
		}

		return this;
	}

	orcaData operator()(orcaVM* vm, int n)
	{
		if (n > 0) {
			throw orcaException(vm, "orca.param", "unmodifiable iterator");
		}

		return curr;
	}

public:
	int from;
	int to;
	int interval;
	int curr;
};

orcaData orcaRoot::ex_range(orcaVM* vm, int n)
{
	if (n < 2) vm->need_param();
	orcaRange* rp = new orcaRange();
	rp->from = vm->get_param(0).Integer();
	rp->to = vm->get_param(1).Integer();
	rp->curr = rp->from;

	if (n >= 3) {
		rp->interval = vm->get_param(2).Integer();
	}

	if (rp->to >= rp->from) {
		if (rp->interval <= 0) {
			throw orcaException(vm, "orca.range", "invalid range");
		}
	}
	else { // descending
		if (rp->interval >= 0) {
			throw orcaException(vm, "orca.range", "invalid range");
		}
	}
	
	return rp;
}



