/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaBoolean.cpp - boolean type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaBoolean.h"
#include "orcaVM.h"

orcaBoolean g_boolean;
orcaData BOOL_TRUE(true);
orcaData BOOL_FALSE(false);

orcaBoolean::orcaBoolean() 
{		
	// this is the only one copy
	make_original();

	orcaData d;
	d.set_type(TYPE_INTERNAL);

	d.internal(FI_INT_EQ, "=="); 
	insert_static("==", d);

	d.internal(FI_INT_NEQ, "!="); 
	insert_static("!=", d);

	d.internal(FI_INT_AND, "&&"); 
	insert_static("&&", d);

	d.internal(FI_INT_OR, "||");
	insert_static("||", d);

	d.internal(FI_BOOL_TO_STR, "string");
	insert_static("string", d);

	d.internal(FI_BOOL_TO_STR, "repr");
	insert_static("repr", d);

	d.internal(FI_BOOL_TO_INT, "integer");
	insert_static("integer", d);

	d.internal(FI_BOOL_TO_FLOAT, "float");
	insert_static("float", d);
}

orcaData orcaBoolean::ex_eq(orcaVM* vm, int b, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(b==1).operator_eq(vm, rhs);
}

orcaData orcaBoolean::ex_neq(orcaVM* vm, int b, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(b==1).operator_neq(vm, rhs);
}

orcaData orcaBoolean::ex_and(orcaVM* vm, int b, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(b==1).operator_and(vm, rhs);
}

orcaData orcaBoolean::ex_or(orcaVM* vm, int b, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(b==1).operator_or(vm, rhs);
}

orcaData orcaBoolean::ex_string(orcaVM* vm, int b, int param_n)
{
	orcaData d;
	b ? d.s_set("true") : d.s_set("false");

	return d;
}

orcaData orcaBoolean::ex_float(orcaVM* vm, int b, int param_n)
{
	if (b) return 1.0;
	return 0.0;
}

orcaData orcaBoolean::ex_integer(orcaVM* vm, int b, int param_n)
{
	if (b) return 1;
	return 0;
}

