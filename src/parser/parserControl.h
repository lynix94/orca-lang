/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserControl.h - manage control statements of parser

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/


#ifndef _DEF_PARSER_CONTROL
#define _DEF_PARSER_CONTROL

#include "parserCode.h"


enum control_type_e
{
	CONTROL_NULL = 0,
	CONTROL_IF, 
	CONTROL_ELSE, 
	CONTROL_DO, 
	CONTROL_TIMES, 
	CONTROL_WHILE, 
	CONTROL_FOR, 
	CONTROL_FOR_2, 
	CONTROL_FOR_SUB, 
	CONTROL_DECODE, 
	CONTROL_SWITCH, 
	CONTROL_SBF, 
	CONTROL_PARALLEL, 
	CONTROL_PARALLEL_FOR, 
	CONTROL_CHANNEL_IN, 
	CONTROL_CHANNEL_OUT, 
};

class parserControl 
{
public:
	parserControl() {}

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
	void for_start_2(const char* key, const char* name);
	void for_start_sub(const char* name); // for sub for of para for
	void for_end();

	void do_return(int i);
	void do_continue();
	void do_break();
	void do_fallthrough();

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

	void switch_start();
	void switch_end();
	void switch_case_start();
	void switch_case_shift();
	void switch_case_end();

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

	void channel_in_start();
	void channel_in_end(int num);
	void channel_out_start();
	void channel_out_end(int num);

private:
	struct context {
		context(control_type_e t)
			: type(t), start(0), end(0), pass2(0) { }

		control_type_e type;

		int pass2;
		int start;					// start of control statement
		int end;					// end of control statement
		vector<int> list_cont;		
		vector<int> list_break;	
		vector<int> list_etc;	

	};

	vector<context> m_ctl;


private:
	bool is_breakable(context& ctx);
	bool is_continuable(context& ctx);
	bool is_for(context& ctx);
};



extern parserControl* g_ctl;

#endif

