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

	d.internal(FI_BN_TO_STR, "string"); 
	insert_static("string", d);

	d.internal(FI_BN_TO_FLOAT, "float"); 
	insert_static("float", d);

	d.internal(FI_BN_TO_INT, "integer"); 
	insert_static("integer", d);
}


orcaData orcaInteger::string_(orcaVM* vm, int i) 
{
	if (is<TYPE_STR>(vm->get_param(0))) {
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

orcaData orcaBigInteger::string_(orcaVM* vm, mpz_t& bn) 
{
	if (is<TYPE_STR>(vm->get_param(0))) {
		string format = vm->get_param(0).s();
		return format_str(vm, format, bn);
	}
	else {
		string format = "%d";
		return format_str(vm, format, bn);
	}

	return NIL;
}

orcaData orcaInteger::float_(orcaVM* vm, int i) 
{
	return static_cast<double>(i);
}

orcaData orcaBigInteger::float_(orcaVM* vm, mpz_t& bn) 
{
	return get_bn_double(bn);
}

orcaData orcaInteger::integer(orcaVM* vm, int i) 
{
	return i;
}

orcaData orcaBigInteger::integer(orcaVM* vm, mpz_t& bn) 
{
	orcaData d = bn;
	return d;
}

