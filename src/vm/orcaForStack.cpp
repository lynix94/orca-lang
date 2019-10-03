/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaForStack.cpp - class for handling "for statement"

  Copyright (C) 2009 Lee, Ki-Yeul

**********************************************************************/

#include "orcaList.h"
#include "orcaSbf.h"
#include "orcaVirtList.h"
#include "orcaStack.h"
#include "orcaTuple.h"
#include "orcaException.h"
#include "orcaForStack.h"

void FOR::dump()
{
	printf("FOR{ lv1:%d, lv2:%d, idx:%d, limit: %d, is_iter2:%d }\n", lv1, lv2, idx, limit, is_iter2);
}

bool orcaForStack::push(const char* code, int lv, orcaObject* obj, orcaData& out, orcaObject* curr) 
{
	FOR* f = new FOR(code, lv, -1, curr);

	orcaData next, iter;
	if (obj->has_member((char*)"iter", iter)) {
		orcaVM* vm = get_current_vm();
		vm->push_stack(iter);
		vm->call(0); // iter()
		obj = vm->m_stack->pop().Object();
		
	}

	if (obj->has_member((char*)"next", next) == false) {
		throw orcaException(NULL, "orca.type", string("not iterable type ") + obj->dump_str());
	}
	
	if (!is<TYPE_OBJ>(next) && !is<TYPE_NATIVE>(next)) {
		throw orcaException(NULL, "orca.type", "next is not runable");
	}

	f->iter = obj;
	f->next = next;
	push(f);

	int dummy_i;
	orcaData dummy_d;
	const char* dummy_code = cont(&lv, &out, &dummy_i, &dummy_d);
	if (dummy_code == 0) {
		pop();
		return false;
	}

	return true;
}

bool orcaForStack::push_2(const char* code, int lv1, int lv2,
						orcaObject* obj, orcaData& out1, orcaData& out2, orcaObject* curr) 
{
	FOR *f = new FOR(code, lv1, lv2, curr);

	orcaData next, iter;
	if (obj->has_member((char*)"iter2", iter)) {
		orcaVM* vm = get_current_vm();
		vm->push_stack(iter);
		vm->call(0); // iter2()
		obj = vm->m_stack->pop().Object();
		f->is_iter2 = true;
	}
	else if (obj->has_member((char*)"iter", iter)) {
		orcaVM* vm = get_current_vm();
		vm->push_stack(iter);
		vm->call(0); // iter()
		obj = vm->m_stack->pop().Object();
	}

	if (obj->has_member((char*)"next", next) == false) {
		throw orcaException(NULL, "orca.type", string("not iterable type ") + obj->dump_str());
	}

	if (!is<TYPE_OBJ>(next) && !is<TYPE_NATIVE>(next)) {
		throw orcaException(NULL, "orca.type", "next is not runable");
	}

	f->iter = obj;
	f->next = next;
	push(f);
	
	const char* dummy_code = cont(&lv1, &out1, &lv2, &out2);
	if (dummy_code == 0) {
		pop();
		return false;
	}

	return true;
}


bool orcaForStack::push_sub(const char* code, int lv, orcaObject* obj, 
							orcaData& out, orcaObject* curr, int per)
{
	FOR *f = new FOR(code, lv, -1, curr);
	f->limit = per;

	orcaData next, iter;
	if (obj->has_member((char*)"iter", iter)) {
		orcaVM* vm = get_current_vm();
		vm->push_stack(iter);
		vm->call(0); // iter()
		obj = vm->m_stack->pop().Object();
		
	}

	if (obj->has_member((char*)"next", next) == false) {
		throw orcaException(NULL, "orca.type", string("not iterable type ") + obj->dump_str());
	}

	if (!is<TYPE_OBJ>(next) && !is<TYPE_NATIVE>(next)) {
		throw orcaException(NULL, "orca.type", "next is not runable");
	}

	f->iter = obj;
	f->next = next;
	push(f);

	int dummy_i;
	orcaData dummy_d;
	const char* dummy_code = cont(&lv, &out, &dummy_i, &dummy_d);
	if (dummy_code == 0) {
		pop();
		return false;
	}

	return true;
}

void orcaForStack::push(FOR* f)
{
	f->iter.rc_inc();
	f->next.rc_inc();
	m_stack.push_back(f);

	//printf("### push result\n");
	//dump();
}

void orcaForStack::dump()
{
	for (int i=0; i<m_stack.size(); i++) {
		FOR *f = m_stack[i];
		f->dump();
	}
}

FOR* orcaForStack::top() 
{
	return m_stack[m_stack.size()-1];
}

void orcaForStack::pop() 
{
	FOR* f = top();
	f->iter.rc_dec();
	f->next.rc_dec();

	delete f;
	m_stack.pop_back();

	//printf("### pop result\n");
	//dump();

}

const char* orcaForStack::cont(int* lv1, orcaData* d1, int *lv2, orcaData* d2) 
{
	FOR f2 = *top();
	FOR* f = top();
	int depth = m_stack.size();
	f->idx++;
	*d2 = NIL;

	// check limit (per for parallel for sub group)
	if (f->limit >= 0) {
		f->limit--;
		if (f->limit < 0) {
			return 0;
		}
	}

	try {
		orcaVM* vm = get_current_vm();
		vm->push_stack(f->next);
		vm->call(0); // iter.next();
		orcaData result = vm->m_stack->pop();
		if (f->lv2 >= 0) {
			if (f->is_iter2) {
				orcaTuple* tp = castobj<orcaTuple>(result);
				if (tp == NULL || tp->size() != 2) {
					throw orcaException(NULL, "orca.type", "iter2 should return tuple (pair)");
				}

				*d1 = tp->at(0);
				*d2 = tp->at(1);
			}
			else {
				*d1 = f->idx;
				*d2 = result;
			}
		}
		else {
			*d1 = result;
		}
	}
	catch(orcaException& e) {
		if (string("orca.iter.end") != e.who()) {
			throw e;
		}

		e.rc_dec();

		get_current_vm()->m_curr = f->m_curr_back;
		return 0;
	}


	*lv1 = f->lv1;
	*lv2 = f->lv2;

	return f->code;
}

