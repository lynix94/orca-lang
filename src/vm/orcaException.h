/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaException.h - handling exception & catch

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_EXCEPTION
#define _DEF_ORCA_EXCEPTION

#include <deque>
#include <vector>
#include <string>

#include "orca_opcode.h"
#include "orcaData.h"
#include "orcaStack.h"
#include "orcaTrace.h"

using namespace std;


class orcaVM;
class orcaObject;
class orcaException
{
public:
	orcaException() { }
	orcaException(orcaVM* vm, const char* id, string msg = "");
	orcaException(orcaVM* vm, const char* id, int argc);

	~orcaException() { }

	void rc_inc();
	void rc_dec();

	void make_trace();
	const char* who()
	{
		return m_id;
	}

	const char* what();
	int argc()
	{
		return params.size();
	}

private:
	const char* m_id;
	string what_buff;
	orcaVM* m_vm;

public:
	deque<orcaData> params;
	string m_stack_trace;
};

struct catch_t 
{
	const char* name;
	int address;
	vector<int> lv;
};

struct CatchList 
{
	vector<catch_t> catch_list;
	orcaObject* m_my;
	int stack_size;

	CatchList(const char* code, int num, orcaObject* my, int stack_size);
	catch_t* compare(const char* name);

	void clear()
	{
		catch_list.clear();
	}

	void dump();
};

#endif


