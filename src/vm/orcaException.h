/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaException.h - handling exception & catch

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_EXCEPTION
#define _DEF_ORCA_EXCEPTION

#include "orca_opcode.h"
#include "orcaVM.h"
#include "orcaStack.h"
#include "orcaTrace.h"

class orcaException
{
public:
	orcaException(orcaVM* vm, const char* id, string msg = "") : m_id(id) { 
		if (vm == NULL) vm = get_current_vm();
		m_vm = vm;

		if (msg != "") {
			m_msg = msg;
		}

		make_trace();
		m_vm->m_last_trace_info = m_stack_trace;
	}

	orcaException(orcaVM* vm, const char* id, int argc) : m_id(id) { 
		if (vm == NULL) vm = get_current_vm();
		m_vm = vm;

		for (int i=0; i<argc; i++) {
			orcaData d = vm->m_stack->pop();
			d.rc_inc();
			params.push_front(d);
		}

		make_trace();
		m_vm->m_last_trace_info = m_stack_trace;
	}

	~orcaException() { }

	void clear()
	{
		for (int i=0; i<params.size(); i++) {
			params[i].rc_dec();
		}
	}

	void make_trace() {
		if (m_vm->m_trace->top_name == NULL) {
			m_vm->m_trace->top_name = m_vm->m_module->get_name();
		}

		if (m_vm->m_cptr == NULL) {
			return; // not executed yet
		}

		m_vm->m_trace->push(m_vm->m_trace->top_name, *m_vm->m_cptr);
		m_stack_trace = m_vm->m_trace->dump();
		m_vm->m_trace->pop();
	}

	const char* who() {
		return m_id;
	}

	const char* what() {
		return m_msg.c_str();
	}

	int argc() {
		return params.size();
	}

private:
	const char* m_id;
	orcaVM* m_vm;
	string m_msg;

public:
	deque<orcaData> params;
	string m_stack_trace;
};

struct catch_t 
{
	const char* name;
	int address;
	vector<int> lv;
};

struct CatchList 
{
	vector<catch_t> catch_list;
	orcaObject* m_my;

	CatchList(const char* code, int num, orcaObject* my) : m_my(my)
	{
		catch_t p;
		const char* cp = code;

		for(int i=0; i<num; i++) {
			int len = cp[0];

			if (len > 0) {
				p.name = &cp[1];
				cp += 1 + 1 + len;

				int num = cp[0];
				cp++;
				if (num > 0) {
					for(int i=0; i<num; i++) {
						p.lv.push_back(cp[i]);
					}

					cp += num;
				}

				p.address = *(int*)cp;
				cp += sizeof(int);

			}
			else {
				p.name = NULL;
				p.address = *(int*)&cp[1];
				cp += 1 + sizeof(int);
			}

			catch_list.push_back(p);
		}
	}

	catch_t* compare(const char* name)
	{
		vector<catch_t>::iterator vi = catch_list.begin();
		for(; vi!=catch_list.end(); ++vi) {
			if ((*vi).name == NULL) {
				return &(*vi);
			}
			else if (strncmp((*vi).name, name, strlen((*vi).name)) == 0) {
				size_t vlen = strlen((*vi).name);
				if (strlen(name) > vlen) {
					if (name[vlen] != '.') {
						continue;
					}
				}

				return &(*vi);
			}
		}

		return NULL;
	}

	void clear()
	{
		catch_list.clear();
	}
};

#endif


