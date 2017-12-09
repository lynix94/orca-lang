/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaStack.h - impl. of orca stack frame

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_STACK
#define _DEF_ORCA_STACK

#include "orcaData.h"
#include "orcaLocal.h"
#include "orcaObject.h"

class LIBORCA_API orcaStack
{
public:
	orcaStack(orcaLocal* local);
	~orcaStack();
	bool empty() {
		return (m_sp < 0) ? true : false;
	}

	void push(const orcaData& d) {
		if (m_sp == m_size-1) more();
		m_frame[++m_sp] = d;
	}

	void replace(const orcaData& d) {
		rc_check(m_frame[m_sp]);
		m_frame[m_sp] = d;
	}

	orcaData& pop() {
		rc_check(m_frame[m_sp]);
		return m_frame[m_sp--];
	}

	orcaData& top() {
		return m_frame[m_sp];
	}

	orcaData& at(int i) {
		return m_frame[m_sp - i];
	}

	void set(int i, orcaData& d) {
		rc_check(m_frame[m_sp - i]);
		m_frame[m_sp - i] = d;
	}

	void dummy_pop() {
		rc_check(m_frame[m_sp]);
		m_sp--;
	}

	void dummy_pop(int c) {
		for (int i=0; i<c; i++) {
			dummy_pop();
		}
	}

	void set_pointer(int i) {
		m_sp += i;
	}

	void rotate() {
		std::swap(m_frame[m_sp], m_frame[m_sp-1]);
	}

	void dup() {
		push(m_frame[m_sp]);
	}

	void dup2() {
		push(m_frame[m_sp-1]);
		push(m_frame[m_sp-1]);
	}

	void more();
	void dump();

	void rc_check(orcaData p) {
		if (p.get_rc() == 0) {
			m_local->save_gc(p);
		}
	}

private:
	orcaData* m_frame;
	orcaLocal* m_local;
	int m_size;
	int m_sp;
};

#endif

