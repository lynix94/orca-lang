/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaLocal.h - impl. of orca local variable stack frame

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_LOCAL
#define _DEF_ORCA_LOCAL

#include "orcaData.h"

#define IDX_CURSIZE		-1
#define IDX_PREVSIZE	-2
#define IDX_CALLER		-3
#define IDX_GC			-4

#define FRAME_HEADER_SIZE	4


class orcaStack;

class LIBORCA_API orcaLocal 
{
friend class orcaSbf;
public:
	orcaLocal(int initialSize=2048); 
	~orcaLocal();

	void reset();

	void set(int i, orcaData d) {
		lp[i].rc_dec();
		lp[i] = d;
		lp[i].rc_inc();
	}

	void force_set(int i, orcaData d) {
		lp[i] = d;
	}

	orcaData get(int i) {
		return lp[i];
	}

	void push_back(orcaData d) {
		set(lp[IDX_CURSIZE].i(), d);
		lp[IDX_CURSIZE].ir()++;
	}

	orcaData top_back() {
		//lp[IDX_CURSIZE].ir()--;
		return get(lp[IDX_CURSIZE].i()-1);
	}

	void pop_back() {
		set(lp[IDX_CURSIZE].i()-1, NIL);
		lp[IDX_CURSIZE].ir()--;
	}

	orcaData get_mark(mark_e t);
	void clean_mark(mark_e t);

	int recount_extract_from_stack(orcaStack* st, int count);
	void copy_from_stack(orcaStack* st, int count);

	void increase(int size);
	void decrease(bool clean_mark=true);

	int get_size() {
		return m_size;
	}

	void save_gc(orcaData d);

	orcaData& unwind();
	void more();
	void dump();

	void mark_return(orcaData d);
	void duplicate(orcaLocal* lp);

private:
	orcaData* m_frame;
	int m_size;
	orcaData* lp;

	list<orcaData> m_mark;
};

#endif

