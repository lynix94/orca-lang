/**********************************************************************

  orcaSelectStack.h - class for handling "select statement"

  Copyright (C) 2009- Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_SELECT_STACK
#define _DEF_ORCA_SELECT_STACK

#include <sys/eventfd.h>
#include <set>

using namespace std;

class orcaVM;
class orcaObject;
class SELECT;


class orcaGlobalSelect // per Machine
{
public:
	void regist(SELECT* sp);
	void unregist(SELECT* sp);
	SELECT* find_select(orcaObject* op);

private:
	set<SELECT*> selects; // machine wide select set
	portMutex mutex;
};

extern orcaGlobalSelect g_select;

struct CASE
{
	orcaObject *src;
	int out_num;
	const char* code;
};

struct SELECT 
{
	SELECT()
	{
		efd = eventfd(0, 0);
	}

	vector<CASE> cases;
	portMutex mutex;
	int efd;

	void push_case(orcaObject* src, int out_num, const char* code);
};

class orcaSelectStack // per VM
{
public:
	orcaSelectStack(orcaVM* vm) : m_vm(vm) {};

	bool push()
	{
		SELECT sel;
		m_stack.push_back(sel);
	};

	SELECT* top()
	{
		if (m_stack.empty()) {
			return NULL;
		}

		SELECT *sel = &m_stack[m_stack.size()-1];
		return sel;
	};

	void pop()
	{
		m_stack.pop_back();
	};

	void push_case(orcaObject* src, int out_num, const char* code);

private:
	vector<SELECT> m_stack;
	orcaVM* m_vm;
};


#endif


