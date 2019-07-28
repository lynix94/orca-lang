/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserCode.cpp - manage code stack of parser

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <boost/filesystem/path.hpp>
namespace fs = boost::filesystem;



#include "orca_opcode.h"
#include "parserCode.h"
#include "parserParser.h"
#include "parserOP.h"
#include "orcaVM.h"
#include "orcaObject.h"
#include "orcaRoot.h"

#pragma warning (disable : 4309)  // 0xf2 to push_char

map<string, string> parserCode::m_space;
vector<char> parserCode::m_def;
vector<parserCode*> parserCode::m_codeStack;

vector<char> parserCode::m_codeFinal;
vector<int> parserCode::m_debugFinal;
int parserCode::m_debug_lineno;

void parserCode::init() /*{{{*/ {
	m_def.clear();
	m_codeFinal.clear();
	m_debugFinal.clear();
	m_debug_lineno=0;
}
/*}}}*/

void parserCode::Final(string name) /*{{{*/
{
	string parent_path = fs::path(name).parent_path().string();
	string basename = fs::path(name).filename().string();

	int idx = basename.find_last_of(".");
	string oname;

	if (idx > 0) {
		oname = basename.substr(0, idx) + ".kw";
	}
	else {
		oname = basename  + ".kw";
	}

	if (parent_path.length() > 0) {
		oname= parent_path + "/" + oname;
	}

	FILE* fp = fopen(oname.c_str(), "wb+");
	if (fp == NULL) {
		printf("file open(or create) '%s' failed. check authority\n", oname.c_str());
		exit(0);
	}

	OrcaHeader hd(m_def.size(), m_codeFinal.size(), m_debugFinal.size()*sizeof(int));
	fseek(fp, sizeof(hd), SEEK_SET);
	fwrite(&m_def[0], 1, m_def.size(), fp);
	fwrite(&m_codeFinal[0], 1, m_codeFinal.size(), fp);


	//fwrite(&m_debugFinal[0], 1, m_debugFinal.size()*sizeof(int), fp);

	vector<string> line; 
	if (g_parser->curr_fp != NULL && g_parser->curr_fp != stdin) {
		fseek(g_parser->curr_fp, 0, SEEK_SET);

		char* cp;
		do {
			char buff[128];
			cp = fgets(buff, sizeof(buff), g_parser->curr_fp);
			line.push_back(buff);
		} while (cp != NULL);
	}

	for (int i=0; i<m_debugFinal.size(); i+=2) {
		fwrite(&m_debugFinal[i], 1, sizeof(int) * 2, fp);
		const char* cp = "(null)\n";
		if (line.size() > m_debugFinal[i+1]) {
			cp = line[m_debugFinal[i+1]-1].c_str();
		}

		fwrite(cp, 1, strlen(cp), fp);
	}
	
	fseek(fp, 0, SEEK_SET);
	fwrite(&hd, 1, sizeof(hd), fp);
	fclose(fp);
}
/*}}}*/

parserCode::parserCode(const char* module_name, vector<const char*>* param, /*{{{*/
				int flag_define, vector<const char*>* supers, const char* under_path )
{
	m_name = module_name;

	// write object name
	if (under_path) {
		m_def.push_back(OP_DEF_UNDER_START);
		m_flag_under = true;
	}
	else {
		m_def.push_back(OP_DEF_START);
		m_flag_under = false;
	}

	// flag
	m_def.push_back(flag_define);

	// name
	m_def.push_back(m_name.length()+1);
	copy(m_name.begin(), m_name.end(), back_inserter(m_def));
	m_def.push_back(0);

	// under
	if (under_path) {
		m_def.push_back(strlen(under_path) + 1);
		copy(under_path, under_path + strlen(under_path), back_inserter(m_def));
		m_def.push_back(0);
	}

	// param, make local variable index
	if (param) {
		vector<const char*>::iterator it = param->begin();
		for(; it!=param->end(); ++it) {
			const char *cp = *it;
			if (strncmp(cp, "...", 3) == 0) { // ...argv
				cp = cp + 3;
			}

			find_lvar(cp);
		}
	}

	// super
	if (supers) {
		for (int i=0; i<supers->size(); i++) {
			m_def.push_back(OP_DEF_SUPER);
			const char* cp = (*supers)[i];
			int len = strlen(cp);
			if (len > 254) {
				throw "parents name exceeds length";
			}

			m_def.push_back(len + 1);
			copy(cp, cp + len, back_inserter(m_def));
			m_def.push_back(0);
		}
	}

	// reserve code header
	m_code.resize(sizeof(CodeHeader));
	m_ch.frame_size=0;
	m_ch.argument_size=param ? param->size() : 0;

	// set default objects
	m_space["orca"] = "orca";
	m_space["io"] = "io";
	m_space["print"] = "io.print";
	m_space["os"] = "os";
	m_space["type"] = "type";
	m_space["sort"] = "sort";
	m_space["string"] = "string";
	m_space["repr"] = "repr";
	m_space["range"] = "range";
	m_space["selector"] = "selector";
}
/*}}}*/

parserCode::parserCode(const char* ctx_type, const char* ctx_code, /*{{{*/
				const char* module_name, vector<const char*>* param,
				int flag_define, vector<const char*>* supers, const char* under_path,
				map<string, int>& pos_map)
{
	m_name = module_name;

	// write object name
	if (under_path) {
		m_def.push_back(OP_DEF_CONTEXT_UNDER_START);
		m_flag_under = true;
	}
	else {
		m_def.push_back(OP_DEF_CONTEXT_START);
		m_flag_under = false;
	}

	// type
	int len = strlen(ctx_type) + 1;
	if (len > 255) len = 255;
	m_def.push_back(len);
	copy(ctx_type, ctx_type+len, back_inserter(m_def));

	// flag
	m_def.push_back(flag_define);

	// name
	len = strlen(module_name) + 1;
	if (len > 255) len = 255;
	m_def.push_back(len);
	copy(module_name, module_name+len, back_inserter(m_def));

	// under
	if (under_path) {
		m_def.push_back(strlen(under_path) + 1);
		copy(under_path, under_path + strlen(under_path), back_inserter(m_def));
		m_def.push_back(0);
	}

	// code
	len = strlen(ctx_code)+1;
	char* cp = i2l(len);
	copy(cp, cp+sizeof(int), back_inserter(m_def));
	copy(ctx_code, ctx_code + len, back_inserter(m_def));

	// param
	if (param) {
		int param_n = param->size();
		if (param_n > 255) {
			throw "parameter count exceeds 255";
		}

		m_def.push_back(param_n);
		for (int i=0; i<param_n; i++) {
			const char* cp = (*param)[i];
			int len = strlen(cp) + 1;
			if (len > 255) len = 255;
			m_def.push_back(len);
			copy(cp, cp+len, back_inserter(m_def));
		}
	}
	else {
		m_def.push_back(0);
	}

	// pos
	m_def.push_back(pos_map.size());
	map<string, int>::iterator it;
	for (it = pos_map.begin(); it != pos_map.end(); ++it) {
		const char* cp = it->first.c_str();
		int len = strlen(cp);
		if (len > 254) {
			throw "name exceeds length";
		}

		m_def.push_back(len + 1);
		copy(cp, cp + len, back_inserter(m_def));
		m_def.push_back(0);
		cp = (char*)&it->second;
		copy(cp, cp+sizeof(int), back_inserter(m_def));
	}

	// super
	if (supers) {
		for (int i=0; i<supers->size(); i++) {
			m_def.push_back(OP_DEF_SUPER);
			const char* cp = (*supers)[i];
			int len = strlen(cp);
			if (len > 254) {
				throw "parents name exceeds length";
			}

			m_def.push_back(len + 1);
			copy(cp, cp + len, back_inserter(m_def));
			m_def.push_back(0);
		}
	}

}
/*}}}*/

void parserCode::pop_and_process_code(bool interpret_or_eval)/*{{{*/
{
	if (m_code.empty()) { // in case of context
		return;
	}

	// set code header
	m_ch.frame_size = htols(m_lvar.size());
	m_ch.argument_size = htols(m_ch.argument_size);

	if (interpret_or_eval) {
		m_def.push_back(OP_DEF_CODE);

		// create code block
		m_code.push_back(OP_RETURN_NIL);
		char* new_code = new char[m_code.size()];
		char* b = ll2l((long long)new_code);

		copy(b, b+sizeof(long long), back_inserter(m_def));
		// set header
		copy((char*)&m_ch, (char*)&m_ch+sizeof(CodeHeader), m_code.begin());

		// real code copy & return
		copy(m_code.begin(), m_code.end(), new_code);
	}
	else {
		m_def.push_back(OP_DEF_CODE);

		// code size & code
		char* b = ll2l(m_codeFinal.size());
		copy(b, b+sizeof(long long), back_inserter(m_def));

		// set header
		copy((char*)&m_ch, (char*)&m_ch+sizeof(CodeHeader), back_inserter(m_codeFinal));

		// set debug info
		map<int, int>::iterator mi = m_debug.begin();
		for(; mi != m_debug.end(); ++mi) {
			m_debugFinal.push_back(mi->first+m_codeFinal.size());
			m_debugFinal.push_back(mi->second);
		}

		// real code copy & return
		copy(m_code.begin() + sizeof(CodeHeader), m_code.end(), back_inserter(m_codeFinal));
		m_codeFinal.push_back(OP_RETURN_NIL);
	}
}
/*}}}*/

void parserCode::pop_and_process_init(bool interpret_or_eval)/*{{{*/
{
	if (m_init.empty()) {
		return;
	}

	if (interpret_or_eval) {
		m_def.push_back(OP_DEF_INIT);

		// create code block
		m_init.push_back(OP_RETURN_NIL);
		char* new_code = new char[m_init.size()];
		char* b = ll2l((long long)new_code);

		copy(b, b+sizeof(long long), back_inserter(m_def));

		// real code copy & return
		copy(m_init.begin(), m_init.end(), new_code);
	}
	else { // parse
		m_def.push_back(OP_DEF_INIT);

		// code size & code
		char* b = ll2l(m_codeFinal.size());
		copy(b, b+sizeof(long long), back_inserter(m_def));

		// set debug info
		map<int, int>::iterator mi = m_debug.begin();
		for(; mi != m_debug.end(); ++mi) {
			m_debugFinal.push_back(mi->first+m_codeFinal.size());
			m_debugFinal.push_back(mi->second);
		}

		// real code copy & return
		copy(m_init.begin(), m_init.end(), back_inserter(m_codeFinal));
		m_codeFinal.push_back(OP_RETURN_NIL);
	}
}
/*}}}*/

parserCode::~parserCode() /*{{{*/
{
	pop_and_process_code(g_parser->is_interactive() || g_parser->is_eval());
	pop_and_process_init(g_parser->is_interactive() || g_parser->is_eval());

	if (m_flag_under) {
		m_def.push_back(OP_DEF_UNDER_END);
	}
	else {
		m_def.push_back(OP_DEF_END);
	}
}
/*}}}*/

void parserCode::using_object(const char* s) /*{{{*/
{
	m_def.push_back(OP_USING);
	m_def.push_back(strlen(s)+1);
	copy(s, s+strlen(s)+1, back_inserter(m_def));

	string path = s;
	string basename = s;
	int idx = path.find_last_of("/");
	if (idx > 0) {
		basename = path.substr(idx+1);
	}

	idx = basename.find_last_of(".");
	if (idx > 0) {
		m_space[basename.substr(idx+1)] = basename;
	}
	else {
		m_space[basename] = basename;
	}
}
/*}}}*/

char* parserCode::find_in_space(const char* s) /*{{{*/
{
	map<string, string>::iterator it = m_space.find(s);
	if (it == m_space.end()) {
		return NULL;
	}

	return (char*)it->second.c_str();
}
/*}}}*/

void parserCode::reg_object(const char* s, int flag_define) /*{{{*/
{
	m_def.push_back(OP_REG);
	m_def.push_back(flag_define);

	m_def.push_back(strlen(s)+1);
	copy(s, s+strlen(s)+1, back_inserter(m_def));
}
/*}}}*/

void parserCode::init_object_start(const char* s) /*{{{*/
{
	m_init_begin = code_top->size();
}
/*}}}*/

void parserCode::init_object_done() /*{{{*/
{
	copy(m_code.begin() + m_init_begin, m_code.end(), back_inserter(m_init));
	m_code.resize(m_init_begin);
}
/*}}}*/

int parserCode::find_lvar(const char* s) /*{{{*/
{
	if (m_lvar.find(s)==m_lvar.end()) {
		short size = m_lvar.size();
		m_lvar[s] = size;
	}

	return m_lvar[s];
}
/*}}}*/

bool parserCode::check_lvar(const char* s) /*{{{*/
{
	if (m_lvar.find(s)==m_lvar.end()) {
		return false;
	}

	return true;
}
/*}}}*/

void parserCode::push_char(char val)/*{{{*/
{
	m_code.push_back(val);

	if (m_debug_lineno < g_parser->lineno) {
		m_debug_lineno = g_parser->lineno;
		m_debug[m_code.size()] = m_debug_lineno;
	}
}
/*}}}*/

void parserCode::push_short(short val)/*{{{*/
{
	char* b = s2l(val);
	copy(b, b+sizeof(short), back_inserter(m_code));
}
/*}}}*/

void parserCode::push_int(int val) /*{{{*/
{
	char* b = i2l(val);
	copy(b, b+sizeof(int), back_inserter(m_code));
}
/*}}}*/

void parserCode::push_double(double val) /*{{{*/
{
	char* b = (char*)&val;
	copy(b, b+sizeof(double), back_inserter(m_code));
}
/*}}}*/

void parserCode::push_raw_string(const char* val)/*{{{*/
{
	copy(val, val+strlen(val)+1, back_inserter(m_code));
}
/*}}}*/

void parserCode::push_string(const char* val)/*{{{*/
{
	if (strlen(val) >= CHAR_MAX) {
		throw "too long name";
	}

	push_char(strlen(val)+1);
	copy(val, val+strlen(val)+1, back_inserter(m_code));
}
/*}}}*/

void parserCode::push_string(string& val)/*{{{*/
{
	if (val.length() >= CHAR_MAX) {
		throw "too long name";
	}

	push_char(val.length()+1);
	copy(val.begin(), val.end()+1, back_inserter(m_code));
}
/*}}}*/

void parserCode::push_long_string(const char* val)/*{{{*/
{
	push_int(strlen(val)+1);
	copy(val, val+strlen(val)+1, back_inserter(m_code));
}
/*}}}*/

void parserCode::push_long_string(string& val)/*{{{*/
{
	push_int(val.length()+1);
	copy(val.begin(), val.end()+1, back_inserter(m_code));
}
/*}}}*/

void parserCode::set_int(int val, int offset)/*{{{*/
{
	char* b = i2l(val);
	copy(b, b+sizeof(int), &m_code[offset]);
}
/*}}}*/

void parserCode::set_char(char val, int offset)/*{{{*/
{
	m_code[offset] = val;
}
/*}}}*/

char parserCode::get_char(int offset)/*{{{*/
{
	return m_code[offset];
}
/*}}}*/

void parserCode::push_code(vector<char>& code) /*{{{*/
{
	copy(code.begin(), code.end(), back_inserter(m_code));
}
/*}}}*/

void parserCode::increase(int size) /*{{{*/
{
	m_code.resize(m_code.size() + size);
}
/*}}}*/

int parserCode::size()/*{{{*/
{
	return m_code.size();
}
/*}}}*/

void parserCode::clear()/*{{{*/
{
	return m_code.clear();
}
/*}}}*/

void parserCode::reinit_code_stack_for_interpreter()/*{{{*/
{
	while (parserCode::m_codeStack.size() > 1) {
		pop_code_stack();
	}
}
/*}}}*/

void parserCode::push_code_stack(const char* name, vector<const char*>* param, int flag_define,/*{{{*/
								vector<const char*>* super_class, const char* under_path)
{
	parserCode* c = new parserCode(name, param, flag_define, super_class, under_path);
	parserCode::m_codeStack.push_back(c);
}
/*}}}*/

void parserCode::push_context_stack(const char* type, const char* code,/*{{{*/
								const char* name, vector<const char*>* param, int flag_define,
								vector<const char*>* super_class, const char* under_path,
								map<string, int>& pos_map)
{
	parserCode* c = new parserCode(type, code, name, param, flag_define, super_class, under_path, pos_map);
	parserCode::m_codeStack.push_back(c);
}
/*}}}*/

void parserCode::pop_code_stack()/*{{{*/
{
	delete m_codeStack[parserCode::m_codeStack.size() - 1];
	parserCode::m_codeStack.pop_back();
}
/*}}}*/

vector<char>& parserCode::get_def()/*{{{*/
{
	return m_def;
}
/*}}}*/

parserCode* parserCode::active()/*{{{*/
{
	return m_codeStack[m_codeStack.size()-1];
}
/*}}}*/

void parserCode::dump_final() /*{{{*/
{
	printf("define dump: \n");
	for(int i=0; i<m_def.size(); i++) {
		printf("%02x ", (unsigned char)m_def[i]);
		if (((i+1)%16)==0) printf("\n");
	}

	printf("\n");

	printf("code dump: \n");
	for(int i=0; i<m_codeFinal.size(); i++) {
		printf("%02x ", (unsigned char)m_codeFinal[i]);
		if (((i+1)%16)==0) printf("\n");
	}

	printf("\n");
}
/*}}}*/

void parserCode::dump() /*{{{*/
{
	printf("define dump: \n");
	for(int i=0; i<m_def.size(); i++) {
		printf("%02x ", (unsigned char)m_def[i]);
		if (((i+1)%16)==0) printf("\n");
	}

	printf("\n");

	printf("code dump: \n");
	for(int i=0; i<m_code.size(); i++) {
		printf("%02x ", (unsigned char)m_code[i]);
		if (((i+1)%16)==0) printf("\n");
	}

	printf("\n");
}
/*}}}*/

void parserCode::interpret(orcaVM* vm)/*{{{*/
{
	if (m_def.size()) {
		pop_and_process_init(true);
		
		char* new_def = new char[m_def.size()];
		copy(m_def.begin(), m_def.end(), new_def);
		
		vm->exec_define(new_def, m_def.size(), NULL, NULL, 0, "");
	}

	vm->exec_code(&m_code[0]);
}
/*}}}*/

void parserCode::eval(orcaVM* vm)/*{{{*/
{
	if (m_def.size()) {
		pop_and_process_init(true);
		
		char* new_def = new char[m_def.size()];
		copy(m_def.begin(), m_def.end(), new_def);
		
		vm->exec_define(new_def, m_def.size(), NULL, vm->m_curr, 0, "");
	}

	vm->exec_code(&m_code[0]);
}
/*}}}*/

orcaObject* parserCode::compile(orcaVM* vm)/*{{{*/
{
	// TODO: check name (parameter add) & remove if exists
	pop_code_stack();
	char* new_def = new char[m_def.size()];
	copy(m_def.begin(), m_def.end(), new_def);


	orcaObject* compiled = g_root->get_member("compiled").Object();
	orcaObject* op = vm->exec_define(new_def, m_def.size(), NULL, compiled, 0, "");
	return op;
}
/*}}}*/

void parserCode::init_current() /*{{{*/
{
	m_def.clear();
	m_init.clear();
	m_code.resize(sizeof(CodeHeader));
}
/*}}}*/

void parserCode::set_argv_on()/*{{{*/
{
	m_ch.flag_argv=1;
}
/*}}}*/

const char* parserCode::get_name()/*{{{*/
{
	return m_name.c_str();
}
/*}}}*/

void parserCode::pop_back()/*{{{*/
{
	m_code.pop_back();
}
/*}}}*/


