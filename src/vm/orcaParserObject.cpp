/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaParserObject.cpp - parse object

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/
//#define _VM_DEBUG_
#include "orca_common.h"

#include "orcaParserObject.h"
#include <boost/regex.hpp>

using namespace boost;

#include "orcaStack.h"
#include "orcaException.h"

#include "parserParse.h"



orcaData orcaParserObject::operator()(orcaVM* vm, int n)
{
	if (n<1) vm->need_param();

	string str = vm->get_param(0).String();
	//orcaData ret = parse(str);
	//return ret;
	return NIL;
}


