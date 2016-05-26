/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaException.h - manage exception statements of parser

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_PARSER_EXCEPTION
#define _DEF_PARSER_EXCEPTION

#include <cstddef>
#include <vector>

using namespace std;

class parserException 
{
public:
	void pop();
	void push(); 
	void goto_end();
	void goto_finally();
	void do_finally();
	void catch_start(const char* name, vector<const char*>* vp = NULL);
	void do_throw(const char* s, int argc);

private:
	struct st_exc 
	{
		st_exc() : handler_num(0) { }
		int init_addr;
		int handler_num;
		vector<char> init_code;
		int end_addr;
		vector<int> finally_addr;
	};

	std::vector<st_exc> m_ex;
};

#endif

