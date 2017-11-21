/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserCode.h - manage code stack of parser

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_PARSER_CODE
#define _DEF_PARSER_CODE

#include <vector>
#include <string>
#include <map>
#include <string.h>

#include "orca_common.h"

class orcaVM;


using namespace std;

class parserCode 
{
public:
	parserCode(const char* s, vector<const char*>* param, int flag = 0,
			vector<const char*>* supers = NULL, const char* under_path = NULL);
	parserCode(const char* type, const char* code,
			const char* s, vector<const char*>* param, int flag = 0,
			vector<const char*>* supers = NULL, const char* under_path = NULL);
	~parserCode();

	static void init();

	void using_object(const char* s, const char* by = NULL);
	char* find_in_space(const char* s);

	void reg_object(const char* s, int flag = 0);

	void init_object_start(const char* s);
	void init_object_done();
	static void Final(string name);

	int find_lvar(const char* s);
	bool check_lvar(const char* s);
	static void dump_final();
	void dump();

	// interface
	static parserCode* active();
	void push_char(char val);
	void push_short(short val);
	void push_int(int val);
	void push_double(double val);
	void push_raw_string(const char* val);
	void push_string(const char* val);
	void push_string(string& val);
	void push_code(vector<char>& code);
	void set_int(int val, int offset);
	void set_char(char val, int offset);
	char get_char(int offset);
	void increase(int size);
	int size();
	void pop_back();

	static void push_code_stack(const char* name, vector<const char*>* param,
							int flag = 0, vector<const char*>* super_class = NULL,
							const char* under_path = NULL);

	static void push_context_stack(const char* type, const char* code,
							const char* name, vector<const char*>* param,
							int flag = 0, vector<const char*>* super_class = NULL,
							const char* under_path = NULL);

	// just case for exception in interpreter
	static void reinit_code_stack_for_interpreter();
	static void pop_code_stack();
	static vector<char>& get_def();

	// for interpreter
	void interpret(orcaVM* vm);
	void eval(orcaVM* vm);
	void init_current();

	void set_argv_on();
	const char* get_name();

private:
	void pop_and_process_code(bool interpret_or_eval = false);
	void pop_and_process_init(bool interpret_or_eval = false);

private:
	map<string, short> m_lvar;

	static map<string, string> m_space;	// search space
	static vector<char> m_codeFinal;
	static vector<char> m_def;
	static vector<parserCode*> m_codeStack;

	CodeHeader m_ch;
	vector<char> m_code;

	int m_init_begin; 
	vector<char> m_init;
	bool m_flag_under;

public:
	string m_name;

	// debug info
	static vector<int> m_debugFinal;
	map<int, int> m_debug;
	static int m_debug_lineno;
};



#define code_top parserCode::active()

#endif

