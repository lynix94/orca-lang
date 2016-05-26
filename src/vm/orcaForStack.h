/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaForStack.h - class for handling "for statement"

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_FOR_STACK
#define _DEF_ORCA_FOR_STACK

class orcaList;

#include "orcaListIter.h"

class orcaForStack
{
public:
	struct FOR 
	{
		FOR() : lp(NULL), vp(NULL), next(NIL), count(-1), is_iterator(true) { }

		const char* code;
		int lv;
		int count;
		bool is_iterator;

		// fix. someday, let's pack belows as union

		// for list type
		orcaListIter li;
		orcaList* lp;

		// for vector type
		vector<orcaData>::iterator vi;
		vector<orcaData>* vp;

		// for iterator type
		orcaData next; 

		orcaObject* m_curr_back;
	};

	bool push(const char* code, int lv, orcaObject* obj, orcaData& d, 
			  orcaObject* curr);

	bool push_sub(const char* code, int lv, orcaObject* obj, orcaData& d, 
				  orcaObject* curr, int per, bool is_iterator);
	FOR* top();
	void pop();
	const char* cont(int* lv, orcaData* data);

private:
	vector<FOR> m_stack;
};


#endif


