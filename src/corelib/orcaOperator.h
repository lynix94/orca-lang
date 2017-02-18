/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaOperator.h -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_OPERATOR
#define _DEF_ORCA_OPERATOR

#include "porting.h"
#include "orcaObject.h"

class orcaOperator : public orcaObject 
{
public:
	orcaOperator()
	{
		set_name("operator");
		insert_static_native_function("+", (object_fp)&orcaOperator::ex_add);
		insert_static_native_function("-", (object_fp)&orcaOperator::ex_sub);
		insert_static_native_function("*", (object_fp)&orcaOperator::ex_mul);
		insert_static_native_function("/", (object_fp)&orcaOperator::ex_div);
		insert_static_native_function("%", (object_fp)&orcaOperator::ex_mod);
		insert_static_native_function("==", (object_fp)&orcaOperator::ex_eq);
		insert_static_native_function("!=", (object_fp)&orcaOperator::ex_neq);
		insert_static_native_function("<", (object_fp)&orcaOperator::ex_lt);
		insert_static_native_function("<=", (object_fp)&orcaOperator::ex_le);
		insert_static_native_function(">", (object_fp)&orcaOperator::ex_gt);
		insert_static_native_function(">=", (object_fp)&orcaOperator::ex_ge);
		insert_static_native_function("&&", (object_fp)&orcaOperator::ex_and);
		insert_static_native_function("||", (object_fp)&orcaOperator::ex_or);
	}

	orcaData ex_add(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p1 = vm->get_param(0);
		orcaData p2 = vm->get_param(1);

		return p1.operator_add(vm, p2);
	}

	orcaData ex_sub(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p1 = vm->get_param(0);
		orcaData p2 = vm->get_param(1);

		return p1.operator_sub(vm, p2);
	}

	orcaData ex_mul(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p1 = vm->get_param(0);
		orcaData p2 = vm->get_param(1);

		return p1.operator_mul(vm, p2);
	}

	orcaData ex_div(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p1 = vm->get_param(0);
		orcaData p2 = vm->get_param(1);

		return p1.operator_div(vm, p2);
	}

	orcaData ex_mod(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p1 = vm->get_param(0);
		orcaData p2 = vm->get_param(1);

		return p1.operator_mod(vm, p2);
	}

	orcaData ex_lt(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p1 = vm->get_param(0);
		orcaData p2 = vm->get_param(1);

		return p1.operator_lt(vm, p2);
	}

	orcaData ex_gt(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p1 = vm->get_param(0);
		orcaData p2 = vm->get_param(1);

		return p1.operator_gt(vm, p2);
	}

	orcaData ex_le(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p1 = vm->get_param(0);
		orcaData p2 = vm->get_param(1);

		return p1.operator_le(vm, p2);
	}

	orcaData ex_ge(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p1 = vm->get_param(0);
		orcaData p2 = vm->get_param(1);

		return p1.operator_ge(vm, p2);
	}

	orcaData ex_eq(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p1 = vm->get_param(0);
		orcaData p2 = vm->get_param(1);

		return p1.operator_eq(vm, p2);
	}

	orcaData ex_neq(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p1 = vm->get_param(0);
		orcaData p2 = vm->get_param(1);

		return p1.operator_neq(vm, p2);
	}

	orcaData ex_and(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p1 = vm->get_param(0);
		orcaData p2 = vm->get_param(1);

		return p1.operator_and(vm, p2);
	}

	orcaData ex_or(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p1 = vm->get_param(0);
		orcaData p2 = vm->get_param(1);

		return p1.operator_or(vm, p2);
	}
};


#endif

