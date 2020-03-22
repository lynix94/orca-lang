/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaInteger.cpp - integer type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "porting.h"
#include "orcaInteger.h"
#include "orcaVM.h"

#include <boost/lexical_cast.hpp>
using namespace boost;

extern string get_bn_string(mpz_t bn);

orcaInteger g_integer;
orcaBigInteger g_big_integer;

orcaInteger::orcaInteger() 
{
	// this is the only one copy
	make_original();

	orcaData d;
	d.set_type(TYPE_INTERNAL);

	d.internal(FI_INT_ADD, "+"); 
	insert_static("+", d);

	d.internal(FI_INT_SUB, "-"); 
	insert_static("-", d);

	d.internal(FI_INT_MUL, "*"); 
	insert_static("*", d);

	d.internal(FI_INT_DIV, "/"); 
	insert_static("/", d);

	d.internal(FI_INT_MOD, "%"); 
	insert_static("%", d);

	d.internal(FI_INT_EQ, "=="); 
	insert_static("==", d);

	d.internal(FI_INT_NEQ, "!="); 
	insert_static("!=", d);

	d.internal(FI_INT_GT, ">"); 
	insert_static(">", d);

	d.internal(FI_INT_GE, ">="); 
	insert_static(">=", d);

	d.internal(FI_INT_LT, "<"); 
	insert_static("<", d);

	d.internal(FI_INT_LE, "<="); 
	insert_static("<=", d);

	d.internal(FI_INT_AND, "&&"); 
	insert_static("&&", d);

	d.internal(FI_INT_OR, "||");
	insert_static("||", d);

	d.internal(FI_INT_TO_STR, "string"); 
	insert_static("string", d);

	d.internal(FI_INT_TO_STR, "repr"); 
	insert_static("repr", d);

	d.internal(FI_INT_TO_FLOAT, "float"); 
	insert_static("float", d);

	d.internal(FI_INT_TO_INT, "integer"); 
	insert_static("integer", d);
}

orcaBigInteger::orcaBigInteger() 
{
	// this is the only one copy
	make_original();

	orcaData d;
	d.set_type(TYPE_INTERNAL);

	d.internal(FI_BN_ADD, "+"); 
	insert_static("+", d);

	d.internal(FI_BN_SUB, "-"); 
	insert_static("-", d);

	d.internal(FI_BN_MUL, "*"); 
	insert_static("*", d);

	d.internal(FI_BN_DIV, "/"); 
	insert_static("/", d);

	d.internal(FI_BN_DIV, "%"); 
	insert_static("%", d);

	d.internal(FI_BN_EQ, "=="); 
	insert_static("==", d);

	d.internal(FI_BN_NEQ, "!="); 
	insert_static("!=", d);

	d.internal(FI_BN_GT, ">"); 
	insert_static(">", d);

	d.internal(FI_BN_GE, ">="); 
	insert_static(">=", d);

	d.internal(FI_BN_LT, "<"); 
	insert_static("<", d);

	d.internal(FI_BN_LE, "<="); 
	insert_static("<=", d);

	d.internal(FI_BN_AND, "&&"); 
	insert_static("&&", d);

	d.internal(FI_BN_OR, "||");
	insert_static("||", d);

	d.internal(FI_BN_TO_STR, "string"); 
	insert_static("string", d);

	d.internal(FI_BN_TO_STR, "repr"); 
	insert_static("repr", d);

	d.internal(FI_BN_TO_FLOAT, "float"); 
	insert_static("float", d);

	d.internal(FI_BN_TO_INT, "integer"); 
	insert_static("integer", d);
}


orcaData orcaInteger::ex_add(orcaVM* vm, int i, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(i).operator_add(vm, rhs);
}

orcaData orcaInteger::ex_sub(orcaVM* vm, int i, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(i).operator_sub(vm, rhs);
}

orcaData orcaInteger::ex_mul(orcaVM* vm, int i, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(i).operator_mul(vm, rhs);
}

orcaData orcaInteger::ex_div(orcaVM* vm, int i, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(i).operator_div(vm, rhs);
}

orcaData orcaInteger::ex_mod(orcaVM* vm, int i, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(i).operator_mod(vm, rhs);
}


orcaData orcaInteger::ex_eq(orcaVM* vm, int i, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(i).operator_eq(vm, rhs);
}

orcaData orcaInteger::ex_neq(orcaVM* vm, int i, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(i).operator_neq(vm, rhs);
}

orcaData orcaInteger::ex_gt(orcaVM* vm, int i, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(i).operator_gt(vm, rhs);
}

orcaData orcaInteger::ex_ge(orcaVM* vm, int i, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(i).operator_ge(vm, rhs);
}

orcaData orcaInteger::ex_lt(orcaVM* vm, int i, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(i).operator_lt(vm, rhs);
}

orcaData orcaInteger::ex_le(orcaVM* vm, int i, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(i).operator_le(vm, rhs);
}

orcaData orcaInteger::ex_and(orcaVM* vm, int i, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(i).operator_and(vm, rhs);
}

orcaData orcaInteger::ex_or(orcaVM* vm, int i, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(i).operator_or(vm, rhs);
}

orcaData orcaInteger::ex_string(orcaVM* vm, int i, int param_n) 
{
	if (param_n > 0 && is<TYPE_STR>(vm->get_param(0))) {
		string format = vm->get_param(0).s();
		return format_str(vm, format, i);
	}
	else {
		char buff[20];
		sprintf(buff, "%d", i);
		return buff;
	}

	return NIL;
}

orcaData orcaInteger::ex_float(orcaVM* vm, int i, int param_n) 
{
	return static_cast<double>(i);
}

orcaData orcaInteger::ex_integer(orcaVM* vm, int i, int param_n) 
{
	return i;
}





orcaData orcaBigInteger::ex_add(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	orcaData d = bn;
	orcaData ret = d.operator_add(vm, rhs);
	d.rc_dec();

	return ret;
}

orcaData orcaBigInteger::ex_sub(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	orcaData d = bn;
	orcaData ret = d.operator_sub(vm, rhs);
	d.rc_dec();

	return ret;
}

orcaData orcaBigInteger::ex_mul(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	orcaData d = bn;
	orcaData ret = d.operator_mul(vm, rhs);
	d.rc_dec();

	return ret;
}

orcaData orcaBigInteger::ex_div(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	orcaData d = bn;
	orcaData ret = d.operator_div(vm, rhs);
	d.rc_dec();

	return ret;
}

orcaData orcaBigInteger::ex_mod(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	orcaData d = bn;
	orcaData ret = d.operator_mod(vm, rhs);
	d.rc_dec();

	return ret;
}


orcaData orcaBigInteger::ex_eq(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	orcaData d = bn;
	orcaData ret = d.operator_eq(vm, rhs);
	d.rc_dec();

	return ret;
}

orcaData orcaBigInteger::ex_neq(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	orcaData d = bn;
	orcaData ret = d.operator_neq(vm, rhs);
	d.rc_dec();

	return ret;
}

orcaData orcaBigInteger::ex_gt(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	orcaData d = bn;
	orcaData ret = d.operator_gt(vm, rhs);
	d.rc_dec();

	return ret;
}

orcaData orcaBigInteger::ex_ge(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	orcaData d = bn;
	orcaData ret = d.operator_ge(vm, rhs);
	d.rc_dec();

	return ret;
}

orcaData orcaBigInteger::ex_lt(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	orcaData d = bn;
	orcaData ret = d.operator_lt(vm, rhs);
	d.rc_dec();

	return ret;
}

orcaData orcaBigInteger::ex_le(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	orcaData d = bn;
	orcaData ret = d.operator_le(vm, rhs);
	d.rc_dec();

	return ret;
}

orcaData orcaBigInteger::ex_and(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	orcaData d = bn;
	orcaData ret = d.operator_and(vm, rhs);
	d.rc_dec();

	return ret;
}

orcaData orcaBigInteger::ex_or(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	orcaData d = bn;
	orcaData ret = d.operator_or(vm, rhs);
	d.rc_dec();

	return ret;
}


orcaData orcaBigInteger::ex_string(orcaVM* vm, mpz_t& bn, int param_n) 
{
	if (param_n > 0 && is<TYPE_STR>(vm->get_param(0))) {
		string format = vm->get_param(0).s();
		return format_str(vm, format, bn);
	}
	else {
		string format = "%d";
		orcaData d = orcaData(bn);
		orcaData ret = format_str(vm, format, d);
		d.rc_dec();
		return ret;
	}

	return NIL;
}

orcaData orcaBigInteger::ex_float(orcaVM* vm, mpz_t& bn, int param_n) 
{
	return get_bn_double(bn);
}

orcaData orcaBigInteger::ex_integer(orcaVM* vm, mpz_t& bn, int param_n) 
{
	orcaData d = bn;
	return d;
}

