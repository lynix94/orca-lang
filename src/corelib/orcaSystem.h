/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaSystem.h - system utils

  Copyright (C) 2009-2010 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_SYSTEM
#define _DEF_ORCA_SYSTEM


#include "porting.h"

#ifdef WINDOWS
#else
#include <unistd.h>
#endif



namespace fs = boost::filesystem;

using namespace std;
using namespace boost;

class orcaSystem : public orcaObject 
{
public:
	orcaSystem() 
	{
		set_name("system");

		insert_static_native_function("cpu_n", (object_fp)&orcaSystem::ex_cpu_n);
		insert_static_native_function("memory", (object_fp)&orcaSystem::ex_memory);
		insert_static_native_function("free", (object_fp)&orcaSystem::ex_free);
		insert_static_native_function("os", (object_fp)&orcaSystem::ex_os);
		insert_static_native_function("version", (object_fp)&orcaSystem::ex_version);
	}

	orcaData ex_cpu_n(orcaVM* vm, int n) 
	{
		return port_cpu_num();
	}

	orcaData ex_os(orcaVM* vm, int n) 
	{
		return port_os();
	}

	orcaData ex_version(orcaVM* vm, int n) 
	{
		return ORCA_VERSION_STRING;
	}

	orcaData ex_memory(orcaVM* vm, int n) 
	{
		orcaData ret;
		ret.bn_set(port_memory());
		return ret;
	}

	orcaData ex_free(orcaVM* vm, int n) 
	{
		orcaData ret;
		ret.bn_set(port_free());
		return ret;
	}
};

#endif

