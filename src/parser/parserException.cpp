/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserException.cpp - manage exception statements of parser

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "parserException.h"
#include "parserCode.h"
#include "parser_common.h"
#include "orca_opcode.h"

// Exception structure in code
// OP_MARK_TRY, address, num, ...catch_stmt* [finally_stmt]... , 
// [namelen, catch_name, varlen, (vars)*, addr]+ OP_DONE_TRY

void parserException::pop() 
{
	st_exc& ex = m_ex[m_ex.size() - 1];

	// mark to initial
	code_top->set_int(code_top->size(), ex.init_addr);
	code_top->set_int(ex.handler_num, ex.init_addr + sizeof(int));
	code_top->push_code(ex.init_code);

	// mark to end, if there is no finally stmt
	vector<int>::iterator vi = ex.finally_addr.begin();
	for(; vi != ex.finally_addr.end(); ++vi) {
		code_top->set_int(code_top->size(), *vi);
	}

	// mark to end
	code_top->set_int(code_top->size(), ex.end_addr);
	
	m_ex.pop_back();
	code_top->push_char(OP_DONE_TRY);
}

void parserException::push() 
{
	st_exc ex;

	code_top->push_char(OP_MARK_TRY);
	ex.init_addr = code_top->size();
	m_ex.push_back(ex);
	code_top->increase(sizeof(int));	// addr
	code_top->increase(sizeof(int));	// num
}

void parserException::goto_end() 
{
	// jmp to end
	st_exc& ex = m_ex[m_ex.size() - 1];

	code_top->push_char(OP_JMP);
	ex.end_addr = code_top->size();
	code_top->increase(sizeof(int));
}

void parserException::goto_finally() 
{
	// jmp to end
	st_exc& ex = m_ex[m_ex.size() - 1];

	code_top->push_char(OP_JMP);
	ex.finally_addr.push_back(code_top->size());
	code_top->increase(sizeof(int));
}

void parserException::do_finally()
{
	st_exc& ex = m_ex[m_ex.size() - 1];

	// mark to end, if there is no finally stmt
	vector<int>::iterator vi = ex.finally_addr.begin();
	for(; vi != ex.finally_addr.end(); ++vi) {
		code_top->set_int(code_top->size(), *vi);
	}

	ex.finally_addr.clear();
}

void parserException::catch_start(const char* s, vector<const char*>* vp) 
{
	st_exc& ex = m_ex[m_ex.size() - 1];

	if (s != NULL) {
		ex.init_code.push_back(strlen(s));
		copy(s, s+strlen(s)+1, back_inserter(ex.init_code));

		if (vp) {
			ex.init_code.push_back(vp->size());
			for(int i=0; i<vp->size(); i++) {
				int idx = code_top->find_lvar((*vp)[i]);
				ex.init_code.push_back(idx);
			}
		}
		else {
			ex.init_code.push_back(0);
		}
	}
	else { 
		ex.init_code.push_back(0);
	}

	char* b = i2l(code_top->size());
	copy(b, b+sizeof(int), back_inserter(ex.init_code));
	ex.handler_num++;
}

void parserException::do_throw(const char* s, int argc) 
{
	code_top->push_char(OP_THROW);
	code_top->push_char(argc);
	code_top->push_string(s);
}

