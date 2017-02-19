/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserControl.h - manage control statements of parser

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/


#ifndef _DEF_PARSER_CONTROL
#define _DEF_PARSER_CONTROL

#include "parserCode.h"

class parserControl 
{
public:
	parserControl() : m_once_id(0), m_in_once(false) { }

	// ABOUT control
	void if_start(bool flag=true);
	void if_end();
	void else_start();
	void else_end();

	void do_start();
	void do_end();

	void times_start();
	void times_end();

	void while_start_1();
	void while_start_2();
	void while_end();

	void for_start(const char* name);
	void for_start_sub(const char* name); // for sub for of para for
	void for_end();

	void do_return(int i);
	void do_continue();
	void do_break();

	void decode_start();
	void decode_func_start();
	void decode_end();
	void decode_pattern_start();
	void decode_pattern_shift();
	void decode_pattern_end();
	void decode_match_expr();
	void decode_shift(const char* name);
	void decode_match_and_assign(const char* name);
	void decode_cut_list(const char* head, const char* tail);

	void sbf_start();
	void sbf_end();
	void sbf_rule_start();
	void sbf_rule();
	void sbf_in();
	void sbf_list_gen(const char* name);
	void sbf_range_gen(const char* name);

	void parallel_start();
	void parallel_end();

	void parallel_for_start(const char* name);
	void parallel_for_end();

	bool is_once();
	void once_start();
	void once_end();

	void channel_in_start();
	void channel_in_end(int num);

	void channel_out_start();
	void channel_out_end(int num);

private:
	struct context {
		context() : start(0), end(0), pass2(0) { }

		int pass2;
		int start;					// start of control statement
		int end;					// end of control statement
		vector<int> list_cont;		
		vector<int> list_break;	
		vector<int> list_etc;	
	};

	vector<context> m_ctl;

	int m_once_id;
	bool m_in_once;
};

extern parserControl* g_ctl;

#endif

