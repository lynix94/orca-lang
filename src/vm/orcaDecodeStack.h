/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaDecodeStack.h - class for handling "decode statement"

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_DECODE_STACK
#define _DEF_ORCA_DECODE_STACK

#include "orcaListIter.h"

class orcaLocal;
class orcaList;
class orcaVM;

class orcaDecodeStack
{
public:
	struct DECODE 
	{
		DECODE() : next_pattern_addr(0) { }

		int next_pattern_addr;
		int pattern_idx;
		orcaListIter pattern_iter;
		orcaData original;
	};

	orcaDecodeStack(orcaVM* vm);

	void push(orcaData d);
	void pop();

	void init_pattern();
	orcaData get_tail();
	orcaData& get_pattern();

	void set_idx(int idx);
	int get_idx();
	void set_iter(orcaListIter it);
	orcaListIter get_iter();

	void set_next_pattern_addr(int addr);
	int get_next_pattern_addr();

	bool match_str(orcaData p2, short idx);
	bool match_str_shift(orcaData p2, short idx, short shift);
	bool match_list(orcaList* p2, short idx);
	bool match_list_shift(orcaList* p2, short idx, short shift);
	bool match_expr(orcaData p2, short idx);
	bool match_expr_shift(orcaData p2, short idx, short shift);
	bool check_remain();

private:
	vector<DECODE> m_stack;
	DECODE& last(); 

	orcaLocal* m_local;
	orcaVM* m_vm;
};

#endif

