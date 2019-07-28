/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserOP.h - manage opcodes of parser

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_PARSER_OP
#define _DEF_PARSER_OP

#include "parserCode.h"

class parserOP 
{
public:
	parserOP();

	// about assign
	void assign_local(const char* name);
	void assign_member(const char* s);
	void assign_reserved(int op);
	void assign_list(bool include_right);

	// about op
	void call(int pnum);
	bool change_to_parallel_call();
	void mul();
	void mod();
	void add();
	void div();
	void sub();
	void do_and();
	void do_and_short_check();
	void do_or();
	void gt();
	void ge();
	void lt();
	void le();
	void eq();
	void neq();
	void clone(int argc);
	void insert_member(int argc);
	void insert_static_member(int argc);
	void update_member(int argc);
	void remove_member(int argc);
	void has_member(int argc);
	void get_member(int argc);
	void listat(bool include_right);
	void pop_stack();
	void fast_pop_stack();
	void disable_fast_pop();
	void minus();
	void do_not();
	void rotate();
	void rotate3();
	void dup();
	void dup2();
	void eval();
	void compile();
	void do_scope_start();
	void do_scope_end();
	void do_rc_inc();
	void do_rc_dec();
	void extract();

	// about make
	void make_list(int n);
	void make_tuple(int n);
	void make_pair();
	void make_regex();
	void make_map(int n);

	// ABOUT push
	bool check_lvar(const char* s);
	void push_lvar(const char* s);
	void push_mvar(const char* s);
	void push_ovar(const char* s);
	void push_cvar(const char* s);
	void find_member(const char* s);
	void set_last_find_position();
	void clear_last_find_position();
	void fix_last_find_position();
	void find_reserved(int o);
	void push_reserved(int OP);
	void push_nil();
	void push_integer(int i);
	void push_bignum(char sign, const char* s);
	void push_real(double d);
	void push_boolean(bool tf);
	void push_string(const char* s);

	// for debug
	void dump_stack();
	void dump_local();

	bool push_mvar_using_space(const char* s);
private:
	int m_last_call_idx; // used for parallel call
	int m_last_idx; // index to op code which push stack
	int m_last_find;
};

extern parserOP* g_op; 

#endif

