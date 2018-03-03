/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaNil.cpp - boolean type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaNil.h"
#include "orcaVM.h"

orcaNil g_nil;

orcaNil::orcaNil() 
{		
	// this is the only one copy
	make_original();

	orcaData d;
	d.set_type(TYPE_INTERNAL);

	d.internal(FI_NIL_TO_STR, "string");
	insert_static("string", d);

	d.internal(FI_NIL_TO_STR, "repr");
	insert_static("repr", d);
}

orcaData orcaNil::string_()
{
	return "nil";
}

