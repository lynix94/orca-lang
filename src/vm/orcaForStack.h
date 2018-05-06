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


enum for_source_type
{
	FOR_SOURCE_LIST,
	FOR_SOURCE_VECTOR,
	FOR_SOURCE_MAP,
	FOR_SOURCE_ITER,
};

struct FOR 
{
	FOR(const char* code, int lv1, int lv2, orcaObject* curr) : 
		code(code), lv1(lv1), lv2(lv2), m_curr_back(curr), limit(-1), idx(0), is_iterator(true) {}

	virtual ~FOR() {}

	const char* code;
	int lv1;
	int lv2;
	int idx;
	int limit;
	bool is_iterator;
	for_source_type type;

	orcaObject* m_curr_back;
};

struct FOR_LIST : public FOR
{
	FOR_LIST(const char* code, int lv1, int lv2, orcaObject* curr) : FOR(code, lv1, lv2, curr)
	{
		type = FOR_SOURCE_LIST;
	}

	virtual ~FOR_LIST() {}

	orcaListIter li;
	orcaList* lp;
};

struct FOR_VECTOR : public FOR
{
	FOR_VECTOR(const char* code, int lv1, int lv2, orcaObject* curr) : FOR(code, lv1, lv2, curr)
	{
		type = FOR_SOURCE_VECTOR;
	}

	virtual ~FOR_VECTOR() {}

	vector<orcaData>::iterator vi;
	vector<orcaData>* vp;
};

struct FOR_MAP : public FOR
{
	FOR_MAP(const char* code, int lv1, int lv2, orcaObject* curr) : FOR(code, lv1, lv2, curr)
	{
		type = FOR_SOURCE_MAP;
	}

	virtual ~FOR_MAP() {}

	orcamap_iterator mi;
	orcaMap* mp;
};


struct FOR_ITER : public FOR
{
	FOR_ITER(const char* code, int lv1, int lv2, orcaObject* curr) : FOR(code, lv1, lv2, curr)
	{
		type = FOR_SOURCE_ITER;
	}

	virtual ~FOR_ITER() {}

	orcaData next; 
};

class orcaForStack
{
public:
	bool push(const char* code, int lv, orcaObject* obj, orcaData& d, orcaObject* curr);
	bool push_2(const char* code, int lv1, int lv2, orcaObject* obj, orcaData& d1, orcaData& d2, orcaObject* curr);

	bool push_sub(const char* code, int lv, orcaObject* obj, orcaData& d, 
				  orcaObject* curr, int per, bool is_iterator);
	FOR* top();
	void pop();
	const char* cont(int* lv1, orcaData* d1, int* lv2, orcaData* d2);

private:
	vector<FOR*> m_stack;
};


#endif


