/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaForStack.cpp - class for handling "for statement"

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaList.h"
#include "orcaSbf.h"
#include "orcaVirtList.h"
#include "orcaStack.h"
#include "orcaTuple.h"
#include "orcaException.h"
#include "orcaForStack.h"

bool orcaForStack::push(const char* code, int lv, orcaObject* obj,
						orcaData& out, orcaObject* curr) 
{
	FOR f;
	f.code = code;
	f.lv1 = lv;
	f.lv2 = -1;
	f.m_curr_back = curr;

	orcaList* lp = NULL;
	if( (lp = dynamic_cast<orcaList*>(obj)) || 
		(lp = dynamic_cast<orcaSbf*>(obj)) ||
		(lp = dynamic_cast<orcaVirtList*>(obj)) )
	{
		f.lp = lp;
		f.li = f.lp->begin();

		if (f.li == f.lp->end()) {
			return false;
		}

		m_stack.push_back(f);

		out = *f.li;
		return true;
	}
	else if (orcaMap* mp = dynamic_cast<orcaMap*>(obj)) {
		orcaVM* vm = get_current_vm();

		f.mp = mp;
		f.mi = f.mp->begin();

		if (f.mi == f.mp->end()) {
			return false;
		}

		m_stack.push_back(f);

		out = f.mi->first;
		return true;
	}
	else if (orcaTuple* tp = dynamic_cast<orcaTuple*>(obj)) {
		f.vp = &tp->m_value;
		f.vi = f.vp->begin();

		if (f.vi == f.vp->end()) {
			return false;
		}

		m_stack.push_back(f);

		out = *f.vi;
		return true;
	}
	else {
		orcaVM* vm = get_current_vm();

		orcaData next, value;
		if (obj->has_member((char*)"next", next) == false) {
			throw orcaException(vm, "orca.type", string("not iteratable type ") + obj->dump_str());
		}

		try {
			vm->push_stack(obj);
			vm->call(0);		// iter()
			vm->m_stack->pop();
		}
		catch(orcaException& e) {
			if (string("orca.iter") != e.who()) {
				throw e;
			}

			for (int i=0; i<e.argc(); i++) {
				vm->m_stack->pop();
			}

			get_current_vm()->m_curr = curr;
			return false;
		}

		if (is<TYPE_OBJ>(next) || is<TYPE_NATIVE>(next)) {
			f.next = next;
			out = obj;
			m_stack.push_back(f);
			return true;
		}
		else {
			throw orcaException(vm, "orca.type", "next is not runable");
		}
	}

	return false;
}

bool orcaForStack::push_2(const char* code, int lv1, int lv2,
						orcaObject* obj, orcaData& out1, orcaData& out2, orcaObject* curr) 
{
	FOR f;
	f.code = code;
	f.lv1 = lv1;
	f.lv2 = lv2;
	f.m_curr_back = curr;

	orcaList* lp = NULL;
	if( (lp = dynamic_cast<orcaList*>(obj)) || 
		(lp = dynamic_cast<orcaSbf*>(obj)) ||
		(lp = dynamic_cast<orcaVirtList*>(obj)) )
	{
		f.lp = lp;
		f.li = f.lp->begin();

		if (f.li == f.lp->end()) {
			return false;
		}

		m_stack.push_back(f);

		out1 = f.idx;
		out2 = *f.li;
		return true;
	}
	else if (orcaMap* mp = dynamic_cast<orcaMap*>(obj)) {
		f.mp = mp;
		f.mi = f.mp->begin();

		if (f.mi == f.mp->end()) {
			return false;
		}

		m_stack.push_back(f);

		out1 = f.mi->first;
		out2 = f.mi->second;
		return true;
	}
	else if (orcaTuple* tp = dynamic_cast<orcaTuple*>(obj)) {
		f.vp = &tp->m_value;
		f.vi = f.vp->begin();

		if (f.vi == f.vp->end()) {
			return false;
		}

		m_stack.push_back(f);

		out1 = f.idx;
		out2 = *f.vi;
		return true;
	}
	else {
		orcaVM* vm = get_current_vm();

		orcaData next, value;
		if (obj->has_member((char*)"next", next) == false) {
			throw orcaException(vm, "orca.type", string("not iteratable type ") + obj->dump_str());
		}

		try {
			vm->push_stack(obj);
			vm->call(0);		// iter()
			vm->m_stack->pop();
		}
		catch(orcaException& e) {
			if (string("orca.iter") != e.who()) {
				throw e;
			}

			for (int i=0; i<e.argc(); i++) {
				vm->m_stack->pop();
			}

			get_current_vm()->m_curr = curr;
			return false;
		}

		if (is<TYPE_OBJ>(next) || is<TYPE_NATIVE>(next)) {
			f.next = next;
			out1 = f.idx;
			out2 = obj;
			m_stack.push_back(f);
			return true;
		}
		else {
			throw orcaException(vm, "orca.type", "next is not runable");
		}
	}

	return false;
}


bool orcaForStack::push_sub(const char* code, int lv, orcaObject* obj, 
							orcaData& out, orcaObject* curr, int per, bool is_iterator)
{
	FOR f;
	f.code = code;
	f.lv1 = lv;
	f.lv2 = -1;
	f.m_curr_back = curr;
	f.count = per;
	f.is_iterator = is_iterator;

	orcaVM* vm = get_current_vm();

	orcaData next, value;
	if (obj->has_member((char*)"next", next) == false) {
		throw orcaException(vm, "orca.type", string("not iteratable type ") + obj->dump_str());
	}

	try {
		vm->push_stack(obj);
		vm->call(0);		// iter()
		value = vm->m_stack->pop();
	}
	catch(orcaException& e) {
		if (string("orca.iter") != e.who()) {
			throw e;
		}

		for (int i=0; i<e.argc(); i++) {
			vm->m_stack->pop();
		}

		get_current_vm()->m_curr = curr;
		return false;
	}

	if (is<TYPE_OBJ>(next) || is<TYPE_NATIVE>(next)) {
		f.next = next;

		if (is_iterator) {
			out = obj;
		}
		else {
			out = value;
		}

		m_stack.push_back(f);
		return true;
	}
	else {
		throw orcaException(vm, "orca.type", "next is not runable");
	}

	return false;
}


orcaForStack::FOR* orcaForStack::top() 
{
	return &m_stack[m_stack.size()-1];
}

void orcaForStack::pop() 
{
	m_stack.pop_back();
}

const char* orcaForStack::cont(int* lv1, orcaData* d1, int *lv2, orcaData* d2) 
{
	FOR* f = top();
	f->idx++;
	*d2 = NIL;

	// check count (per for parallel for sub group)
	if (f->count >= 0) {
		f->count--;
		if (f->count == 0) {
			return 0;
		}
	}

	if (f->lp != NULL) {
		f->li++;

		if (f->li == f->lp->end()) {
			return 0;
		}
		else {
			if (f->lv2 > 0) {
				*d1  = f->idx;
				*d2  = *f->li;
			}
			else {
				*d1  = *f->li;
			}
		}
	}
	else if (f->mp != NULL) {
		f->mi++;

		if (f->mi == f->mp->end()) {
			return 0;
		}
		else {
			orcaVM* vm = get_current_vm();
			*d1  = f->mi->first;
			*d2  = f->mi->second;
		}
	}
	else if (f->vp != NULL) {
		f->vi++;

		if (f->vi == f->vp->end()) {
			return 0;
		}
		else {
			if (f->lv2 > 0) {
				*d1  = f->idx;
				*d2  = *f->vi;
			}
			else {
				*d1  = *f->vi;
			}
		}
	}
	else {
		orcaVM* vm = get_current_vm();
		try {
			orcaData iter;
			vm->push_stack(f->next);
			vm->call(0); // iter.next();
			iter = vm->m_stack->top();
			if (is<TYPE_NIL>(iter)) {
				vm->m_stack->pop();
				return 0;
			}

			if (f->is_iterator) {
				vm->m_stack->pop();
				if (f->lv2 > 0) {
					*d1  = f->idx;
					*d2 = iter;
				}
				else {
					*d1 = iter;
				}
			}
			else {
				vm->call(0); // iter()
				if (f->lv2 > 0) {
					*d1  = f->idx;
					*d2 = vm->m_stack->pop();
				}
				else {
					*d1 = vm->m_stack->pop();
				}
			}
		}
		catch(orcaException& e) {
			if (string("orca.iter") != e.who()) {
				throw e;
			}

			for (int i=0; i<e.argc(); i++) {
				vm->m_stack->pop();
			}

			get_current_vm()->m_curr = f->m_curr_back;
			return 0;
		}
	}

	*lv1 = f->lv1;
	*lv2 = f->lv2;

	return f->code;
}

