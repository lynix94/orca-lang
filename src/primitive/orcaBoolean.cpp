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

	d.internal(FI_BOOL_TO_STR, "string");
	insert_static("string", d);

	d.internal(FI_BOOL_TO_INT, "integer");
	insert_static("integer", d);

	d.internal(FI_BOOL_TO_FLOAT, "float");
	insert_static("float", d);
}

orcaData orcaBoolean::string_(orcaVM* vm, int b)
{
	orcaData d;
	b ? d.s_set("True") : d.s_set("False");

	return d;
}

orcaData orcaBoolean::float_(orcaVM* vm, int b)
{
	if (b) return 1.0;
	return 0.0;
}

orcaData orcaBoolean::integer(orcaVM* vm, int b)
{
	if (b) return 1;
	return 0;
}

