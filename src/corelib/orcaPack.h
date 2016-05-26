/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaPack.h -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_PACK
#define _DEF_ORCA_PACK

#include "porting.h"
#include "orcaObject.h"


using namespace boost;

class orcaPack : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaPack);

	orcaPack();
	string save(orcaData d);
	const char* getline(char** cp);
	orcaData load(char** cp);

	orcaData ex_save(orcaVM* vm, int n);
	orcaData ex_load(orcaVM* vm, int n);
	orcaData ex_dump_code(orcaVM* vm, int n);
	orcaData ex_load_code(orcaVM* vm, int n); 
	orcaData ex_list_code(orcaVM* vm, int n);
	orcaData ex_check_code(orcaVM* vm, int n);
};

extern orcaPack* g_pack;

#endif


