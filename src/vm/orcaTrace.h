/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaTrace.h - impl. of orca stack trace

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_TRACE
#define _DEF_ORCA_TRACE

#include "porting.h"

#include <vector>
#include <string>

class orcaVM;

class LIBORCA_API orcaTrace 
{
public:
	orcaTrace(orcaVM* vm) : m_vm(vm) { top_cp = NULL; top_name = NULL; }

	void push(const char* name, const char* cp); 
	void pop() 
	{
		m_item.pop_back(); 
	}

	std::string dump();

private:
	struct trace_info {
		trace_info(const char* fun, const char* c) : funname(fun), cp(c) {}
		const char* funname;
		const char* cp;
	};
		
	std::vector<trace_info> m_item;
	orcaVM* m_vm;

public:
	const char** top_cp;
	const char* top_name;
};

#endif


