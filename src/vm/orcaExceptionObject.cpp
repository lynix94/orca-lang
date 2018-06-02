/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaExceptionObject.cpp - orcaException Object 

  Copyright (C) 2018-2018 Lee, Ki-Yeul

**********************************************************************/


#include <iostream>

#include "orcaTuple.h"
#include "orcaExceptionObject.h"

orcaExceptionObject::orcaExceptionObject()
{
    set_name("exception");

    insert_native_function("who", (object_fp)&orcaExceptionObject::ex_who);
    insert_native_function("what", (object_fp)&orcaExceptionObject::ex_what);
    insert_native_function("trace", (object_fp)&orcaExceptionObject::ex_trace);
    insert_native_function("print_trace", (object_fp)&orcaExceptionObject::ex_print_trace);
    insert_native_function("->", (object_fp)&orcaExceptionObject::ex_channel_out);
    insert_native_function("rethrow", (object_fp)&orcaExceptionObject::ex_rethrow);
}

orcaExceptionObject::~orcaExceptionObject()
{
	e.rc_dec();
}

orcaObject* orcaExceptionObject::v_clone()
{
	orcaExceptionObject* op = new orcaExceptionObject(NULL);
	op->e = e;
	op->e.rc_inc();

	return op;
}

orcaData orcaExceptionObject::ex_who(orcaVM* vm, int n)
{
	return e.who();
}

orcaData orcaExceptionObject::ex_what(orcaVM* vm, int n)
{
	return e.params[0].string_(vm);
}


orcaData orcaExceptionObject::ex_trace(orcaVM* vm, int n)
{
	return e.m_stack_trace;
}

orcaData orcaExceptionObject::ex_print_trace(orcaVM* vm, int n)
{
	cout << e.m_stack_trace << endl;
	return NIL;
}

orcaData orcaExceptionObject::ex_channel_out(orcaVM* vm, int n)
{
    if (n<1) vm->need_param();

    int count = vm->get_param(0).Integer();
    if (count == 0) { // argv
        count = e.params.size();
    } 

    orcaTuple* tup = new orcaTuple();
    for (int i=0; i<count && i<e.params.size(); i++) { 
		orcaData d = e.params[i];
        tup->push_back(d);
    } 

    return tup;
}

orcaData orcaExceptionObject::ex_rethrow(orcaVM* vm, int n)
{
	throw e;
}


