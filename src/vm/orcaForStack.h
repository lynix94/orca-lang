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

class orcaForStack
{
public:
	struct FOR 
	{
		FOR() : lp(NULL), vp(NULL), mp(NULL), next(NIL), count(-1), idx(0), is_iterator(true) { }

		const char* code;
		int lv1;
		int lv2;
		int idx;
		int count;
		bool is_iterator;

		// fix. someday, let's pack belows as union

		// for list type
		orcaListIter li;
		orcaList* lp;

		// for vector type
		vector<orcaData>::iterator vi;
		vector<orcaData>* vp;

		// for map type
		orcamap_iterator mi;
		orcaMap* mp;

		// for iterator type
		orcaData next; 

		orcaObject* m_curr_back;
	};

	bool push(const char* code, int lv, orcaObject* obj, orcaData& d, orcaObject* curr);
	bool push_2(const char* code, int lv1, int lv2, orcaObject* obj, orcaData& d1, orcaData& d2, orcaObject* curr);

	bool push_sub(const char* code, int lv, orcaObject* obj, orcaData& d, 
				  orcaObject* curr, int per, bool is_iterator);
	FOR* top();
	void pop();
	const char* cont(int* lv1, orcaData* d1, int* lv2, orcaData* d2);

private:
	vector<FOR> m_stack;
};


#endif


