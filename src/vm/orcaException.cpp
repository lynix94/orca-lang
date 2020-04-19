/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaException.cpp - handling exception & catch

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/


#include "orcaException.h"
#include "orca_opcode.h"
#include "orcaVM.h"

orcaException::orcaException(orcaVM* vm, const char* id, string msg) : m_id(id)
{ 
	if (vm == NULL) vm = get_current_vm();
	m_vm = vm;

	if (msg != "") {
		params.push_back(msg);
	}

	make_trace();
	m_vm->m_last_trace_info = m_stack_trace;

	rc_inc();
}

orcaException::orcaException(orcaVM* vm, const char* id, int argc) : m_id(id)
{ 
	if (vm == NULL) vm = get_current_vm();
	m_vm = vm;

	for (int i=0; i<argc; i++) {
		orcaData d = vm->m_stack->pop();
		//d.rc_inc();
		params.push_front(d);
	}

	make_trace();
	m_vm->m_last_trace_info = m_stack_trace;

	rc_inc();
}

const char* orcaException::what()
{ 
	if (params.empty()) { 
		return "";
	} 

	what_buff = params[0].string_(NULL);
	return what_buff.c_str();
} 

void orcaException::rc_inc()
{
	for (int i=0; i<params.size(); i++) {
		params[i].rc_inc();
	}
}

void orcaException::rc_dec()
{
	for (int i=0; i<params.size(); i++) {
		params[i].rc_dec();
	}
}

void orcaException::make_trace()
{
	if (m_vm->m_trace->top_name == NULL) {
		m_vm->m_trace->top_name = m_vm->m_module->get_name();
	}

	const char* cp = NULL;
	if (m_vm->m_cptr != NULL) {
		cp = *m_vm->m_cptr;
	}
	else if (m_vm->m_cp != NULL) {
		cp = m_vm->m_cp;
	}

	if (cp == NULL) { // can not make trace
		// assert(false);
		return;
	}

	m_vm->m_trace->push(m_vm->m_trace->top_name, cp);
	m_stack_trace = m_vm->m_trace->dump();
	m_vm->m_trace->pop();
}


CatchList::CatchList(const char* code, int num, orcaObject* my, int stack_size) : m_my(my), stack_size(stack_size)
{
	const char* cp = code;

	for(int i=0; i<num; i++) {
		catch_t p;

		// name
		int len = cp[0];
		if (len == 0) {
			p.name = NULL;
		}
		else {
			p.name = &cp[1];
		}

		cp += 1 + len;

		// var
		int varnum = *(short*)cp;
		cp += sizeof(short);
		if (varnum > 0) {
			for (int i=0; i<varnum; i++) {
				p.lv.push_back(*(short*)cp);
				cp += sizeof(short);
			}
		}

		// address
		p.address = *(int*)cp;
		cp += sizeof(int);
		catch_list.push_back(p);

	}
}

void CatchList::dump()
{
	vector<catch_t>::iterator vi = catch_list.begin();
	for(; vi!=catch_list.end(); ++vi) {
		catch_t* ct = &(*vi);
		printf("# catch: %s, varnum:%d, ", ct->name, (int)ct->lv.size());
		for (int i=0; i<ct->lv.size(); i++)
			printf("%d, ", ct->lv[i]);

		printf("\n");
	}
}

catch_t* CatchList::compare(const char* name)
{
	vector<catch_t>::iterator vi = catch_list.begin();
	for(; vi!=catch_list.end(); ++vi) {
		if (strcmp((*vi).name, "any") == 0) {
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



