/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaMath.h -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_MATH
#define _DEF_ORCA_MATH

#include <math.h>

#include "porting.h"
#include "orcaObject.h"
#include "orcaRandom.h"

class orcaMath : public orcaObject 
{
public:
	orcaMath()
	{
		set_name("math");
		insert_static_native_function("sin", (object_fp)&orcaMath::ex_sin);
		insert_static_native_function("cos", (object_fp)&orcaMath::ex_cos);
		insert_static_native_function("tan", (object_fp)&orcaMath::ex_tan);

		insert_static_native_function("asin", (object_fp)&orcaMath::ex_asin);
		insert_static_native_function("acos", (object_fp)&orcaMath::ex_acos);
		insert_static_native_function("atan", (object_fp)&orcaMath::ex_atan);
		insert_static_native_function("atan2", (object_fp)&orcaMath::ex_atan2);

		insert_static_native_function("sinh", (object_fp)&orcaMath::ex_sinh);
		insert_static_native_function("cosh", (object_fp)&orcaMath::ex_cosh);
		insert_static_native_function("tanh", (object_fp)&orcaMath::ex_tanh);

		insert_static_native_function("exp", (object_fp)&orcaMath::ex_exp);
		insert_static_native_function("frexp", (object_fp)&orcaMath::ex_frexp);
		insert_static_native_function("ldexp", (object_fp)&orcaMath::ex_ldexp);
		insert_static_native_function("log", (object_fp)&orcaMath::ex_log);
		insert_static_native_function("log10", (object_fp)&orcaMath::ex_log10);
		insert_static_native_function("modf", (object_fp)&orcaMath::ex_modf);

		insert_static_native_function("pow", (object_fp)&orcaMath::ex_pow);
		insert_static_native_function("sqrt", (object_fp)&orcaMath::ex_sqrt);

		insert_static_native_function("ceil", (object_fp)&orcaMath::ex_ceil);
		insert_static_native_function("fabs", (object_fp)&orcaMath::ex_fabs);
		insert_static_native_function("floor", (object_fp)&orcaMath::ex_floor);
		insert_static_native_function("fmod", (object_fp)&orcaMath::ex_fmod);

		insert_static("random", new orcaRandom());
	}

	orcaData ex_sin(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return sin(vm->get_param(0).Double());
	}

	orcaData ex_cos(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return cos(vm->get_param(0).Double());
	}

	orcaData ex_tan(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return tan(vm->get_param(0).Double());
	}

	orcaData ex_asin(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return asin(vm->get_param(0).Double());
	}

	orcaData ex_acos(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return acos(vm->get_param(0).Double());
	}

	orcaData ex_atan(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return atan(vm->get_param(0).Double());
	}

	orcaData ex_atan2(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();
		return atan2(vm->get_param(0).Double(), vm->get_param(1).Double());
	}

	orcaData ex_sinh(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return sinh(vm->get_param(0).Double());
	}

	orcaData ex_cosh(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return cosh(vm->get_param(0).Double());
	}

	orcaData ex_tanh(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return tanh(vm->get_param(0).Double());
	}

	orcaData ex_exp(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return exp(vm->get_param(0).Double());
	}

	orcaData ex_frexp(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		double s;
		int e;
		s = frexp(vm->get_param(0).Double(), &e);

		orcaTuple* tp = new orcaTuple();
		tp->push_back(s);
		tp->push_back(e);

		return tp;
	}

	orcaData ex_ldexp(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();
		return ldexp(vm->get_param(0).Double(), vm->get_param(1).Integer());
	}

	orcaData ex_log(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return log(vm->get_param(0).Double());
	}

	orcaData ex_log10(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return log10(vm->get_param(0).Double());
	}

	orcaData ex_modf(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		double f;
		double i;
		f = modf(vm->get_param(0).Double(), &i);

		orcaTuple* tp = new orcaTuple();
		tp->push_back(f);
		tp->push_back(i);

		return tp;
	}

	orcaData ex_pow(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();
		return pow(vm->get_param(0).Double(), vm->get_param(1).Double());
	}

	orcaData ex_sqrt(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return sqrt(vm->get_param(0).Double());
	}

	orcaData ex_ceil(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return ceil(vm->get_param(0).Double());
	}

	orcaData ex_fabs(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return fabs(vm->get_param(0).Double());
	}

	orcaData ex_floor(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		return floor(vm->get_param(0).Double());
	}

	orcaData ex_fmod(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();
		return fmod(vm->get_param(0).Double(), vm->get_param(1).Double());
	}
};


#endif

