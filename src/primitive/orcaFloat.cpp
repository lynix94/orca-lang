/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaFloat.cpp - real number type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <boost/lexical_cast.hpp>

#include "orcaFloat.h"
#include "orcaVM.h"

using namespace boost;

orcaFloat g_float;

orcaFloat::orcaFloat() 
{
	// this is the only one copy
	make_original();

	orcaData d;
	d.set_type(TYPE_INTERNAL);

	d.internal(FI_FLOAT_ADD, "+"); 
	insert_static("+", d);

	d.internal(FI_FLOAT_SUB, "-"); 
	insert_static("-", d);

	d.internal(FI_FLOAT_MUL, "*"); 
	insert_static("*", d);

	d.internal(FI_FLOAT_DIV, "/"); 
	insert_static("/", d);

	d.internal(FI_FLOAT_MOD, "%"); 
	insert_static("%", d);

	d.internal(FI_FLOAT_EQ, "=="); 
	insert_static("==", d);

	d.internal(FI_FLOAT_NEQ, "!="); 
	insert_static("!=", d);

	d.internal(FI_FLOAT_GT, ">"); 
	insert_static(">", d);

	d.internal(FI_FLOAT_GE, ">="); 
	insert_static(">=", d);

	d.internal(FI_FLOAT_LT, "<"); 
	insert_static("<", d);

	d.internal(FI_FLOAT_LE, "<="); 
	insert_static("<=", d);

	d.internal(FI_FLOAT_AND, "&&"); 
	insert_static("&&", d);

	d.internal(FI_FLOAT_OR, "||");
	insert_static("||", d);

	d.internal(FI_FLOAT_TO_STR, "string"); 
	insert_static("string", d);

	d.internal(FI_FLOAT_TO_STR, "repr"); 
	insert_static("repr", d);

	d.internal(FI_FLOAT_TO_INT, "integer"); 
	insert_static("integer", d);

	d.internal(FI_FLOAT_TO_FLOAT, "float"); 
	insert_static("float", d);
}

orcaData orcaFloat::ex_add(orcaVM* vm, double f, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(f).operator_add(vm, rhs);
}

orcaData orcaFloat::ex_sub(orcaVM* vm, double f, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(f).operator_sub(vm, rhs);
}

orcaData orcaFloat::ex_mul(orcaVM* vm, double f, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(f).operator_mul(vm, rhs);
}

orcaData orcaFloat::ex_div(orcaVM* vm, double f, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(f).operator_div(vm, rhs);
}

orcaData orcaFloat::ex_mod(orcaVM* vm, double f, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(f).operator_mod(vm, rhs);
}


orcaData orcaFloat::ex_eq(orcaVM* vm, double f, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(f).operator_eq(vm, rhs);
}

orcaData orcaFloat::ex_neq(orcaVM* vm, double f, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(f).operator_neq(vm, rhs);
}

orcaData orcaFloat::ex_gt(orcaVM* vm, double f, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(f).operator_gt(vm, rhs);
}

orcaData orcaFloat::ex_ge(orcaVM* vm, double f, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(f).operator_ge(vm, rhs);
}

orcaData orcaFloat::ex_lt(orcaVM* vm, double f, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(f).operator_lt(vm, rhs);
}

orcaData orcaFloat::ex_le(orcaVM* vm, double f, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(f).operator_le(vm, rhs);
}

orcaData orcaFloat::ex_and(orcaVM* vm, double f, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(f).operator_and(vm, rhs);
}

orcaData orcaFloat::ex_or(orcaVM* vm, double f, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(f).operator_or(vm, rhs);
}

orcaData orcaFloat::ex_string(orcaVM* vm, double f, int param_n) 
{
	if (is<TYPE_STR>(vm->get_param(0))) {
		char buff[1024];

		string format = vm->get_param(0).s();
		snprintf(buff, 1024, format.c_str(), f);
		return buff;
	}
	
	return lexical_cast<string>(f);
}

orcaData orcaFloat::ex_integer(orcaVM* vm, double f, int param_n) 
{
	if (f > INT_MAX) {
		orcaData d;
		mpz_t b;
		mpz_init(b);
		mpz_set_d(b, f);
		d.bn_set(b);
		mpz_clear(b);

		return d;
	}

	return static_cast<int>(f);
}

orcaData orcaFloat::ex_float(orcaVM* vm, double f, int param_n) 
{
	return f;
}

