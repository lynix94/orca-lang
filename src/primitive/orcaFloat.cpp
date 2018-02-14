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

	d.internal(FI_FLOAT_TO_STR, "string"); 
	insert_static("string", d);

	d.internal(FI_FLOAT_TO_STR, "repr"); 
	insert_static("repr", d);

	d.internal(FI_FLOAT_TO_INT, "integer"); 
	insert_static("integer", d);

	d.internal(FI_FLOAT_TO_FLOAT, "float"); 
	insert_static("float", d);
}

orcaData orcaFloat::string_(orcaVM* vm, double f) 
{
	if (is<TYPE_STR>(vm->get_param(0))) {
		char buff[1024];

		string format = vm->get_param(0).s();
		snprintf(buff, 1024, format.c_str(), f);
		return buff;
	}
	
	return lexical_cast<string>(f);
}

orcaData orcaFloat::integer(orcaVM* vm, double f) 
{
	return static_cast<int>(f);
}

orcaData orcaFloat::float_(orcaVM* vm, double f) 
{
	return f;
}

