/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaParserObject.h - parse object

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_PARSER_OBJ
#define _DEF_ORCA_PARSER_OBJ

#include "orcaObject.h"
#include "orcaVM.h"
#include "orcaLocal.h"


class orcaParserObject : public orcaObject
{
public:
	orcaParserObject(orcaVM* vm) : m_vm(vm) { }
	orcaData operator()(orcaVM* vm, int n);

private:
	orcaVM* m_vm;
};

#endif

