/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaDL.h - dynamic binding

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_DL
#define _DEF_ORCA_DL

#ifdef WIN32
#include <windows.h>
#else

#endif

#include "porting.h"
#include "orcaObject.h"

using namespace std;

// handle for c-style function pointer
class orcaFP : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaFP);

	orcaFP(void (*fp)(void))
	{
		set_name("fp");
		m_fp = fp;
	}

	orcaData operator()(orcaVM* vm, int n)
	{
		m_fp();
		return NIL;
	}

private:
	
	void (*m_fp)(void);
};



class orcaDL : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaDL);

	orcaDL() : m_handle(NULL)
	{
		set_name("dl");

		insert_native_function("open", (object_fp)&orcaDL::ex_open);
		insert_native_function("func", (object_fp)&orcaDL::ex_func);
		insert_native_function("obj", (object_fp)&orcaDL::ex_obj);

	}

	orcaData ex_open(orcaVM* vm, int n) 
	{
		string& file = vm->get_param(0).String();

		DLHANDLE handle = dlopen(file.c_str(), RTLD_NOW);

		if (handle == NULL) {
			throw orcaException(vm, "orca.name", string("file ") + file + " not exists");
		}

		orcaDL* dl = new orcaDL();
		dl->m_handle = handle;

		return dl;
	}

	orcaData ex_func(orcaVM* vm, int n) 
	{
		if (m_handle == NULL) {
			throw orcaException(vm, "orca.internal", "invalid handle");
		}

		string& func = vm->get_param(0).String();

		typedef void(*fp_t)(void);
		fp_t pfunc = NULL;

		pfunc = (fp_t)dlsym(m_handle, func.c_str());

		if (pfunc == NULL) {
			throw orcaException(vm, "orca.name", string("func ") + func + " not exists");
		}

		orcaFP* fp = new orcaFP(pfunc);
		return fp;
	}

	orcaData ex_obj(orcaVM* vm, int n) 
	{
		if (m_handle == NULL) {
			throw orcaException(vm, "orca.internal", "invalid handle");
		}

		string& obj = vm->get_param(0).String();

		typedef void* (*fp_t)(void);
		fp_t pfunc = NULL;

		pfunc = (fp_t)dlsym(m_handle, (string("get_")+obj).c_str());

		if (pfunc == NULL) {
			throw orcaException(vm, "orca.name", string("object ") + obj + " not exists");
		}

		orcaObject* op = (orcaObject*)pfunc();
		return op;
	}

private:
	DLHANDLE m_handle;
};

#endif

