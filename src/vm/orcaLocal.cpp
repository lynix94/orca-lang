/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaLocal.cpp - impl. of orca local variable stack frame

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <string.h>

#include "orcaLocal.h"
#include "orcaStack.h"
#include "orcaForStack.h"
#include "orcaDecodeStack.h"
#include "orcaException.h"
#include "orcaTuple.h"

orcaLocal::orcaLocal(int size) 
{ 
	m_size = size;
	m_frame = new orcaData[m_size];
	memset(m_frame, 0x00, sizeof(orcaData) * m_size);
	lp = &m_frame[FRAME_HEADER_SIZE];
	lp[IDX_CURSIZE].i_set(0);
}

orcaLocal::~orcaLocal() 
{
	list<orcaData>::iterator li = m_mark.begin();
	for(; li!=m_mark.end(); ++li) {
		(*li).rc_dec();
	}

	delete[] m_frame;
}

void orcaLocal::more()
{
	int idx = lp - m_frame;

	orcaData* tmp = new orcaData[m_size*2];
	memset(tmp, 0x00, sizeof(orcaData)*m_size*2);
	copy(&m_frame[0], &m_frame[m_size], &tmp[0]);
	m_size *= 2;
	delete[] m_frame;

	m_frame = tmp;
	lp = m_frame + idx;
}

orcaData& orcaLocal::unwind()
{
	for (int i = (lp[IDX_CURSIZE].i() - 1); i >= 0; i--) {
		if (is<TYPE_MARK>(lp[i])) {
			return lp[i];
		}
	}

	return NIL;
}

void orcaLocal::save_gc(orcaData d)
{
	vector<orcaData>*vp = (vector<orcaData>*)lp[IDX_GC].o();
	if (vp == NULL) {
		vp = new vector<orcaData>();
		lp[IDX_GC].o((orcaObject*)vp);
	}

	d.rc_inc();
	vp->push_back(d);
}

int orcaLocal::recount_extract_from_stack(orcaStack* st, int count) 
{
	int ret = 0;
	orcaData* op = &st->at(count-1);
	for (int i=0, j=0; i < count; i++) {
		orcaData d = op[i];
		if (is<TYPE_EXTRACT>(d)) {
			orcaTuple* tp = TO_TUPLE(d.o());
			ret += tp->size();
		} else {
			ret++;
		}
	}

	return ret;
}


void orcaLocal::copy_from_stack(orcaStack* st, int count) 
{
	orcaData* op = &st->at(count-1);
	for (int i=0, j=0; i < count; i++) {
		orcaData d = op[i];
		if (is<TYPE_EXTRACT>(d)) {
			orcaTuple* tp = TO_TUPLE(d.o());
			for(int k=0; k<tp->size(); k++) {
				set(j++, tp->at(k));
			}
		} else {
			set(j++, d);
		}
	}

	st->set_pointer(-count);
}

void orcaLocal::dump() 
{
	int idx = lp[IDX_CURSIZE].i();
	printf("# orcaLocal Dump: %d\n", idx);
	for(int i=0; i< idx; i++) {
		printf("  [%d] ", i);
		get(i).dump();
	}
}

void orcaLocal::increase(int size)
{
	int old_size = lp[IDX_CURSIZE].i();

	int remain = m_size - (lp - m_frame) - old_size - FRAME_HEADER_SIZE;
	if (size >= remain) {
		more();
	}
	
	lp += (old_size + FRAME_HEADER_SIZE);
	lp[IDX_GC].o_set(NULL);
	lp[IDX_CALLER].i_set(0);
	lp[IDX_CURSIZE].i_set(size);
	lp[IDX_PREVSIZE].i_set(old_size);

	// 
	// lp[3]
	// lp[2]
	// lp[1]
	// lp[0]
	// new size (4)
	// old size (2)
	// caller
	// for gc
	// old_lp[1]
	// old_lp[0]
	// old size (2)
	// older size (..)
	// caller
	// for gc
	//
}

orcaData orcaLocal::get_mark(mark_e t)
{
	for (int i = lp[IDX_CURSIZE].i() - 1; i>=0; i--) {
		orcaData d = lp[i];
		if (is<TYPE_MARK>(d)) {
			if (d.mark().type == t) {
				return d;
			}
		}
	}

	return NIL;
}


void orcaLocal::clean_mark(mark_e t)
{
	for (int i = lp[IDX_CURSIZE].i() - 1; i>=0; i--) {
		orcaData d = lp[i];
		if (is<TYPE_MARK>(d)) {
			if (d.mark().type == t) {
				d = NIL;
				set(i, d);
				break;
			}
		}
	}
}

void orcaLocal::decrease(bool clean_mark) 
{
	int cur_size = lp[IDX_CURSIZE].i();
	int old_size = lp[IDX_PREVSIZE].i();

	for(int i=0; i<cur_size; i++) {
		if (clean_mark && is<TYPE_MARK>(lp[i])) {
			switch(lp[i].mark().type)
			{
            case MARK_CATCH: 
				delete (CatchList*)lp[i].mark().vp;
				break;

			case MARK_SCOPE: 
			  {
                orcaObject* o = (orcaObject*)lp[i].mark().vp;
                orcaData f = o->get_member("}");
				orcaVM* vm = get_current_vm();
                vm->m_stack->push(f);
                vm->call(0);
                vm->m_stack->pop(); // because it's void type
				break;
              }
            case MARK_FOR:
			  {
				orcaVM* vm = get_current_vm();
                vm->m_for_stack->pop();
				break;
              }
            case MARK_DECODE: 
			  {
				orcaVM* vm = get_current_vm();
                vm->m_decode_stack->pop();
				break;
              }
            case MARK_STACK: 
			  {
				orcaVM* vm = get_current_vm();
                vm->m_stack->pop();
				break;
              }
			}
		}
		lp[i].rc_dec();
		lp[i] = NIL;
	}

	//lp[IDX_CALLER].rc_dec();	// cause, set_caller does'nt increase count
	lp[IDX_CALLER] = NIL;

	vector<orcaData>* vp = (vector<orcaData>*)lp[IDX_GC].o();
	if (vp) {
		for(int i=0; i<vp->size(); i++) {
			(*vp)[i].rc_dec();
		}

		vp->clear();
		delete vp;
	}
	lp[IDX_GC] = NIL;
	lp[IDX_CURSIZE] = NIL;
	lp[IDX_PREVSIZE] = NIL;

	lp -= (old_size + FRAME_HEADER_SIZE);
}

void orcaLocal::mark_return(orcaData d) 
{
	d.rc_inc();
	m_mark.push_back(d);

	// clean up tmp
	if (m_mark.size() > 1000) {
		for(int i=0; i<10; i++) {
			(*m_mark.begin()).rc_dec();
			m_mark.pop_front();
		}
	}
}

void orcaLocal::duplicate(orcaLocal* local)
{
	orcaData* p = lp - FRAME_HEADER_SIZE;
	int size = lp[IDX_CURSIZE].i() + FRAME_HEADER_SIZE;
	
	local->m_frame[0].o_set(NULL);	// GC
	local->m_frame[1] = lp[IDX_CALLER];	// CALLER
	for(int i=2; i<size; i++) {
		p[i].rc_inc();
		local->m_frame[i] = p[i];
	}

	local->lp = local->m_frame + FRAME_HEADER_SIZE;
}



