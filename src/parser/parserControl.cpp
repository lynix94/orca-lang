/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserControl.cpp - manage control statements of parser

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <stdio.h>

#include "parserControl.h"
#include "orca_opcode.h"
#include "parserOP.h"

#pragma warning (disable : 4309)  // 0xf2 to push_char

#define MARK_PARALLEL_FOR 1000000000

void yyerror(const char* msg);

parserControl s_ctl;
parserControl* g_ctl = &s_ctl;

void parserControl::if_start(bool flag)	
{ 
	if (flag) 
		code_top->push_char(OP_JMP_FALSE);
	else
		code_top->push_char(OP_JMP_TRUE);

	context ctx;
	ctx.pass2 = code_top->size();
	m_ctl.push_back(ctx);
	
	code_top->increase(sizeof(int));
}


void parserControl::if_end() 
{
	int pos_if_false = m_ctl[m_ctl.size()-1].pass2;
	m_ctl.pop_back();
	code_top->set_int(code_top->size(), pos_if_false);
}


void parserControl::else_start() 
{
	int pos_if_false = m_ctl[m_ctl.size()-1].pass2;
	m_ctl.pop_back();

	code_top->push_char(OP_JMP);

	context ctx;
	ctx.pass2 = code_top->size();
	m_ctl.push_back(ctx);

	code_top->increase(sizeof(int));
	code_top->set_int(code_top->size(), pos_if_false); 
}


void parserControl::else_end() 
{
	int pos_end = m_ctl[m_ctl.size()-1].pass2;
	m_ctl.pop_back();
	code_top->set_int(code_top->size(), pos_end); 
}


void parserControl::do_start() 
{
	context ctx;
	ctx.start = code_top->size();
	m_ctl.push_back(ctx);
}


void parserControl::do_end() 
{
	context& ctx = m_ctl[m_ctl.size()-1];
	int pos_cont = ctx.start;

	code_top->push_char(OP_JMP_TRUE);
	code_top->push_int(pos_cont);

	if (!ctx.list_break.empty()) {
		vector<int>::iterator vi = ctx.list_break.begin();

		for(;vi != ctx.list_break.end(); ++vi) {
			code_top->set_int(code_top->size(), *vi);
		}
	}

	m_ctl.pop_back();
}


void parserControl::times_start() 
{
	code_top->push_char(OP_MARK_STACK);

	context ctx;
	ctx.start = code_top->size();
	m_ctl.push_back(ctx);
}


void parserControl::times_end() 
{
	context& ctx = m_ctl[m_ctl.size()-1];
	int pos_cont = ctx.start;

	code_top->push_char(OP_PUSH_INT);
	code_top->push_int(1);
	code_top->push_char(OP_SUB);
	code_top->push_char(OP_DUP);
	code_top->push_char(OP_PUSH_INT);
	code_top->push_int(0);
	code_top->push_char(OP_GT);
	code_top->push_char(OP_JMP_TRUE);
	code_top->push_int(pos_cont);

	if (!ctx.list_break.empty()) {
		vector<int>::iterator vi = ctx.list_break.begin();

		for(;vi != ctx.list_break.end(); ++vi) {
			code_top->set_int(code_top->size(), *vi);
		}
	}

	code_top->push_char(OP_MARK_STACK_POP);

	m_ctl.pop_back();
}


void parserControl::while_start_1() 
{
	context ctx;
	ctx.start = code_top->size();
	m_ctl.push_back(ctx);
}


void parserControl::while_start_2() 
{
	code_top->push_char(OP_JMP_FALSE);
	m_ctl[m_ctl.size()-1].pass2 = code_top->size();
	code_top->increase(sizeof(int));
}


void parserControl::while_end() 
{
	context& ctx = m_ctl[m_ctl.size()-1];
	int pass2 = ctx.pass2;
	int pos_start = ctx.start;

	code_top->push_char(OP_JMP);
	code_top->push_int(pos_start);
	code_top->set_int(code_top->size(), pass2);

	if (!ctx.list_break.empty()) {
		vector<int>::iterator vi = ctx.list_break.begin();

		for (; vi!= ctx.list_break.end(); ++vi) {
			code_top->set_int(code_top->size(), *vi);
		}
	}

	m_ctl.pop_back();
}


void parserControl::for_start(const char* name) 
{
	int idx = code_top->find_lvar(name);
	code_top->push_char(OP_FOR);
	code_top->push_short(idx);
	
	context ctx;
	ctx.start = code_top->size();
	ctx.start *= -1; // mark for for_stmt
	ctx.list_break.push_back(code_top->size());
	m_ctl.push_back(ctx);

	code_top->increase(sizeof(int));
}

void parserControl::for_start_2(const char* name1, const char* name2) 
{
	int idx1 = code_top->find_lvar(name1);
	int idx2 = code_top->find_lvar(name2);
	code_top->push_char(OP_FOR_2);
	code_top->push_short(idx1);
	code_top->push_short(idx2);
	
	context ctx;
	ctx.start = code_top->size();
	ctx.start *= -1; // mark for for_stmt
	ctx.list_break.push_back(code_top->size());
	m_ctl.push_back(ctx);

	code_top->increase(sizeof(int));
}

void parserControl::for_start_sub(const char* name) 
{
	int idx = code_top->find_lvar(name);
	code_top->push_char(OP_FOR_SUB);
	code_top->push_short(idx);
	
	context ctx;
	ctx.start = code_top->size();
	ctx.start *= -1; // mark for for_stmt
	ctx.list_break.push_back(code_top->size());
	m_ctl.push_back(ctx);

	code_top->increase(sizeof(int));
}

void parserControl::for_end() 
{
	code_top->push_char(OP_FOR_END);

	context& ctx = m_ctl[m_ctl.size()-1];

	if (!ctx.list_break.empty()) {
		vector<int>::iterator vi = ctx.list_break.begin();

		for (; vi != ctx.list_break.end(); ++vi) {
			code_top->set_int(code_top->size(), *vi);
		}
	}

	m_ctl.pop_back();
}


void parserControl::decode_start()
{
	code_top->push_char(OP_DECODE);

	context ctx;
	m_ctl.push_back(ctx);
}

void parserControl::decode_func_start()
{
	code_top->push_char(OP_PUSH_LVAR);
	code_top->push_short(0);

	code_top->push_char(OP_DECODE);

	context ctx;
	m_ctl.push_back(ctx);
}


void parserControl::decode_end()
{
	context& ctx = m_ctl[m_ctl.size()-1];

	if (!ctx.list_break.empty()) {
		vector<int>::iterator vi = ctx.list_break.begin();
		for (; vi != ctx.list_break.end(); ++vi) {
			code_top->set_int(code_top->size(), *vi);
		}

		ctx.list_break.clear();
	}

	// fix last pattern address
	if (!ctx.list_cont.empty()) {
		vector<int>::iterator vi = ctx.list_cont.begin();
		for (; vi != ctx.list_cont.end(); ++vi) {
			code_top->set_int(code_top->size(), *vi);
		}

		ctx.list_cont.clear();
	}

	m_ctl.pop_back();
	code_top->push_char(OP_DECODE_END);
}

static bool g_flag_pattern_shifted = false;
static int g_shift_idx = 0;

void parserControl::decode_pattern_start()
{
	g_flag_pattern_shifted = false;

	// fix previous pattern address
	context& ctx = m_ctl[m_ctl.size()-1];
	if (!ctx.list_cont.empty()) {
		vector<int>::iterator vi = ctx.list_cont.begin();
		for (; vi != ctx.list_cont.end(); ++vi) {
			code_top->set_int(code_top->size(), *vi);
		}

		ctx.list_cont.clear();
	}

	code_top->push_char(OP_PATTERN_START);
	// continues are used for go to next pattern start
	ctx.list_cont.push_back(code_top->size());
	code_top->increase(sizeof(int));
}

void parserControl::decode_pattern_shift()
{
	if (g_flag_pattern_shifted) {
		if (g_shift_idx < 0) { // cut list case
			return;
		}

		code_top->push_char(OP_SHIFT_ALL); 
		code_top->push_short(g_shift_idx);
	}
	else {
		code_top->push_char(OP_DECODE_CHECK_REMAIN); 
	}
}

void parserControl::decode_pattern_end()
{
	context& ctx = m_ctl[m_ctl.size()-1];

	// breaks are used for go to end
	code_top->push_char(OP_JMP);
	ctx.list_break.push_back(code_top->size());
	code_top->increase(sizeof(int));
}

void parserControl::decode_match_expr()
{
	if (g_flag_pattern_shifted) {
		if (g_shift_idx < 0) { // cut list case
			return;
		}

		code_top->push_char(OP_MATCH_EXPR_W_SHIFT);
		code_top->push_short(g_shift_idx);
		g_flag_pattern_shifted = false;
	}
	else {
		code_top->push_char(OP_MATCH_EXPR);
	}
}

void parserControl::decode_match_and_assign(const char* name)
{
	if (g_flag_pattern_shifted) {
		if (g_shift_idx < 0) { // cut list case
			return;
		}

		code_top->push_char(OP_MATCH_N_ASSIGN_W_SHIFT);
		code_top->push_short(g_shift_idx);
		g_flag_pattern_shifted = false;
	}
	else {
		code_top->push_char(OP_MATCH_N_ASSIGN);
	}

	int idx = code_top->find_lvar(name);
	code_top->push_short(idx);
}

void parserControl::decode_shift(const char* name)
{
	if (g_flag_pattern_shifted) {
		// error
	}

	g_flag_pattern_shifted = true;
	g_shift_idx = code_top->find_lvar(name);
}

void parserControl::decode_cut_list(const char* head_name, const char* tail_name)
{
	int head = code_top->find_lvar(head_name);
	int tail = code_top->find_lvar(tail_name);

	code_top->push_char(OP_CUT_LIST);
	code_top->push_short(head);
	code_top->push_short(tail);

	g_flag_pattern_shifted = true;
	g_shift_idx = -1;
}

void parserControl::do_return(int i) 
{
	if (i == 0) {
		code_top->push_char(OP_RETURN_NIL);
		return;	
	}
	else if (i > 1) {
		g_op->make_list(i);
	}
	else if (i == 1) {

	}

	code_top->push_char(OP_RETURN);
}

void parserControl::do_continue() 
{
	int idx;
	for (idx = m_ctl.size()-1; idx >= 0; idx--) {
		if (m_ctl[idx].start != 0)
			break;
	}
	if (idx < 0) {
		printf("abnormal continue");
		return;
	}

	int offset = m_ctl[idx].start;

	if (offset == MARK_PARALLEL_FOR) { // para for
		code_top->push_char(OP_PARALLEL_END);

		// break when for items are empty
		code_top->push_char(OP_JMP);
		m_ctl[idx].list_break.push_back(code_top->size());
		code_top->increase(sizeof(int));
	}
	else if (offset > 0) {
		code_top->push_char(OP_JMP);
		code_top->push_int(offset);
	}
	else {  // for
		code_top->push_char(OP_FOR_END);

		// break when for items are empty
		code_top->push_char(OP_JMP);
		m_ctl[idx].list_break.push_back(code_top->size());
		code_top->increase(sizeof(int));
	}

}

void parserControl::do_break()
{
	int idx;
	for (idx = m_ctl.size()-1; idx >= 0; idx--) {
		if (m_ctl[idx].start != 0)
			break;
	}
	if (idx < 0) {
		printf("abnormal break");
		return;
	}

	if (m_ctl[idx].start == MARK_PARALLEL_FOR) { // para for
		code_top->push_char(OP_PARALLEL_END);
	}
	else {
		if (m_ctl[idx].start < 0) { // remove for stack
			code_top->push_char(OP_FOR_POP);
		}

		code_top->push_char(OP_JMP);
		m_ctl[idx].list_break.push_back(code_top->size());
		code_top->increase(sizeof(int));
	}
}


void parserControl::sbf_start()
{
	context ctx;

	code_top->push_char(OP_JMP);
	ctx.start = code_top->size();
	code_top->increase(sizeof(int));
	ctx.end = code_top->size();

	m_ctl.push_back(ctx);
}

void parserControl::sbf_end() 
{
	// fix start jmp
	context& ctx = m_ctl[m_ctl.size()-1];
	int start = ctx.start;
	code_top->set_int(code_top->size(), start);

	code_top->push_char(OP_SBF);

	code_top->push_int(ctx.end);
	code_top->push_int(ctx.list_break.size());
	code_top->push_int(ctx.list_cont.size());

	// sbf in
	for (int i=0; i<ctx.list_break.size(); i++) {
		code_top->push_int(ctx.list_break[i]);
	}

	// sbf rule
	for (int i=0; i<ctx.list_cont.size(); i++) {
		code_top->push_int(ctx.list_cont[i]);
	}

	m_ctl.pop_back();
}


void parserControl::sbf_rule_start() // result end
{
	// return of result code
	code_top->push_char(OP_RETURN);

	context& ctx = m_ctl[m_ctl.size()-1];
	ctx.pass2 = code_top->size();
}

void parserControl::sbf_rule() 
{
	context& ctx = m_ctl[m_ctl.size()-1];
	ctx.list_cont.push_back(ctx.pass2);
	code_top->push_char(OP_RETURN);

	ctx.pass2 = code_top->size();
}

void parserControl::sbf_in() 
{
	context& ctx = m_ctl[m_ctl.size()-1];
	ctx.list_break.push_back(ctx.pass2);
	code_top->push_char(OP_RETURN);

	ctx.pass2 = code_top->size();
}

void parserControl::sbf_list_gen(const char* name) 
{
	g_op->push_integer(code_top->find_lvar(name));
	g_op->push_integer(2);
}


void parserControl::sbf_range_gen(const char* name) 
{
	g_op->push_integer(code_top->find_lvar(name));
	g_op->push_integer(1);
}


void parserControl::parallel_start()
{
	context ctx;

	code_top->push_char(OP_PARALLEL_START);
	ctx.pass2 = code_top->size();
	m_ctl.push_back(ctx);
	code_top->increase(sizeof(int));
}
 
void parserControl::parallel_end()
{
	code_top->push_char(OP_PARALLEL_END);

	context& ctx = m_ctl[m_ctl.size()-1];
	int pos_pass2 = ctx.pass2;
	m_ctl.pop_back();

	code_top->set_int(code_top->size(), pos_pass2);
}

void parserControl::parallel_for_start(const char* name)
{
	int idx = code_top->find_lvar(name);
	code_top->push_char(OP_PARALLEL_FOR);
	code_top->push_short(idx);

	context ctx;
	ctx.start = MARK_PARALLEL_FOR;
	ctx.pass2 = code_top->size();
	m_ctl.push_back(ctx);
	code_top->increase(sizeof(int));

	for_start_sub(name);
}
 
void parserControl::parallel_for_end()
{
	for_end();

	code_top->push_char(OP_PARALLEL_END);

	context& ctx = m_ctl[m_ctl.size()-1];

	if (!ctx.list_break.empty()) {
		vector<int>::iterator vi = ctx.list_break.begin();

#if 0
		// for sub thread break.
		for (; vi != ctx.list_break.end(); ++vi) {
			code_top->set_int(code_top->size(), *vi);
		}
#endif
	}

	// for main thread which run to here
	int pos_pass2 = ctx.pass2;
	code_top->set_int(code_top->size(), pos_pass2);

	m_ctl.pop_back();
}


void parserControl::channel_in_start()
{
	code_top->push_char(OP_CHANNEL_IN);

	context ctx;
	ctx.pass2 = code_top->size();
	m_ctl.push_back(ctx);
	
	code_top->increase(sizeof(int));
}
 
void parserControl::channel_in_end(int num)
{
	// call if check ok
	g_op->call(num);

	// 2pass set
	int pos_if_false = m_ctl[m_ctl.size()-1].pass2;
	m_ctl.pop_back();
	code_top->set_int(code_top->size(), pos_if_false);
}
 
void parserControl::channel_out_start()
{
	code_top->push_char(OP_CHANNEL_OUT);

	context ctx;
	ctx.pass2 = code_top->size();
	m_ctl.push_back(ctx);
	
	code_top->increase(sizeof(int) * 2); // jump address, out num
}
 
void parserControl::channel_out_end(int num)
{
	int pos_if_false = m_ctl[m_ctl.size()-1].pass2;
	m_ctl.pop_back();
	code_top->set_int(code_top->size(), pos_if_false);
	code_top->set_int(num, pos_if_false + sizeof(int));
}
 

