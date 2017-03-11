/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaTrace.cpp - impl. of orca stack trace

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <map>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

#include "orcaTrace.h"
#include "orcaVM.h"

using namespace std;

void orcaTrace::push(const char* name, const char* cp)
{ 
	m_item.push_back(trace_info(name, cp)); 
}

void orcaTrace::pop()
{
	m_item.pop_back(); 
}

string orcaTrace::dump()
{
	string ret = "recent call-stack trace\n";
	
	if (top_cp != NULL && top_name != NULL) {
		//push(top_name, *top_cp);
	}

	for(int i=0; i<10; i++) {
		if (i >= m_item.size()) {
			break;
		}

		trace_info t = m_item[m_item.size()-1-i];
		
		map<const char*, int>::iterator mi = m_vm->m_debug.upper_bound(t.cp+1);
		int line = 0;
		if (mi != m_vm->m_debug.begin()) {
			--mi;
			line = mi->second;
		}

		map<const char*, string>::iterator ni = m_vm->m_debug_name.upper_bound(t.cp);
		string name = "internal";
		if (ni != m_vm->m_debug_name.begin()) {
			--ni;
			name = ni->second;
		}

		ni = m_vm->m_debug_line.upper_bound(t.cp);
		string code = "\n";
		if (ni != m_vm->m_debug_line.begin()) {
			--ni;
			code = ni->second;
		}

		ret += string(">> ") + (t.funname?t.funname:"(null)") + "\t(" + name + " " +
				lexical_cast<string>(line) + ")\t" + code;
	}

	return ret;
}

