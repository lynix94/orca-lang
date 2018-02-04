/**********************************************************************

  orcaSelectStack.cpp - class for handling "select statement"

  Copyright (C) 2009- Lee, Ki-Yeul

**********************************************************************/

#include <vector>

using namespace std;


#include "porting.h"
#include "orcaSelectStack.h"
#include "orcaObject.h"

orcaGlobalSelect g_select;
void orcaGlobalSelect::regist(SELECT* sp)
{
	mutex.lock();
	selects.insert(sp);
	mutex.unlock();
}

void orcaGlobalSelect::unregist(SELECT* sp)
{
	mutex.lock();
	selects.erase(sp);
	mutex.unlock();
}

SELECT* orcaGlobalSelect::find_select(orcaObject* op)
{
	mutex.lock();
	set<SELECT*>::iterator it = selects.begin();
	for (; it != selects.end(); ++it) {
		SELECT* sp = *it;
		for (int i=0; i<sp->cases.size(); i++) {
			if (sp->cases[i].src == op) {
				mutex.unlock();
				return sp;
			}
		}
	}
	mutex.unlock();
	return NULL;
}


void SELECT::push_case(orcaObject* src, int out_num, const char* code)
{
	CASE new_case;
	new_case.src = src;
	new_case.out_num = out_num;
	new_case.code = code;
	cases.push_back(new_case);
}

void orcaSelectStack::push_case(orcaObject* src, int out_num, const char* code)
{
	top()->push_case(src, out_num, code);
}





