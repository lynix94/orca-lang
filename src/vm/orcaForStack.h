/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaForStack.h - class for handling "for statement"

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_FOR_STACK
#define _DEF_ORCA_FOR_STACK

class orcaList;
class orcaMap;

#include "orcaListIter.h"
#include "orcaMapIter.h"


struct FOR 
{
	FOR(const char* code, int lv1, int lv2, orcaObject* curr) : 
		code(code), lv1(lv1), lv2(lv2), m_curr_back(curr), limit(-1), idx(-1), is_iter2(false) {}

	virtual ~FOR() {}

	const char* code;
	int lv1;
	int lv2;
	int idx;
	int limit;
	bool is_iter2;

	orcaObject* m_curr_back;
	orcaData source; 
	orcaData iter; 
	orcaData next; 

	void dump();
};


class orcaForStack
{
public:
	bool push(const char* code, int lv, orcaObject* obj, orcaData& d, orcaObject* curr);
	bool push_2(const char* code, int lv1, int lv2, orcaObject* obj, orcaData& d1, orcaData& d2, orcaObject* curr);

	bool push_sub(const char* code, int lv, orcaObject* obj, orcaData& d, 
				  orcaObject* curr, int per);
	FOR* top();
	void pop();
	void push(FOR* f);
	const char* cont(int* lv1, orcaData* d1, int* lv2, orcaData* d2);

	int size() { return m_stack.size(); }
	void dump();

private:
	vector<FOR*> m_stack;
};


#endif


