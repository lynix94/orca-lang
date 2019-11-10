/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserOP.cpp - manage opcodes of parser

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "parserOP.h"
#include "orca_opcode.h"
#include "parserControl.h"

#pragma warning (disable : 4309)  // 0xf2 to push_char

void yyerror(const char* msg);
extern int g_lvar_nil_check;
extern parserControl* g_ctl;

#ifndef CHAR_MAX
#define CHAR_MAX 0x7f
#endif

parserOP s_op;
parserOP* g_op = &s_op;

parserOP::parserOP()
{
	m_last_idx = 0;
	m_last_call_idx = 0;
}

void parserOP::assign_local(const char* name)	
{
	short idx = code_top->find_lvar(name);
	m_last_idx = code_top->size();

	code_top->push_char(OP_ASSIGN_LOCAL); 
	code_top->push_short(idx);
}

void parserOP::assign_member(const char* s)	
{
	m_last_idx = code_top->size();
	code_top->push_char(OP_ASSIGN_MEMBER); 
	code_top->push_string(s);
}

void parserOP::assign_reserved(int op)	
{
	m_last_idx = code_top->size();
	code_top->push_char(OP_ASSIGN_RESERVED); 
	code_top->push_char(op);
}

void parserOP::assign_list(bool include_right)	
{
	m_last_idx = code_top->size();

	if (include_right)
		code_top->push_char(OP_ASSIGN_LIST_IR); 
	else
		code_top->push_char(OP_ASSIGN_LIST); 
}

#include <stdio.h>

void parserOP::call(int pnum)		
{ 
	m_last_idx = code_top->size();
	m_last_call_idx = code_top->size();
	code_top->push_char(OP_CALL); 
	code_top->push_char(pnum);
}

bool parserOP::change_to_parallel_call()		
{ 
	int curr_size = code_top->size();
	if ((curr_size - 2) == m_last_call_idx) {
		code_top->set_char(OP_PARALLEL_CALL, m_last_call_idx);
		return true;
	}

	return false; // syntax error
}

void parserOP::disable_fast_pop()
{
	m_last_idx = 0;
}

void parserOP::fast_pop_stack()
{
	if (false && m_last_idx > 0) {
		char op = code_top->get_char(m_last_idx);
		code_top->set_char(op+1, m_last_idx);
	}
	else {
		pop_stack();
	}

	m_last_idx = 0;
}

void parserOP::mul()		
{
	code_top->push_char(OP_MUL); 
}

void parserOP::mod()		
{
	code_top->push_char(OP_MOD); 
}

void parserOP::add()		
{ 
	code_top->push_char(OP_ADD); 
}

void parserOP::div()		
{ 
	code_top->push_char(OP_DIV); 
}

void parserOP::sub()		
{
	code_top->push_char(OP_SUB);
}

void parserOP::do_and()		
{
	code_top->push_char(OP_AND);
}

void parserOP::do_or()		
{
	code_top->push_char(OP_OR);
}

void parserOP::gt()		
{
	code_top->push_char(OP_GT);
}

void parserOP::ge()		
{
	code_top->push_char(OP_GE);
}

void parserOP::lt()		
{
	code_top->push_char(OP_LT);
}

void parserOP::le()		
{
	code_top->push_char(OP_LE);
}

void parserOP::eq()		
{
	code_top->push_char(OP_EQ);
}

void parserOP::neq()		
{
	code_top->push_char(OP_NEQ);
}

void parserOP::clone(int argc)		
{
	code_top->push_char(OP_CLONE);
	code_top->push_char(argc);
}

void parserOP::listat(bool include_right)	
{
	if (include_right)
		code_top->push_char(OP_LIST_AT_IR);
	else
		code_top->push_char(OP_LIST_AT);
}

void parserOP::pop_stack() 
{
	code_top->push_char(OP_POP_STACK);
}

void parserOP::minus()		
{
	code_top->push_char(OP_MINUS);
}

void parserOP::do_not()		
{
	code_top->push_char(OP_NOT);
}

void parserOP::rotate()	
{
	code_top->push_char(OP_ROTATE);
}

void parserOP::rotate3()	
{
	code_top->push_char(OP_ROTATE3);
}

void parserOP::dup()
{
	code_top->push_char(OP_DUP);
}

void parserOP::dup2()
{
	code_top->push_char(OP_DUP2);
}

void parserOP::eval()
{
	code_top->push_char(OP_EVAL);
}

void parserOP::compile()
{
	code_top->push_char(OP_COMPILE);
}

void parserOP::extract()
{
	code_top->push_char(OP_EXTRACT);
}

void parserOP::do_rc_inc()		
{
	code_top->push_char(OP_RC_INC); 
}

void parserOP::do_rc_dec()		
{
	code_top->push_char(OP_RC_DEC); 
}

void parserOP::make_list(int n) 
{ 
	if (n < CHAR_MAX) {
		code_top->push_char(OP_MAKE_LIST); 
		code_top->push_char(n); 
	}
	else {
		code_top->push_char(OP_MAKE_LONG_LIST); 
		code_top->push_int(n); 
	}
}

void parserOP::make_tuple(int n) 
{ 
	if (n < CHAR_MAX) {
		code_top->push_char(OP_MAKE_TUPLE); 
		code_top->push_char(n); 
	}
	else {
		code_top->push_char(OP_MAKE_LONG_TUPLE); 
		code_top->push_int(n); 
	}
}

void parserOP::make_map(int n) 
{ 
	if (n < CHAR_MAX) {
		code_top->push_char(OP_MAKE_MAP); 
		code_top->push_char(n); 
	}
	else {
		code_top->push_char(OP_MAKE_LONG_MAP); 
		code_top->push_int(n); 
	}
}

void parserOP::make_pair()		
{
	code_top->push_char(OP_MAKE_PAIR); 
}

void parserOP::make_regex()		
{
	code_top->push_char(OP_MAKE_REGEX); 
}

#include <stdio.h>

bool parserOP::check_lvar(const char* s)/*{{{*/
{ 
	if (g_lvar_nil_check < 0) {
		return true;
	}

	// first, check if self recurrsion
	if (strcmp(s, code_top->get_name())==0) {  // recurrsion
		return true;
	}

	// second, find it from using space
	char* cp = code_top->find_in_space(s);
	if (cp != NULL) return true;

	// now, find it from local variable set;
	return code_top->check_lvar(s);
}
/*}}}*/

void parserOP::push_lvar(const char* s)/*{{{*/
{ 
	// local should be faster than using space
	bool ret = code_top->check_lvar(s);
	if (ret == true) {
		short idx = code_top->find_lvar(s);
		code_top->push_char(OP_PUSH_LVAR);
		code_top->push_short(idx);
		return;
	}

	// second check if self recurrsion
	if (strcmp(s, code_top->get_name())==0) {  // recurrsion
		push_reserved(OP_PUSH_MY);
		return;
	}

	// last, find it from using space
	ret = push_mvar_using_space(s);

	// if not exists at all, make one
	if (ret == false) {
		short idx = code_top->find_lvar(s);
		code_top->push_char(OP_PUSH_LVAR);
		code_top->push_short(idx);
	}
}
/*}}}*/

bool parserOP::push_mvar_using_space(const char* s) /*{{{*/
{
	char* cp = code_top->find_in_space(s);

	if (cp == NULL)
		return false;

	push_reserved(OP_PUSH_ROOT);
	for(char* p = cp; *p != 0; p++) {
		if (*p == '.') {
			*p = 0;
			find_member(cp);
			*p = '.';
			cp = p+1;
		}
	}

	find_member(cp);

	return true;
}
/*}}}*/

void parserOP::push_mvar(const char* s) 
{
	code_top->push_char(OP_PUSH_MVAR);
	code_top->push_string(s);
}

void parserOP::push_ovar(const char* s) 
{
	code_top->push_char(OP_PUSH_OVAR);
	code_top->push_string(s);
}

void parserOP::push_cvar(const char* s) 
{
	code_top->push_char(OP_PUSH_CVAR);
	code_top->push_string(s);
}

void parserOP::find_member(const char* s) 
{
	code_top->push_char(OP_FIND_MEMBER);
	code_top->push_string(s);
}

void parserOP::clear_last_find_position()
{
	m_last_find = 0;
}

void parserOP::set_last_find_position()
{
	m_last_find = code_top->size();
}

void parserOP::fix_last_find_position()
{
	if (m_last_find && code_top->get_char(m_last_find) == OP_FIND_MEMBER) {
		code_top->set_char(OP_FIND_MEMBER_LAST, m_last_find);
	}
	clear_last_find_position();
}


void parserOP::find_reserved(int o) 
{
	code_top->push_char(OP_FIND_RESERVED);
	code_top->push_char(o);
}

void parserOP::push_reserved(int OP)	
{ 
	code_top->push_char(OP); 
}

void parserOP::push_nil() 
{
	code_top->push_char(OP_PUSH_NIL);
}

void parserOP::push_integer(int i) 
{
	code_top->push_char(OP_PUSH_INT);
	code_top->push_int(i);
}

void parserOP::push_bignum(char sign, const char* s)
{
	code_top->push_char(OP_PUSH_BIGNUM);
	code_top->push_char(sign);
	code_top->push_string(s);
}

void parserOP::push_real(double d) 
{
	code_top->push_char(OP_PUSH_REAL);
	code_top->push_double(d);
}

void parserOP::push_boolean(bool tf) 
{
	code_top->push_char(OP_PUSH_BOOLEAN);
	code_top->push_char(tf?1:0);
}

void parserOP::push_string(const char* s) 
{
	int len = strlen(s);

	if (len < CHAR_MAX) {
		code_top->push_char(OP_PUSH_STR);
		code_top->push_string(s);
	}
	else {
		code_top->push_char(OP_PUSH_LONG_STR);
		code_top->push_long_string(s);
	}
}

void parserOP::dump_stack()		
{
	code_top->push_char(OP_DUMP_STACK); 
}

void parserOP::dump_local()		
{
	code_top->push_char(OP_DUMP_LOCAL); 
}


