/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaVM.cpp - main orcaVM routine

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/

//#define _VM_DEBUG_

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <netinet/in.h>
#include <dlfcn.h>
#endif

#ifdef WIN32
#include <direct.h>
#define getcwd(a, b) _getcwd(a, b)
#endif

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <string>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
namespace fs = boost::filesystem;
#include <gmpxx.h>

#include "porting.h"

// common
#include "orcaGlobal.h"
#include "orca_opcode.h"
#include "kyString.h"


// primitive
#include "orcaInteger.h"
#include "orcaFloat.h"
#include "orcaString.h"
#include "orcaTuple.h"
#include "orcaTupleIter.h"
#include "orcaList.h"
#include "orcaListIterator.h"
#include "orcaSbf.h"
#include "orcaVirtList.h"
#include "orcaMap.h"
#include "orcaBoolean.h"
#include "orcaNil.h"
#include "orcaRoot.h"

// vm
#include "orcaLocal.h"
#include "orcaStack.h"
#include "orcaForStack.h"
#include "orcaSwitchStack.h"
#include "orcaSelectStack.h"
#include "orcaDecodeStack.h"
#include "orcaException.h"
#include "orcaExceptionObject.h"
#include "orcaParserObject.h"
#include "orcaObjectMembers.h"
#include "orcaObjectParents.h"

// parser
#include "parserParser.h"
#include "parserParse.h"

// core
#include "orcaPack.h"
#include "orcaDatetime.h"
#include "orcaSocket.h"
#include "orcaSelector.h"

#include "orcaVM.h"

#define FJ_INC 1
#define TO_INT(a) (*(int*)(a))
#define TO_SHORT(a) (*(short*)(a))
#define TO_LONGLONG(a) (*(long long*)(a))
#define TO_DOUBLE(a) (*(double*)(a))

using namespace std;
using namespace boost;

vector<fs::path> orcaVM::m_module_path;
map<const char*, int> orcaVM::m_debug;
map<const char*, string> orcaVM::m_debug_name;
map<const char*, string> orcaVM::m_debug_line;

orcaData g_last_pop_stack = NIL;


inline void BOOL_REVERSE(orcaData d) /*{{{*/
{
	if (d.get_type() != TYPE_BOOL)
		return;

	d.i( d.i()?0:1 );
}
/*}}}*/

void orca_error(const char* fmt, ...)/*{{{*/
{
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	printf("\n");
	va_end(ap);

	orcaVM* vm = get_current_vm();
	cout << vm->m_trace->dump() << endl;

	exit(0);
}
/*}}}*/

void set_current_vm(orcaVM* vm)/*{{{*/
{
	pthread_setspecific(g_thread_context, vm);
}
/*}}}*/

orcaVM* get_current_vm()/*{{{*/
{
	return (orcaVM*)pthread_getspecific(g_thread_context);
}
/*}}}*/

void orcaVM::init_once()/*{{{*/
{
	static bool flag = false;
	if (flag == false) {
		flag = true;

		NIL.set_type(TYPE_NIL);

		// set module path

		// default path
#ifdef WIN32
		char FileName[_MAX_PATH]; 
		GetModuleFileNameA(NULL, FileName, _MAX_PATH);  
		fs::path orca_file_path(FileName);
		m_module_path.push_back(orca_file_path.branch_path() / "lib");	
#else
		m_module_path.push_back(fs::path("/lib/orca"));
		m_module_path.push_back(fs::path("/usr/local/lib/orca"));
#endif

		char* cp = getenv("ORCA_PATH");
		if (cp == NULL) {
			return;
		}

		string path = cp;

		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
#ifdef WIN32
		boost::char_separator<char> sep(";", "");
#else
		boost::char_separator<char> sep(":", "");
#endif

		tokenizer tok(path, sep);
		for (tokenizer::iterator it=tok.begin(); 
			 it != tok.end(); ++it) 
		{
			try {
				if (fs::is_directory(fs::path(*it))) {
					m_module_path.push_back(fs::path(*it));
				}
			}
			catch(...) {
				continue;
			}
		}
	}
}
/*}}}*/

void orcaVM::init()/*{{{*/
{
	init_once();

	NIL.set_type(TYPE_NIL);

	m_for_stack = new orcaForStack();
	m_local = new orcaLocal();
	m_decode_stack = new orcaDecodeStack(this);
	m_switch_stack = new orcaSwitchStack(this);
	m_select_stack = new orcaSelectStack(this);
	m_stack = new orcaStack(m_local);
	m_trace = new orcaTrace(this);

	m_cptr = NULL;
	m_cp = NULL;
}
/*}}}*/

void orcaVM::cleanup()/*{{{*/
{
	delete m_for_stack;
	delete m_decode_stack;
	delete m_switch_stack;
	delete m_select_stack;
	delete m_stack;
	delete m_local;
	delete m_trace;
}
/*}}}*/

struct auto_trace/*{{{*/
{
	auto_trace(orcaVM* vm) {
		vp = vm;
		const char* cp = NULL;
		if (vm->m_cptr != NULL) {
			cp = *vm->m_cptr;
		}
		else if (vm->m_cp != NULL) {
			cp = vm->m_cp;
		}

		vp->m_trace->push(vm->m_curr->get_name(), cp);
	}

	~auto_trace() {
		vp->m_trace->pop();
	}

	orcaVM* vp;
};
/*}}}*/

orcaData orcaVM::invoke_internal_func(InternalFunction& in, int param_n) /*{{{*/
{
	int code = in.idx;
	u_internal d = in.owner;
	orcaData r;

	switch(code) 
	{
	case FI_STR_ADD:	
		r = g_string.ex_add(this, d.so->s, param_n); 
		break;

	case FI_STR_MUL:	
		r = g_string.ex_mul(this, d.so->s, param_n); 
		break;

	case FI_STR_MOD:	
		r = g_string.ex_mod(this, d.so->s, param_n); 
		break;

	case FI_STR_GT:	
		r = g_string.ex_gt(this, d.so->s, param_n); 
		break;

	case FI_STR_GE:	
		r = g_string.ex_ge(this, d.so->s, param_n); 
		break;

	case FI_STR_LT:	
		r = g_string.ex_lt(this, d.so->s, param_n); 
		break;

	case FI_STR_LE:	
		r = g_string.ex_le(this, d.so->s, param_n); 
		break;

	case FI_STR_EQ:	
		r = g_string.ex_eq(this, d.so->s, param_n); 
		break;

	case FI_STR_NEQ:	
		r = g_string.ex_neq(this, d.so->s, param_n); 
		break;

	case FI_STR_LENGTH:	
		r = g_string.ex_length(this, d.so->s, param_n);
		break;

	case FI_STR_FIND:	
		r = g_string.ex_find(this, d.so->s, param_n); 
		break;

	case FI_STR_FIND_ALL:	
		r = g_string.ex_find_all(this, d.so->s, param_n); 
		break;

	case FI_STR_STRIP:	
		r = g_string.ex_strip(this, d.so->s, param_n); 
		break;

	case FI_STR_LSTRIP:	
		r = g_string.ex_lstrip(this, d.so->s, param_n); 
		break;

	case FI_STR_REPLACE:	
		r = g_string.ex_replace(this, d.so->s, param_n); 
		break;

	case FI_STR_RSTRIP:	
		r = g_string.ex_rstrip(this, d.so->s, param_n); 
		break;

	case FI_STR_TO_INT:	
		r = g_string.ex_integer(this, d.so->s, param_n); 
		break;

	case FI_STR_TO_FLOAT:	
		r = g_string.ex_float(this, d.so->s, param_n); 
		break;

	case FI_STR_TO_STR:	
		r = g_string.ex_string(this, d.so->s, param_n); 
		break;

	case FI_STR_TO_REPR:	
		r = g_string.ex_repr(this, d.so->s, param_n); 
		break;

	case FI_STR_STARTSWITH:	
		r = g_string.ex_starts_with(this, d.so->s, param_n); 
		break;

	case FI_STR_ENDSWITH:	
		r = g_string.ex_ends_with(this, d.so->s, param_n); 
		break;

	case FI_STR_HASH:	
		r = g_string.ex_hash(this, d.so->s, param_n); 
		break;

	case FI_STR_SPLIT:	
		r = g_string.ex_split(this, d.so->s, param_n); 
		break;

	case FI_STR_PUSH_BACK:	
		g_string.ex_push_back(this, d.so->s, param_n); 
		r.__so_set__(d.so);
		break;

	case FI_STR_CHAR:	
		r = g_string.ex_char(this, d.so->s, param_n); 
		break;

	case FI_STR_UPPER:	
		r = g_string.ex_upper(this, d.so->s, param_n); 
		break;

	case FI_STR_LOWER:	
		r = g_string.ex_lower(this, d.so->s, param_n); 
		break;

	case FI_STR_LIST_FORMAT:	
		r = g_string.ex_list_format(this, d.so->s, param_n); 
		break;

	case FI_INT_ADD:	
		r = g_integer.ex_add(this, d.i, param_n); 
		break;

	case FI_INT_SUB:	
		r = g_integer.ex_sub(this, d.i, param_n); 
		break;

	case FI_INT_MUL:	
		r = g_integer.ex_mul(this, d.i, param_n); 
		break;

	case FI_INT_DIV:	
		r = g_integer.ex_div(this, d.i, param_n); 
		break;

	case FI_INT_MOD:	
		r = g_integer.ex_mod(this, d.i, param_n); 
		break;

	case FI_INT_GT:	
		r = g_integer.ex_gt(this, d.i, param_n); 
		break;

	case FI_INT_GE:	
		r = g_integer.ex_ge(this, d.i, param_n); 
		break;

	case FI_INT_LT:	
		r = g_integer.ex_lt(this, d.i, param_n); 
		break;

	case FI_INT_LE:	
		r = g_integer.ex_le(this, d.i, param_n); 
		break;

	case FI_INT_EQ:	
		r = g_integer.ex_eq(this, d.i, param_n); 
		break;

	case FI_INT_NEQ:	
		r = g_integer.ex_neq(this, d.i, param_n); 
		break;

	case FI_INT_AND:	
		r = g_integer.ex_and(this, d.i, param_n); 
		break;

	case FI_INT_OR:	
		r = g_integer.ex_or(this, d.i, param_n); 
		break;

	case FI_INT_TO_INT:	
		r = g_integer.ex_integer(this, d.i, param_n); 
		break;

	case FI_INT_TO_FLOAT:	
		r = g_integer.ex_float(this, d.i, param_n); 
		break;

	case FI_INT_TO_STR:	
		r = g_integer.ex_string(this, d.i, param_n); 
		break;

	case FI_BN_ADD:	
		r = g_big_integer.ex_add(this, d.bo->bn, param_n); 
		break;

	case FI_BN_SUB:	
		r = g_big_integer.ex_sub(this, d.bo->bn, param_n); 
		break;

	case FI_BN_MUL:	
		r = g_big_integer.ex_mul(this, d.bo->bn, param_n); 
		break;

	case FI_BN_DIV:	
		r = g_big_integer.ex_div(this, d.bo->bn, param_n); 
		break;

	case FI_BN_MOD:	
		r = g_big_integer.ex_mod(this, d.bo->bn, param_n); 
		break;

	case FI_BN_GT:	
		r = g_big_integer.ex_gt(this, d.bo->bn, param_n); 
		break;

	case FI_BN_GE:	
		r = g_big_integer.ex_ge(this, d.bo->bn, param_n); 
		break;

	case FI_BN_LT:	
		r = g_big_integer.ex_lt(this, d.bo->bn, param_n); 
		break;

	case FI_BN_LE:	
		r = g_big_integer.ex_le(this, d.bo->bn, param_n); 
		break;

	case FI_BN_EQ:	
		r = g_big_integer.ex_eq(this, d.bo->bn, param_n); 
		break;

	case FI_BN_NEQ:	
		r = g_big_integer.ex_neq(this, d.bo->bn, param_n); 
		break;

	case FI_BN_AND:	
		r = g_big_integer.ex_and(this, d.bo->bn, param_n); 
		break;

	case FI_BN_OR:	
		r = g_big_integer.ex_or(this, d.bo->bn, param_n); 
		break;

	case FI_BN_TO_INT:	
		r = g_big_integer.ex_integer(this, d.bo->bn, param_n); 
		break;

	case FI_BN_TO_FLOAT:	
		r = g_big_integer.ex_float(this, d.bo->bn, param_n); 
		break;

	case FI_BN_TO_STR:	
		r = g_big_integer.ex_string(this, d.bo->bn, param_n); 
		break;

	case FI_FLOAT_ADD:	
		r = g_float.ex_add(this, d.r, param_n); 
		break;

	case FI_FLOAT_SUB:	
		r = g_float.ex_sub(this, d.r, param_n); 
		break;

	case FI_FLOAT_MUL:	
		r = g_float.ex_mul(this, d.r, param_n); 
		break;

	case FI_FLOAT_DIV:	
		r = g_float.ex_div(this, d.r, param_n); 
		break;

	case FI_FLOAT_MOD:	
		r = g_float.ex_mod(this, d.r, param_n); 
		break;

	case FI_FLOAT_GT:	
		r = g_float.ex_gt(this, d.r, param_n); 
		break;

	case FI_FLOAT_GE:	
		r = g_float.ex_ge(this, d.r, param_n); 
		break;

	case FI_FLOAT_LT:	
		r = g_float.ex_lt(this, d.r, param_n); 
		break;

	case FI_FLOAT_LE:	
		r = g_float.ex_le(this, d.r, param_n); 
		break;

	case FI_FLOAT_EQ:	
		r = g_float.ex_eq(this, d.r, param_n); 
		break;

	case FI_FLOAT_NEQ:	
		r = g_float.ex_neq(this, d.r, param_n); 
		break;

	case FI_FLOAT_AND:	
		r = g_float.ex_and(this, d.r, param_n); 
		break;

	case FI_FLOAT_OR:	
		r = g_float.ex_or(this, d.r, param_n); 
		break;

	case FI_FLOAT_TO_INT:	
		r = g_float.ex_integer(this, d.r, param_n); 
		break;

	case FI_FLOAT_TO_FLOAT:	
		r = g_float.ex_float(this, d.r, param_n); 
		break;

	case FI_FLOAT_TO_STR:	
		r = g_float.ex_string(this, d.r, param_n); 
		break;

	case FI_BOOL_EQ:	
		r = g_boolean.ex_eq(this, d.i, param_n); 
		break;

	case FI_BOOL_NEQ:	
		r = g_boolean.ex_neq(this, d.i, param_n); 
		break;

	case FI_BOOL_AND:	
		r = g_boolean.ex_and(this, d.i, param_n); 
		break;

	case FI_BOOL_OR:	
		r = g_boolean.ex_or(this, d.i, param_n); 
		break;

	case FI_BOOL_TO_STR:	
		r = g_boolean.ex_string(this, d.i, param_n); 
		break;

	case FI_BOOL_TO_INT:	
		r = g_boolean.ex_integer(this, d.i, param_n); 
		break;

	case FI_BOOL_TO_FLOAT:	
		r = g_boolean.ex_float(this, d.i, param_n); 
		break;

	case FI_NIL_TO_STR:	
		r = g_nil.string_();
		break;

	default:
		return NIL;
	}

	return r;
}
/*}}}*/

struct auto_local/*{{{*/
{
	auto_local(int size, orcaLocal* lp) : m_lp(lp) {
		lp->increase(size);
	}

	~auto_local() {
		m_lp->decrease();
	}

	orcaLocal* m_lp;
};
/*}}}*/

void orcaVM::call(int param_n)/*{{{*/
{
#ifdef _VM_DEBUG_
	char buff[1024]; // for debug message
#endif
	int param_size = m_local->recount_extract_from_stack(m_stack, param_n);

	orcaData f = m_stack->at(param_n);
	orcaData r;
	if (is<TYPE_INTERNAL>(f)) {
		PRINT1("\t\t  internal function called: %x\n", f.i());
		{{	auto_local al(param_size, m_local);

			m_local->copy_from_stack(m_stack, param_n);
			set_caller(m_curr);
			m_stack->pop();

			r = invoke_internal_func(f.internal(), param_n);
			m_stack->push(r);
		}}
	}
	else if (is<TYPE_NATIVE>(f)) {
		PRINT0("\t\t  native code called\n");
		{{	auto_local al(param_size, m_local);

			m_local->copy_from_stack(m_stack, param_n);
			set_caller(m_curr);
			m_stack->pop();

			r = f.native_call(this, param_size);
			m_stack->push(r);
		}}
	}
	else if (is<TYPE_OBJ>(f)) {
#ifdef _VM_DEBUG_
		char buff[1024];
		PRINT1("\t\t  object called: %s\n", f.o()->dump(buff));
#endif
		int inc_size=param_size;
		if (f.o()->m_code != NULL) {
			int frame_size = ((CodeHeader*)(f.o()->m_code))->frame_size;
			if (frame_size > param_n) {
				inc_size = frame_size;
			}
		}


		{{	auto_local al(inc_size, m_local);

			m_local->copy_from_stack(m_stack, param_n);
			set_caller(m_curr);
			m_stack->pop();

			{{	
				auto_trace at(this);
				m_trace->top_name = m_curr->get_name();
				orcaData ret = (*f.o())(this, param_size);
				m_local->mark_return(ret);
				m_stack->push(ret);
			}}
		}}
	}
	else if (is<TYPE_TYPE>(f)) {
		{{	auto_local al(param_size, m_local);
			m_local->copy_from_stack(m_stack, param_n);

			orcaData d;
			int i = 0;
			double fl = 0;
			string s = "";
			bool b = false;

			switch(f.type_get().t)
			{
			case TYPE_INT:
			case TYPE_BIGNUM:
				if (param_n > 0) 
					i = m_local->get(0).Integer();

				m_stack->replace(i);
				break;

			case TYPE_REAL:
				if (param_n > 0) 
					fl = m_local->get(0).Double();

				m_stack->replace(fl);
				break;
				
			case TYPE_BOOL:
				if (param_n > 0) 
					b = m_local->get(0).Boolean();

				m_stack->replace(b);
				break;

			case TYPE_STR:
				if (param_n > 0) 
					s = m_local->get(0).String();

				m_stack->replace(s);
				break;

			case TYPE_REGEX:
				if (param_n > 0) {
					s = m_local->get(0).String();
					d.re_set(s);
				}

				m_stack->replace(d);
				break;

			case TYPE_OBJ:
				{
					orcaObject* op = (orcaObject*)f.type_get().vp;
					if (dynamic_cast<orcaList*>(op)) {
						orcaList* lp = new orcaList();
						for (int i=0; i<param_n; i++) 
							lp->push_back(m_local->get(i));

						d.o_set(lp);
					}
					else if (dynamic_cast<orcaTuple*>(op)) {
						orcaTuple* tp = new orcaTuple();
						for (int i=0; i<param_n; i++) 
							tp->push_back(m_local->get(i));

						d.o_set(tp);
					}
					else if (dynamic_cast<orcaMap*>(op)) {
						orcaMap* mp =  new orcaMap();

						for (int i=0; i<param_n; i+=2) {
							orcaData key = m_local->get(i);
							orcaData val = m_local->get(i+1);
							mp->update(key, val);
						}

						d.o_set(mp);
					}
					else {
						s = m_local->get(0).String();
						if (g_root->has_member(s.c_str(), d)) {
							// do nothing, already assigned
						}
					}
				}

				m_stack->replace(d);
				break;

			case TYPE_NIL:
			case TYPE_NATIVE:
			case TYPE_INTERNAL: 
			default:
				m_stack->replace(NIL);
				break;
			}
		}}
	}
	else {
		{{	auto_local al(param_size, m_local);

			m_local->copy_from_stack(m_stack, param_n);
			//m_stack->pop();	// return itself
		}}
	}
}
/*}}}*/

orcaData& orcaVM::handle_throw(const char* name)/*{{{*/
{
	do {
		orcaData& ret = m_local->unwind();

		if (is<TYPE_MARK>(ret)) {
			switch(ret.mark().type)
			{
			case MARK_CATCH: 
				return ret;

			case MARK_SCOPE: 
			  {
				orcaObject* o = (orcaObject*)ret.mark().vp;
				orcaData f = o->get_member("}");
				m_stack->push(f);
				call(0);
				m_stack->pop(); // because it's void type
				m_local->clean_mark(MARK_SCOPE);
				break;
			  }
			case MARK_FOR:
			  {
				m_for_stack->pop();
				m_local->clean_mark(MARK_FOR);
				break;
			  }
			case MARK_DECODE: 
			  {
				m_decode_stack->pop();
				m_local->clean_mark(MARK_DECODE);
				break;
			  }
			case MARK_STACK: 
			  {
				m_stack->pop();
				m_local->clean_mark(MARK_STACK);
				break;
			  }
			case MARK_SWITCH: 
			  {
				m_switch_stack->pop();
				m_local->clean_mark(MARK_SWITCH);
				break;
			  }
			case MARK_SELECT: 
			  {
				m_select_stack->pop();
				m_local->clean_mark(MARK_SELECT);
				break;
			  }
			default:
				orca_error("fatal.. invalid mark\n");
			}
		}
		else if (is<TYPE_NIL>(ret)) {
			return ret;
		}
		else {
			orca_error("fatal.. invalid exception\n");
		}
	} while(true);
}
/*}}}*/

orcaObject* orcaVM::find_object_by_path(const char* path)/*{{{*/
{
	orcaObject* op = g_root;
	orcaData out;

	char buff[1024];
	strncpy(buff, path, 1024);

	if (strcmp(buff, "root") == 0) {
		op = g_root;
	}
	else {
		char *last;
		char *tok = strtok_r(buff, ".", &last);
		if (op->has_member(tok, out) == false) {
			throw orcaException(this, "orca.define", string("define under failed"));
		}
		op = out.Object();

		while (tok != NULL) {
			tok = strtok_r(NULL, ".", &last);
			if (tok == NULL) break;
			if (op->has_member(tok, out) == false) {
				throw orcaException(this, "orca.define", string("define under failed"));
			}

			op = out.Object();
		}
	}

	return op;
}
/*}}}*/


orcaObject* orcaVM::load_parse_object(const string& name, const string& path)
{
	PRINT1("\t\t  load parse: %s\n", name.c_str());
	string mod_name = string("libparse_") + name + ".so";
	string mod_path = mod_name;
	if (path != "") {
		mod_path = path + "/" + mod_name;
	}

	DLHANDLE handle = dlopen(mod_path.c_str(), RTLD_NOW);
	if (handle == NULL) {
		throw orcaException(this, "orca.module", kyString::sprintf("module '%s' launch failure", mod_path.c_str()));
	}

	typedef void* (*fp_t)(void);
	fp_t pfunc = (fp_t)dlsym(handle, "get_parse");
	if (pfunc == NULL) {
		printf("invalid module file: %p, %s\n", handle, "parse");
		throw orcaException(this, "orca.module", "invalid module");
	}

	orcaObject* obj = (orcaObject*)(*pfunc)();
	if (obj == NULL) {
		throw orcaException(this, "orca.define", kyString::sprintf("parse object %s load failed", name.c_str()));
	}

	obj->insert_member("RESULT", NIL);
	obj->insert_member("ERROR", "");
	return obj;
}

orcaObject* orcaVM::exec_define(const char* c, int size, const char* code,
							orcaObject* owner, time_t last_write_time, const string& path)/*{{{*/
{
	vector<orcaObject*> v;
	orcaObject* current = owner;
	orcaObject* o;
	orcaData d;
	int count, j;
	vector<orcaObject*> parents;

	orcaObject* mod = NULL;

	if (current == NULL) current = g_root;

	for(int i=0; i<size; i++) {
		PRINT2("%u[%02x] ", i, (unsigned char)*(c + i));
		switch((unsigned char)c[i])
		{
		case OP_DEF_START:			// this, flag, len, name_cp
		case OP_DEF_UNDER_START:  { // this, flag, len, name_cp, len, under_cp
			bool is_under = false;
			const char* name = &c[i+1+1+1];

			if ((unsigned char)c[i] == OP_DEF_UNDER_START) {
				is_under = true;
			}
			else if (strcmp(name, "CODE") == 0) {
				v.push_back(NULL);
				i += 1 + 1 + c[i+1+1];
				current = owner;
				if (mod == NULL) mod = current;
				break;
			}

			if (c[i+1] & BIT_DEFINE_PARSE) {
				o = load_parse_object(name, path);
			}
			else {
				o = new orcaObject();
			}

			o->make_original();
			d.o_set(o);
			d.o()->set_name(name);

			orcaObject* op = current;

			int len = 0;
			if (is_under) {
				len = c[i+1+1];
				PRINT4("\t\t DEF under start: %s under %s, (%p) - depth:%lu\n", name, &c[i+1+1+1+len+1], d.o(), v.size());
				op = find_object_by_path(&c[i+1+1+1+len+1]);
			}
			else {
				PRINT4("\t\t DEF start: %s(%d), (%p) - depth:%lu\n", name, c[i+1+1], d.o(), v.size());
			}

			if (c[i+1] & BIT_DEFINE_STATIC) {
				if (op->insert_static(d.o()->get_name(), d) == false)
					throw orcaException(this, "orca.define", kyString::sprintf("member '%s' already exists", name));
			}
			else {
				if (op->insert_member(d.o()->get_name(), d) == false)
					throw orcaException(this, "orca.define", kyString::sprintf("member '%s' already exists", name));
			}

			d.o()->set_flag(c[i+1]);

			if (is_under) {
				v.push_back(current);
				v.push_back(op);
				i += 1 + 1 + c[i+1+1] + 1 + c[i+1+1+1+len];
			}
			else {
				v.push_back(current);
				i += 1 + 1 + c[i+1+1];
				if (mod == NULL) {
					mod = d.o();
				}
			}

			current = d.o();
			break;
		  }



		case OP_DEF_END:
			PRINT1("\t\t DEF END - depth:%lu\n", v.size()-1);
			o = v[v.size()-1];
			if (o != NULL) { // !CODE
				current = o;
				m_curr = o;
			}

			v.pop_back();
			break;

		case OP_DEF_UNDER_END:
			PRINT1("\t\t DEF UNDER END - depth:%lu\n", v.size()-2);
			o = v[v.size()-2];
			current = o;
			m_curr = o;
			v.pop_back(); // under target Object
			v.pop_back(); // real saved current
			break;

		case OP_REG: // this, flag, len, cp
			PRINT1("\t\t  regist orcaObject: %s\n", &c[i+1+1+1]);
			if (c[i+1] & BIT_DEFINE_STATIC) {
				current->insert_static(&c[i+1+1+1], NIL);
			}
			else {
				current->insert_member(&c[i+1+1+1], NIL);
			}

			i += 1 + 1 + c[i+1+1];
			break;

		case OP_DEF_CODE:
			PRINT2("\t\t  define code: %lld of %p\n", TO_LONGLONG(&c[i+1]), code);
			current->m_code = code + TO_LONGLONG(&c[i+1]);
			i += sizeof(long long);
			break;

		case OP_DEF_INIT:
			PRINT1("\t\t  define init code: %lld\n", TO_LONGLONG(&c[i+1]));
			m_curr = current;
			{
				const char** cptr_back = m_cptr;
				exec_code (code, code + TO_LONGLONG(&c[i+1]));
				m_cptr = cptr_back;
			}
			m_stack->dummy_pop();
			i += sizeof(long long);
			break;

		case OP_DEF_SUPER: {
			PRINT1("\t\t  super define: %s\n", &c[i+2]);
			const char* path = &c[i+2];
			
			orcaObject* op = g_root;
			orcaData out;

			char buff[256];
			strncpy(buff, path, 256);

			char *last;
			char *tok = strtok_r(buff, ".", &last);
			if (op->has_member(tok, out) == false) {
				throw orcaException(this, "orca.define", "inherit parents failed");
			}
			op = out.Object();

			while (tok != NULL) {
				tok = strtok_r(NULL, ".", &last);
				if (tok == NULL) break;
				if (op->has_member(tok, out) == false) {
					throw orcaException(this, "orca.define", "inherit parents failed");
				}

				op = out.Object();
			}

			op = current->make_super(op);
			if (op->has_member("init", d)) {
				m_stack->push(d);
				d.rc_inc();
				// cause init refer p1 (by owner)
				// and it can gc on that
				call(0);
				m_stack->dummy_pop();
				d.set_rc(d.get_rc()-1);
			}

			i += 1 + c[i+1];
			break;
		  }

		case OP_USING: { // OP_USING, LEN, C_STR
				PRINT1("\t\t  using: %s\n", &c[i+2]);
				bool ret = false;
				int idx = 0;
				string mod_path = &c[i+2];

				idx = mod_path.find_last_of("/");
				if (idx > 0) { // absolute path
					string dir = mod_path.substr(0, idx);
					string base = mod_path.substr(idx);

					int idx2 = mod_path.find_last_of(".");
					if (idx2 > idx)
						ret = load(mod_path.substr(0, idx2));
					else
						ret = load(mod_path);
				}
				else { // pure name
					idx = mod_path.find(".");
					if (idx > 0)
						ret = load(mod_path.substr(0, idx));
					else
						ret = load(mod_path);
				}

				if (ret == false) {
					printf("module (%s) load failure\n", mod_path.c_str());
					throw orcaException(this, "orca.module", "module launch failure");
				}
			}
			i += 1 + c[i+1];
			break;

		case OP_DEF_CONTEXT_START:    // this, ctx_mod_len, ctx_mod, flag, name_len, name, code_len, code, param_n, params, pos_n, pos
		case OP_DEF_CONTEXT_UNDER_START: { // this, ctx_mod_len, ctx_mod, flag, name_len, name, under_len, under, code_len, code, param_n, params, pos_n, pos
			PRINT2("\t\t CODE DEF CONTEXT start (%p) - depth:%lu\n", code, v.size());

			bool is_under = false;
			if ((unsigned char)c[i] == OP_DEF_UNDER_START) {
				is_under = true;
			}

			int idx = i;
			// ctx_mod
			int ctx_mod_len = c[++idx];
			const char* ctx_mod = &c[++idx];
			idx += ctx_mod_len;

			// name
			int name_len = c[++idx];
			const char* name = &c[++idx];
			idx += name_len-1;

			orcaObject* op = current;

			// under
			int under_len = 0;
			const char* under = "(null)";
			if (is_under) {
				under_len  = c[++idx];
				under = &c[++idx];
				idx += under_len-1;
				op = find_object_by_path(under);
			}

			// code
			int code_len  = TO_INT(&c[++idx]);
			idx += sizeof(int);
			const char* code = &c[idx];
			idx += code_len-1;
			

			PRINT4("\t\t  context object: %s, %s, %s, '%s'\n", ctx_mod, name, under, code);

			// params
			vector<const char*> params;
			int param_n  = c[++idx];
			for (int j=0; j<param_n; j++) {
				int param_len = c[++idx];
				const char* cp = &c[++idx];
				idx += param_len-1;
				
				params.push_back(cp);
			}

			// pos_map
			map<string, int> pos_map;
			int pos_n  = c[++idx];
			for (int j=0; j<pos_n; j++) {
				int name_len = c[++idx];
				const char* cp = &c[++idx];
				idx += name_len-1;
				int line_no = *(int*)&c[++idx];
				idx += sizeof(int)-1;
				pos_map[cp] = line_no;
			}

			orcaData ctx = do_context(ctx_mod, name, code, last_write_time, params, pos_map);
			if (c[i +1+ctx_mod_len +1] & BIT_DEFINE_STATIC) {
				op->insert_static(name, ctx.Object());
			}
			else {
				op->insert_member(name, ctx.Object());
			}

			v.push_back(current);
			if (is_under) {
				v.push_back(op);
			}

			i = idx;
			current = ctx.o();
			break;
		  }
		} // switch
	} // for

	return mod;
}
/*}}}*/

THREAD_RET parallel_thread_entry(void* ap)/*{{{*/
{
	thread_arg_u *arg = (thread_arg_u*)ap;
	g_thread_pool->work(arg);
	return 0;
}
/*}}}*/

void orcaVM::parallel_do(const char* code, const char* offset)/*{{{*/
{
	g_thread_pool->m_mutex_pool.lock();

	thread_arg_u *arg = new thread_arg_u();
	orcaVM *vp = new orcaVM();
	vp->init();
	vp->m_module = this->m_module;
	vp->m_curr = this->m_curr;
	this->m_local->duplicate(vp->m_local);

	arg->p_do.type = 'd';
	arg->p_do.vm_main = vp;
	arg->p_call.run_count = NULL;
	arg->p_do.code = code;
	arg->p_do.offset = offset;

	g_thread_pool->m_cond_mutex.lock();
	bool ret = g_thread_pool->signal_restart(arg);
	if (ret == false) {
		pthread_create(&arg->p_do.tid, NULL, parallel_thread_entry, arg); 
	}

	g_thread_pool->m_cond_start.wait(&g_thread_pool->m_cond_mutex);
	g_thread_pool->m_cond_mutex.unlock();


	g_thread_pool->m_mutex_pool.unlock();
}
/*}}}*/

void orcaVM::parallel_for(const char* code, const char* offset, int* run_count, orcaObject* op, int per)/*{{{*/
{
	g_thread_pool->m_mutex_pool.lock();

	thread_arg_u *arg = new thread_arg_u();
	orcaVM *vp = new orcaVM();
	vp->init();
	vp->m_module = this->m_module;
	vp->m_curr = this->m_curr;
	this->m_local->duplicate(vp->m_local);

	arg->p_for.type = 'f';
	arg->p_for.vm_main = vp;
	arg->p_for.code = code;
	arg->p_for.offset = offset;
	arg->p_for.run_count = run_count;
	arg->p_for.iter = op;
	arg->p_for.per = per;

	g_thread_pool->m_cond_mutex.lock();
	bool ret = g_thread_pool->signal_restart(arg);
	if (ret == false) {
		pthread_create(&arg->p_for.tid, NULL, parallel_thread_entry, arg); 
	}

	g_thread_pool->m_cond_start.wait(&g_thread_pool->m_cond_mutex);
	g_thread_pool->m_cond_mutex.unlock();


	g_thread_pool->m_mutex_pool.unlock();
}
/*}}}*/

void orcaVM::parallel_call(orcaData f, vector<orcaData>& params)/*{{{*/
{
	g_thread_pool->m_mutex_pool.lock();

	thread_arg_u *arg = new thread_arg_u();
	orcaVM *vp = new orcaVM();
	vp->init();
	vp->m_module = this->m_module;
	vp->m_curr = this->m_curr;

	arg->p_call.type = 'c';
	arg->p_call.vm_main = vp;
	arg->p_call.run_count = NULL;
	arg->p_call.func = &f;
	arg->p_call.params = &params;

	g_thread_pool->m_cond_mutex.lock();
	bool ret = g_thread_pool->signal_restart(arg);
	if (ret == false) {
		pthread_create(&arg->p_call.tid, NULL, parallel_thread_entry, arg); 
	}

	g_thread_pool->m_cond_start.wait(&g_thread_pool->m_cond_mutex);
	g_thread_pool->m_cond_mutex.unlock();

	g_thread_pool->m_mutex_pool.unlock();
}
/*}}}*/

void orcaVM::exec_code(const char* code, const char* offset)/*{{{*/
{
	register const char *c = NULL;
	m_cptr = &c;
	m_cp = NULL;

	m_trace->top_cp = &c;

	int j;
	orcaData d, p1, p2, p3, p4;
	bool flag;

#ifdef _VM_DEBUG_
	char buff[1024]; // for debug message
#endif
	PRINT1("\n\n\t\t[Execute code] curr: %s\n", m_curr->m_name);
	if (offset) {
		c = offset;
	}
	else {
		c = code + sizeof(CodeHeader);
	}

	const char* sp = c;
	for(;;c++) {
fast_jmp:
		try {
			PRINT2("%ld[%02x] ", c - sp, (unsigned char)*c);
			switch((unsigned char)*c)
			{
			case OP_NOP:	
				PRINT1("\t\t%p : NOP\n", c);
				break;

			case OP_CALL: {
				PRINT2("\t\t%p : call (param: %d)\n", c, c[1]); 
				j = c[1];

				call(j);
				m_cptr = &c;

				c += 1 + FJ_INC;
				goto fast_jmp;
				break; 
			  }

			case OP_ASSIGN_LOCAL:	
				PRINT2("\t\t%p : assign local (%d)\n", c, TO_SHORT(&c[1]));
				j = TO_SHORT(&c[1]);
				p1 = m_stack->pop();
				m_local->set(j, p1);
				m_stack->push(m_local->get(j));
				c += sizeof(short) + FJ_INC;
				goto fast_jmp;
				break;

			case OP_ASSIGN_MEMBER:	
				PRINT2("\t\t%p : assign member (%s)\n", c, &c[2]);
				p2 = m_stack->pop();
				p1 = m_stack->top();
				m_stack->replace(p1.Object()->update_member(&c[2], p2));
				c += c[1] + 1 + FJ_INC;
				goto fast_jmp;
				break;				

			case OP_ASSIGN_RESERVED:	
				PRINT2("\t\t%p : assign reserved (%d)\n", c, c[1]);
				p2 = m_stack->pop();
				p1 = m_stack->top();
				switch(c[1])
				{
				case OP_PUSH_OWNER:
					if (p1.Object()->m_owner) p1.o()->m_owner->rc_dec();
					p1.o()->m_owner = p2.Object();
					p1.o()->m_owner->rc_inc();
					break;

				case OP_PUSH_CALLER:
					set_caller(p2.Object());
					break;
				}

				c += 1 + FJ_INC;
				goto fast_jmp;
				break;				

			case OP_ASSIGN_LIST:	
			case OP_ASSIGN_LIST_IR:	
				if ((unsigned char)*c == OP_ASSIGN_LIST_IR)
					flag = true;
				else
					flag = false;

				PRINT2("\t\t%p : assign list (include right?: %d)\n", c, flag);

				p3 = m_stack->pop();
				p2 = m_stack->pop();
				p1 = m_stack->top();

				try {
					flag = set_collection_at(p1, p2, p3, d, flag, this);
				}
				catch (orcaException& e) {
					m_stack->pop(); // clear unpoped stack
					throw e;
				}

				if (flag == true) { // operator[] & set result
					m_stack->pop();
					m_stack->push(d);
				}
				break;				

			case OP_ADD:
				PRINT1("\t\t%p : add\n", c);
				p2 = m_stack->pop();
				p1 = m_stack->top();

				if (isall<TYPE_INT>(p1, p2)) {
					int j = p1.i() + p2.i();
					if (p1.i()>0 && p2.i()>0 && j<0) {
						mpz_t b;
						mpz_init(b);
						mpz_set_si(b, p1.i());
						mpz_add_ui(b, b, p2.i());
						d.bn_set(b);
						mpz_clear(b);
						m_stack->replace(d);
					}
					else {
						m_stack->replace(j);
					}
					continue;
				}
				else if (is<TYPE_STR>(p1)) {
					p3.s_set(p1.s() + p2.string_(this));
					m_stack->replace(p3);
					continue;
				}

				m_stack->pop();
				m_stack->push(p1.operator_add(this, p2));
				break;

			case OP_MUL:		
				PRINT1("\t\t%p : mul\n", c); 
				p2 = m_stack->pop();
				p1 = m_stack->top();

				if (isall<TYPE_INT>(p1, p2)) {
					long long j = (long long)p1.i() * (long long)p2.i();
					if (j > (int)0x7fffff) {
						mpz_t b;
						mpz_init(b);
						mpz_set_si(b, p1.i());
						mpz_mul_si(b, b, p2.i());
						d.bn_set(b);
						mpz_clear(b);
						m_stack->replace(d);
					}
					else {
						m_stack->replace((int)j);
					}

					continue;
				}

				m_stack->pop();
				m_stack->push(p1.operator_mul(this, p2));
				break;

			case OP_MOD:		
				PRINT1("\t\t%p : mod\n", c); 
				p2 = m_stack->pop();
				p1 = m_stack->top();

				if (isall<TYPE_INT>(p1, p2)) {
					int j = p1.i() % p2.i();
					m_stack->replace(j);
					continue;
				}

				m_stack->pop();
				m_stack->push(p1.operator_mod(this, p2));
				break;

			case OP_SUB:
				PRINT1("\t\t%p : sub\n", c);
				p2 = m_stack->pop();
				p1 = m_stack->top();

				if (isall<TYPE_INT>(p1, p2)) {
					int j = p1.i() - p2.i();
					if (p1.i()<0 && p2.i()>0 && j>0) {
						mpz_t b;
						mpz_init(b);
						mpz_set_si(b, p1.i());
						mpz_sub_ui(b, b, p2.i());
						d.bn_set(b);
						mpz_clear(b);
						m_stack->replace(d);
					}
					else {
						m_stack->replace(j);
					}
					continue;
				}

				m_stack->pop();
				m_stack->push(p1.operator_sub(this, p2));
				break;

			case OP_DIV:		
				PRINT1("\t\t%p : div\n", c); 
				p2 = m_stack->pop();
				p1 = m_stack->top();

				if (isall<TYPE_INT>(p1, p2)) {
					if (p2.i() == 0) {
						m_stack->pop();
						throw orcaException(this, "orca.math", "divide by 0");
					}

					m_stack->replace(p1.i() / p2.i());
					continue;
				}

				m_stack->pop();
				m_stack->push(p1.operator_div(this, p2));
				break;

			case OP_AND:
				PRINT1("\t\t%p : and\n", c);
				p2 = m_stack->pop();
				p1 = m_stack->top();
				if (isall<TYPE_INT>(p1, p2) || isall<TYPE_BOOL>(p1, p2)) {
					m_stack->replace(p1.i() && p2.i());
					continue;
				}

				m_stack->replace(p1.operator_and(this, p2));
				break;

			case OP_OR:
				PRINT1("\t\t%p : or\n", c); 
				p2 = m_stack->pop();
				p1 = m_stack->top();
				if (isall<TYPE_INT>(p1, p2) || isall<TYPE_BOOL>(p1, p2)) {
					m_stack->replace(p1.i() || p2.i());
					continue;
				}

				m_stack->replace(p1.operator_or(this, p2));
				break;

			case OP_MINUS:
				PRINT1("\t\t%p : minus\n", c);
				p1 = m_stack->top();

				if (is<TYPE_INT>(p1)) {
					m_stack->replace(p1.i() * -1);
					continue;
				}

				p2.i_set(-1);
				m_stack->pop();
				m_stack->push(p1.operator_mul(this, p2));
				break;

			case OP_ROTATE:
				PRINT1("\t\t%p : rotate\n", c);
				m_stack->rotate();
				break;

			case OP_ROTATE3:
				PRINT1("\t\t%p : rotate3\n", c);
				m_stack->rotate3();
				break;

			case OP_DUP:
				PRINT1("\t\t%p : dup\n", c);
				m_stack->dup();
				break;

			case OP_DUP2:
				PRINT1("\t\t%p : dup2\n", c);
				m_stack->dup2();
				break;

			case OP_EVAL:
				PRINT1("\t\t%p : eval\n", c);
				p1 = m_stack->pop();
				if (is<TYPE_STR>(p1) == false) {
					throw orcaException(this, "orca.type", "eval parameter should be a string");
				}

				d = g_parser->eval(this, p1.s());
				m_stack->push(d);
				break;

			case OP_COMPILE:
				PRINT1("\t\t%p : compile\n", c);
				p1 = m_stack->pop();
				p2 = m_stack->pop();
				if (is<TYPE_STR>(p1) == false || is<TYPE_STR>(p2) == false) {
					throw orcaException(this, "orca.type", "compile parameter should be a string");
				}

				d = g_parser->compile(this, p2.s(), p1.s());
				m_stack->push(d);
				break;

			case OP_NOT:
				PRINT1("\t\t%p : not\n", c);

				d = m_stack->pop();
				if (is<TYPE_BOOL>(d) && d.b() == false) {
					m_stack->push(true);
				}
				else {
					m_stack->push(false);
				}

				break;

			case OP_JMP_TRUE:
				PRINT2("\t\t%p : jmp if true (to: %x)\n", c, TO_INT(&c[1]));
				m_local->cleanup_gc(false);
				d = m_stack->pop();
				if (istrue(d)) {
					c = code + TO_INT(&c[1]);
					goto fast_jmp;
				}
				else {
					c += sizeof(int) + FJ_INC;
					goto fast_jmp;
				}

				break;

			case OP_JMP_FALSE:	
				PRINT2("\t\t%p : jmp if false (to: %x)\n", c, TO_INT(&c[1]));
				m_local->cleanup_gc(false);
				d = m_stack->pop();
				if (isfalse(d)) {
					c = code + TO_INT(&c[1]);
					goto fast_jmp;
				}
				else  {
					c += sizeof(int) + FJ_INC;
					goto fast_jmp;
				}

				break;

			case OP_GT:			
				PRINT1("\t\t%p : gt\n", c); 
				p2 = m_stack->pop();
				p1 = m_stack->top();

				if (isall<TYPE_INT>(p1, p2)) {
					m_stack->replace(p1.i() > p2.i());
					continue;
				}
				else if (isall<TYPE_STR>(p1, p2)) {
					m_stack->replace(p1.s() > p2.s());
					continue;
				}

				m_stack->replace(p1.operator_gt(this, p2));
				break;

			case OP_GE:			
				PRINT1("\t\t%p : ge\n", c); 
				p2 = m_stack->pop();
				p1 = m_stack->top();

				if (isall<TYPE_INT>(p1, p2)) {
					m_stack->replace(p1.i() >= p2.i());
					continue;
				}
				else if (isall<TYPE_STR>(p1, p2)) {
					m_stack->replace(p1.s() >= p2.s());
					continue;
				}

				m_stack->replace(p1.operator_ge(this, p2));
				break;

			case OP_LT:			
				PRINT1("\t\t%p : lt\n", c); 
				p2 = m_stack->pop();
				p1 = m_stack->top();

				if (isall<TYPE_INT>(p1, p2)) {
					m_stack->replace(p1.i() < p2.i());
					continue;
				}
				else if (isall<TYPE_STR>(p1, p2)) {
					m_stack->replace(p1.s() < p2.s());
					continue;
				}

				m_stack->replace(p1.operator_lt(this, p2));
				break;

			case OP_LE:			
				PRINT1("\t\t%p : le\n", c); 
				p2 = m_stack->pop();
				p1 = m_stack->top();

				if (isall<TYPE_INT>(p1, p2)) {
					m_stack->replace(p1.i() <= p2.i());
					continue;
				}
				else if (isall<TYPE_STR>(p1, p2)) {
					m_stack->replace(p1.s() <= p2.s());
					continue;
				}

				m_stack->replace(p1.operator_le(this, p2));
				break;

			case OP_EQ:			
				PRINT1("\t\t%p : eq\n", c); 
				p2 = m_stack->pop();
				p1 = m_stack->top();

				if (isall<TYPE_INT>(p1, p2) || isall<TYPE_BOOL>(p1, p2)) {
					m_stack->replace(p1.i()==p2.i());
					continue;
				}
				else if (isall<TYPE_STR>(p1, p2)) {
					m_stack->replace(p1.s()==p2.s());
					continue;
				}

				m_stack->replace(p1.operator_eq(this, p2));
				break;

			case OP_NEQ:		
				PRINT1("\t\t%p : neq\n", c);
				p2 = m_stack->pop();
				p1 = m_stack->top();

				if (isall<TYPE_INT>(p1, p2) || isall<TYPE_BOOL>(p1, p2)) {
					m_stack->replace(p1.i()!=p2.i());
					continue;
				}
				else if (isall<TYPE_STR>(p1, p2)) {
					m_stack->replace(p1.s()!=p2.s());
					continue;
				}

				m_stack->replace(p1.operator_neq(this, p2));
				break;

			case OP_JMP:	
				PRINT2("\t\t%p : jmp (to: %x)\n", c, TO_INT(&c[1]));
				m_local->cleanup_gc(false);
				c = code + TO_INT(&c[1]);
				goto fast_jmp;
				break;

			case OP_PUSH_LVAR:	
				PRINT2("\t\t%p : push local (%d)\n", c, TO_SHORT(&c[1]));
				j = TO_SHORT(&c[1]);
				m_stack->push(m_local->get(j));
				c += sizeof(short) + FJ_INC;
				goto fast_jmp;
				break;

			case OP_PUSH_MVAR:
				PRINT2("\t\t%p : push mvar %s\n", c, &c[2]);
				d = m_curr->get_member(&c[2]);
				if (is<TYPE_NIL>(d)) {
					throw orcaException(this, "orca.name", 
						string("member ") + &c[2] + 
						" not exist in " + m_curr->dump_str());
				}
				m_stack->push(d);

				c += c[1] + 1 + FJ_INC;
				goto fast_jmp;
				break;

			case OP_PUSH_OVAR:
				PRINT2("\t\t%p : push ovar %s\n", c, &c[2]);
				if (m_curr->get_owner() == NULL) {
					throw orcaException(this, "orca.name", 
						m_curr->dump_str() + "'s owner not exist");
				}

				d = m_curr->get_owner()->get_member(&c[2]);

				if (is<TYPE_NIL>(d)) {
					throw orcaException(this, "orca.name", 
						string("member ") + &c[2] + 
						" not exist in " + m_curr->get_owner()->dump_str());
				}
				m_stack->push(d);
				
				c += c[1] + 1 + FJ_INC;
				goto fast_jmp;
				break;

			case OP_PUSH_CVAR:
				PRINT2("\t\t%p : push cvar %s\n", c, &c[2]);
				d = get_caller().Object()->get_member(&c[2]);

				if (is<TYPE_NIL>(d)) {
					throw orcaException(this, "orca.name", 
						string("member ") + &c[2] + 
						" not exist in " + get_caller().dump_str());
				}
				m_stack->push(d);
				
				c += c[1] + 1 + FJ_INC;
				goto fast_jmp;
				break;

			case OP_PUSH_INT:	
				PRINT2("\t\t%p : push int (%d)\n", c, TO_INT(&c[1]));
				m_stack->push(TO_INT(&c[1]));
				c += sizeof(int) + FJ_INC;
				goto fast_jmp;
				break;

			case OP_PUSH_BIGNUM: {
				PRINT3("\t\t%p : push bignum (%c%s)\n", c, c[1], &c[3]);
				mpz_t bn;
				mpz_init(bn);
				mpz_set_str(bn, &c[3], 0);

				if (c[1] == '-') {
					mpz_neg(bn, bn);
				}
				m_stack->push(bn);
				mpz_clear(bn);

				c += 1 + c[2] + 1 + FJ_INC;
				goto fast_jmp;
				break;
			}
			
			case OP_PUSH_STR:
			case OP_PUSH_LONG_STR: {
				int len = c[1];
				int size = sizeof(char);
				const char* cp = &c[sizeof(char) + 1];

				if ((unsigned char)*c == OP_PUSH_LONG_STR) {
					len = TO_INT(&c[1]);
					size = sizeof(int);
					cp = &c[sizeof(int) + 1];
				}

				PRINT2("\t\t%p : push string %s\n", c, cp);
				m_stack->push(cp);
				c += len + size + FJ_INC;
				goto fast_jmp;
				break;
			}

			case OP_PUSH_OWNER:
				PRINT2("\t\t%p : push owner: %p\n", c, m_curr->get_owner()); 
				PRINT1("\t\t  object: %s\n", m_curr->get_owner()->dump(buff)); 
				if (m_curr->get_owner() == NULL) {
					m_stack->push(g_root);
				}
				else {
					m_stack->push(m_curr->get_owner());
				}
				break;

			case OP_PUSH_CALLER:	
				PRINT1("\t\t%p : push caller\n", c);
				m_stack->push(get_caller());
				break;

			case OP_PUSH_ROOT:	
				PRINT1("\t\t%p : push root\n", c);
				m_stack->push(g_root);
				break;

			case OP_PUSH_MODULE:	
				PRINT1("\t\t%p : push module\n", c);
				m_stack->push(m_module);
				break;

			case OP_PUSH_BOOLEAN:	
				PRINT2("\t\t%p : push boolean (%d)\n", c, c[1]);
				if (c[1] == 1) {
					m_stack->push(BOOL_TRUE);
				}
				else {
					m_stack->push(BOOL_FALSE);
				}

				c += 1 + FJ_INC;
				goto fast_jmp;
				break;

			case OP_PUSH_REAL:	
				PRINT2("\t\t%p : push real (%g)\n", c, TO_DOUBLE(&c[1]));
				m_stack->push(TO_DOUBLE(&c[1]));

				c += sizeof(double) + FJ_INC;
				goto fast_jmp;
				break;

			case OP_FIND_MEMBER_LAST:
			case OP_FIND_MEMBER:	
				p1 = m_stack->top();

				if (is<TYPE_OBJ>(p1)) {
					if ((unsigned char)*c == OP_FIND_MEMBER_LAST) {
						p2 = p1.Object()->get_member_last(&c[2]);
					}
					else {
						p2 = p1.Object()->get_member(&c[2]);
					}

					PRINT3("\t\t%p : find member (%s) -> %p\n", c, &c[2], p2.o()); 
					m_stack->replace(p2);

					c += c[1] + 1 + FJ_INC;
					goto fast_jmp;
					break;
				}
				else {
					if (strcmp(&c[2], "TYPE") == 0)
					{
						d.type_set(p1);
					}
					else if (strcmp(&c[2], "TYPENAME") == 0 ||  
							 strcmp(&c[2], "NAME") == 0)
					{
						string str;
						switch (p1.get_type())
						{
						case TYPE_INT:
						case TYPE_BIGNUM:	str = "int"; break;
						case TYPE_STR:		str = "string"; break;
						case TYPE_REAL:		str = "float"; break;
						case TYPE_BOOL:		str = "bool"; break;
						case TYPE_REGEX:	str = "regex"; break;
						case TYPE_INTERNAL:	str = "internal function"; break;
						case TYPE_NATIVE:	str = "native function"; break;
						case TYPE_TYPE:		str = "type"; break;
						default:			str = "unknown";
						}

						d = str;
					}
					else if (strcmp(&c[2], "ID") == 0) {
						d = p1.id();
					}
					else if (strcmp(&c[2], "RC") == 0) {
						d = p1.get_rc();
					}
					else if (strcmp(&c[2], "MEMBERS") == 0) {
						orcaObjectMembers* mp = new orcaObjectMembers(p1);
						d = mp;
					}
					else if (strcmp(&c[2], "STATIC_MEMBERS") == 0) {
						orcaObjectMembers* mp = new orcaObjectMembers(p1);
						mp->set_static();
						d = mp;
					}
					else if (strcmp(&c[2], "PARENTS") == 0) {
						orcaObjectParents* pp = new orcaObjectParents(p1);
						d = pp;
					}
					else if (strcmp(&c[2], "ORIGINAL") == 0) {
						d = NIL;
					}
					else {
						switch (p1.get_type())
						{
						case TYPE_STR:
							PRINT2("\t\t%p : find string member (%s)\n", c, &c[2]);
							d = g_string.get_member(&c[2]);
							d.internal().owner.so = m_stack->top().so();
							break;

						case TYPE_INT:
							PRINT2("\t\t%p : find integer member (%s)\n", c, &c[2]);
							d = g_integer.get_member(&c[2]);
							d.internal().owner.i = m_stack->top().i();
							break;

						case TYPE_BIGNUM:
							PRINT2("\t\t%p : find integer member (%s)\n", c, &c[2]);
							d = g_big_integer.get_member(&c[2]);
							d.internal().owner.bo = m_stack->top().bo();
							break;

						case TYPE_REAL:
							PRINT2("\t\t%p : find float member (%s)\n", c, &c[2]);
							d = g_float.get_member(&c[2]);
							d.internal().owner.r = m_stack->top().r();
							break;

						case TYPE_BOOL:
							PRINT2("\t\t%p : find boolean member (%s)\n", c, &c[2]);
							d = g_boolean.get_member(&c[2]);
							d.internal().owner.i = m_stack->top().i();
							break;

						case TYPE_NIL:
							PRINT2("\t\t%p : find nil member (%s)\n", c, &c[2]);
							d = g_nil.get_member(&c[2]);
							d.internal().owner.i = 0;
							break;

						default:
							d = NIL;
							break;
						}
					}

					m_stack->replace(d);
					c += c[1] + 1 + FJ_INC;
					goto fast_jmp;
					break;
				}

				break;

			case OP_FIND_RESERVED:	
				PRINT2("\t\t%p : find reserved (%d)\n", c, c[1]); 

				switch(c[1])
				{
				case OP_PUSH_OWNER:
					if (m_stack->top().Object()->get_owner()) {
						m_stack->replace(m_stack->top().o()->get_owner());
					}
					else {
						m_stack->replace(g_root);
					}

					break;

				case OP_PUSH_CALLER:
					// error
					break;
				}

				c += 1 + FJ_INC;
				goto fast_jmp;
				break;

			case OP_PUSH_MY:	
				PRINT2("\t\t%p : push my: %p\n", c, m_curr); 
				m_stack->push(m_curr);
				break;

			case OP_PUSH_NIL:	
				PRINT1("\t\t%p : push nil\n", c);
				m_stack->push(NIL);
				break;

			case OP_MAKE_LIST: 
			case OP_MAKE_LONG_LIST: {
				int len = c[1];
				int size = sizeof(char);

				if ((unsigned char)*c == OP_MAKE_LONG_LIST) {
					len = TO_INT(&c[1]);
					size = sizeof(int);
				}

				PRINT2("\t\t%p : make list (%d)\n", c, len); 

				orcaList* lp = new orcaList();

				if (len > 0) {
					for(j=0; j<len; j++) {
						d = m_stack->pop();
						if (is<TYPE_EXTRACT>(d)) {
							orcaTuple* tp = TO_TUPLE(d.o());
							for(int k=tp->size()-1; k>=0; k--) {
								lp->push_front(tp->at(k));
							}
						}
						else {
							lp->push_front(d);
						}
					}
				}
				else if (len < 0) {
					if (len == -3) {
						p3 = m_stack->pop();
					}
					else {
						p3 = 1;
					}

					p2 = m_stack->pop();
					p1 = m_stack->pop();

					d = 0;
					if (p3 <= d) {
						throw orcaException(this, "orca.list", "list step is invalid (plus value required)");
					}

					if (p1 < p2) {
						for(d=p1; d<=p2; d = d + p3) {
							lp->push_back(d);
						}
					}
					else {
						for(d=p1; d>=p2; d = d - p3) {
							lp->push_back(d);
						}
					}
				}

				m_stack->push(lp);

				c += size + FJ_INC;
				goto fast_jmp;
				break;
			}

			case OP_MAKE_TUPLE: 
			case OP_MAKE_LONG_TUPLE: {
				int len = c[1];
				int size = sizeof(char);

				if ((unsigned char)*c == OP_MAKE_LONG_TUPLE) {
					len = TO_INT(&c[1]);
					size = sizeof(int);
				}

				PRINT2("\t\t%p : make tuple (%d)\n", c, len); 

				orcaTuple* tp = new orcaTuple();

				if (len >= 0) {
					for (j=len-1; j>=0; j--) {
						d = m_stack->at(j);
						if (is<TYPE_EXTRACT>(d)) {
							orcaTuple* tp2 = TO_TUPLE(d.o());
							for(int k=0; k<tp2->size(); k++) {
								tp->push_back(tp2->at(k));
							}
						}
						else {
							tp->push_back(d);
						}
					}

					m_stack->dummy_pop(len);
				}
				else if (len < 0) {
					if (len == -3) {
						p3 = m_stack->pop();
					}
					else {
						p3 = 1;
					}

					p2 = m_stack->pop();
					p1 = m_stack->pop();

					d = 0;
					if (p3 <= d) {
						throw orcaException(this, "orca.tuple", "tuple step is invalid (plus value required)");
					}

					if (p1 < p2) {
						for(d=p1; d<=p2; d = d + p3) {
							tp->push_back(d);
						}
					}
					else {
						for(d=p1; d>=p2; d = d - p3) {
							tp->push_back(d);
						}
					}
				}

				m_stack->push(tp);

				c += size + FJ_INC;
				goto fast_jmp;
				break;
			}

			case OP_MAKE_MAP: 
			case OP_MAKE_LONG_MAP: {
				int len = c[1];
				int size = sizeof(char);

				if ((unsigned char)*c == OP_MAKE_LONG_MAP) {
					len = TO_INT(&c[1]);
					size = sizeof(int);
				}

				PRINT2("\t\t%p : make map (%d)\n", c, len); 

				orcaMap* mp = new orcaMap();
				for (j=len-1; j>=0; j--) {
					p1 = m_stack->pop();
					p2 = m_stack->pop();
					mp->update(p2, p1);
				}

				m_stack->push(mp);

				c += size + FJ_INC;
				goto fast_jmp;
				break;
			}

			case OP_CLONE: {	
				PRINT2("\t\t%p : clone, %d\n", c, c[1]); 
				orcaObject* owner = NULL;
				d = m_stack->at(c[1]);
				
				if (is<TYPE_OBJ>(d)) {
					owner = d.o()->get_owner();
				}

				p1 = d.clone(owner);
				if (is<TYPE_OBJ>(p1)) {
					if (p1.o()->has_member("init", p2)) {
						m_stack->set(c[1], p2);
						// cause init refer p1 (by owner)
						// and it can gc on that
						p1.rc_inc();
						call(c[1]);
						p1.set_rc(p1.get_rc()-1);
					}
				}
				else {
					m_stack->dummy_pop(c[1]);
				}

				m_stack->replace(p1);

				c += 1 + 1;
				goto fast_jmp;
				break;
			  }

			case OP_LIST_AT:	
			case OP_LIST_AT_IR:	
				if ((unsigned char)*c == OP_LIST_AT_IR) {
					flag = true;
				}
				else {
					flag = false;
				}

				PRINT2("\t\t%p : list at (include right?: %d)\n", c, flag); 
				p2 = m_stack->pop();
				p1 = m_stack->pop();
				p3 = get_collection_at(p1, p2, flag, this);
				m_stack->push(p3);
				break;

			case OP_MAKE_PAIR: 
				PRINT1("\t\t%p : make pair\n", c); 
				p2 = m_stack->pop();
				p1 = m_stack->top();

				if (!isall<TYPE_INT>(p1, p2)) {
					m_stack->pop();
					throw orcaException(this, "orca.type", 
						string("invalid parameter for make pair : ") + 
						p1.dump_str() + ", " + p2.dump_str());
				}

				p3.pair_set(p1.i(), p2.i());
				m_stack->replace(p3);
				break;

			case OP_MAKE_REGEX: 
				PRINT1("\t\t%p : make regex\n", c); 
				p1 = m_stack->top();
				if (!is<TYPE_STR>(p1)) {
					m_stack->pop();
					throw orcaException(this, "orca.type", 
						string("invalid parameter for make regex : ") + p1.dump_str());
				}

				p2.re_set(p1.s());
				m_stack->replace(p2);
				break;

			case OP_RETURN:
				PRINT1("\t\t%p : return\n", c); 
				return;

			case OP_RETURN_NIL	:
				PRINT1("\t\t%p : return nil\n", c); 
				m_stack->push(NIL);
				return;
	
			case OP_FOR: {
				PRINT4("\t\t%p : for (lv: %d), %d, depth:%d\n", c, TO_SHORT(&c[1]), TO_INT(&c[1 + sizeof(short)]), m_for_stack->size()+1);
				int lv = TO_SHORT(&c[1]);
				int addr = TO_INT(&c[1 + sizeof(short)]);

				p1 = m_stack->pop();
				if (!is<TYPE_OBJ>(p1)) {
					throw orcaException(this, "orca.type", 
						string("abnormal type at for statement loop factor : ") + 
						p1.dump_str());
				}

				if (m_for_stack->push(c + sizeof(short) + sizeof(int), lv, p1.o(), d, m_curr) == false) {
					c = code + addr;
					goto fast_jmp;
				}

				m_local->set(lv, d);
				p2.mark_for();
				m_local->push_back(p2);

				c += sizeof(short) + sizeof(int) + FJ_INC;
				goto fast_jmp;
				break;
			}

			case OP_FOR_2: {
				orcaData out1, out2;
				PRINT5("\t\t%p : for2 (lv: %d, %d), %d, depth:%d\n", c, TO_SHORT(&c[1]), TO_SHORT(&c[1 + sizeof(short)]), TO_INT(&c[1 + sizeof(short) + sizeof(short)]), m_for_stack->size()+1);
				int lv1 = TO_SHORT(&c[1]);
				int lv2 = TO_SHORT(&c[1 + sizeof(short)]);
				int addr = TO_INT(&c[1 + sizeof(short) + sizeof(short)]);

				p1 = m_stack->pop();
				if (!is<TYPE_OBJ>(p1)) {
					throw orcaException(this, "orca.type", 
						string("abnormal type at for statement loop factor : ") + 
						p1.dump_str());
				}

				if (m_for_stack->push_2(c + sizeof(short) + sizeof(short) + sizeof(int), lv1, lv2, p1.o(), out1, out2, m_curr) == false) {
					
					c = code + addr;
					goto fast_jmp;
				}

				m_local->set(lv1, out1);
				m_local->set(lv2, out2);
				p2.mark_for();
				m_local->push_back(p2);

				c += sizeof(short) + sizeof(int) + FJ_INC;
				goto fast_jmp;
				break;
			}

			case OP_FOR_SUB: {
				PRINT3("\t\t%p : for sub (%d), %d\n", c, TO_SHORT(&c[1]), TO_INT(&c[1 + sizeof(short)]));
				int lv = TO_SHORT(&c[1]);
				int addr = TO_INT(&c[1 + sizeof(short)]);

				int per = m_stack->pop().Integer();	// per
				p1 = m_stack->pop();	// iter
				if (!is<TYPE_OBJ>(p1)) {
					throw orcaException(this, "orca.type", 
						string("abnormal type at for statement loop factor : ") + 
						p1.dump_str());
				}

				bool ret = m_for_stack->push_sub(c+sizeof(short)+sizeof(int), lv, p1.o(), d, m_curr, per);
				if (ret == false) {
					c = code + addr;
					goto fast_jmp;
				}

				m_local->set(lv, d);
				p2.mark_for();
				m_local->push_back(p2);

				c += sizeof(short) + sizeof(int) + FJ_INC;
				goto fast_jmp;
				break;
			}

			case OP_FOR_END: {		
				PRINT1("\t\t%p : for end\n", c); 
				int lv1;
				int lv2;
				
				m_local->cleanup_gc(false);
				const char* cont = m_for_stack->cont(&lv1, &p1, &lv2, &p2);
				if (cont != 0) { // continue
					m_local->set(lv1, p1);
					if (lv2 >= 0) {
						m_local->set(lv2, p2);
					}
					c = cont;
				}
				else {			// end
					m_for_stack->pop();
					m_local->clean_mark(MARK_FOR);
				}
				break;
			}

			case OP_FOR_POP:
				PRINT1("\t\t%p : for pop\n", c); 
				m_for_stack->pop();

				m_local->clean_mark(MARK_FOR);
				break;

			case OP_MARK_STACK:
				PRINT1("\t\t%p : mark stack\n", c); 
				p2.mark_stack();
				m_local->push_back(p2);
				break;

			case OP_MARK_STACK_POP:
				PRINT1("\t\t%p : mark stack pop\n", c); 
				m_stack->pop();
				m_local->clean_mark(MARK_STACK);
				break;

			case OP_DUMP_STACK: 
				m_stack->dump();
				break;

			case OP_DUMP_LOCAL: 
				m_local->dump();
				break;

			case OP_POP_STACK:
				PRINT1("\t\t%p : remove stack\n", c);
				if (g_parser->is_interactive() || g_parser->is_eval()) {
					g_last_pop_stack = m_stack->pop();
				}
				else {
					m_stack->dummy_pop();
				}
				break;

			case OP_POP_STACK_SILENT:
				PRINT1("\t\t%p : remove stack silently\n", c);
				m_stack->dummy_pop();
				break;

			case OP_THROW: 
				PRINT2("\t\t  throw: %s (%d)\n", &c[3], c[1]);
				m_cptr = NULL;
				m_cp = c;
				throw orcaException(this, &c[3], (int)c[1]);
				break;

			case OP_MARK_TRY: {
				PRINT1("\t\t  mark try: (to: %x)\n", TO_INT(&c[1]));
				CatchList* cp =  new CatchList(code + TO_INT(&c[1]), 
									TO_INT(&c[1+sizeof(int)]), m_curr); 
				p1.mark_catch(cp);
				m_local->push_back(p1);

				c += sizeof(int) + sizeof(int) + FJ_INC;
				goto fast_jmp;
				break;
			  }
			case OP_DONE_TRY: 
				PRINT0("\t\t  done try\n");
				d = m_local->get_mark(MARK_CATCH);
				delete (CatchList*)d.mark().vp;
				m_local->clean_mark(MARK_CATCH);
				break;

			case OP_SCOPE_START:
				PRINT1("\t\t%p : scope start\n", c);
				p1 = m_stack->top().Object()->get_member("{"); // check { if exists first
				d.mark_scope(m_stack->top().Object());
				m_local->push_back(d);
				m_stack->replace(p1);
				call(0);
				m_stack->dummy_pop();
				break;

			case OP_SCOPE_END:
				PRINT1("\t\t%p : scope end\n", c);
				p1 = m_local->get_mark(MARK_SCOPE);
				d = ((orcaObject*)p1.mark().vp)->get_member("}");
				m_stack->push(d);
				m_local->clean_mark(MARK_SCOPE);

				call(0);
				m_stack->dummy_pop();
				break;

			case OP_DECODE: 
				PRINT1("\t\t%p : decode start\n", c);
				p1 = m_stack->pop();
				m_decode_stack->push(p1);

				p2.mark_decode();
				m_local->push_back(p2);

				break;

			case OP_DECODE_END: 
				PRINT1("\t\t%p : decode end\n", c); 
				m_decode_stack->pop();
				m_local->clean_mark(MARK_DECODE);
				break;

			case OP_PATTERN_START:
				PRINT1("\t\t%p : pattern start\n", c); 
				m_decode_stack->set_next_pattern_addr(TO_INT(&c[1]));
				m_decode_stack->init_pattern();
				c += sizeof(int) + FJ_INC;
				goto fast_jmp;
				break;

			case OP_MATCH_EXPR:
				PRINT1("\t\t%p : match expr\n", c); 

				p2 = m_stack->pop();

				if (!m_decode_stack->match_expr(p2, -1)) {
					c = code + m_decode_stack->get_next_pattern_addr();
					goto fast_jmp;
				}

				break;

			case OP_MATCH_EXPR_W_SHIFT:
				PRINT1("\t\t%p : match expr with shift\n", c); 

				p2 = m_stack->pop();

				if (!m_decode_stack->
					  match_expr_shift(p2, -1, TO_SHORT(&c[1]) )) 
				{
					c = code + m_decode_stack->get_next_pattern_addr();
					goto fast_jmp;
				}

				c += sizeof(short) + FJ_INC;
				goto fast_jmp;
				break;
	
			case OP_MATCH_N_ASSIGN:
				PRINT1("\t\t%p : match and assign expr\n", c); 

				p2 = m_stack->pop();

				if (!m_decode_stack->match_expr(p2, TO_SHORT(&c[1]) )) {
					c = code + m_decode_stack->get_next_pattern_addr();
					goto fast_jmp;
				}

				c +=  sizeof(short) + FJ_INC;
				goto fast_jmp;
				break;

			case OP_MATCH_N_ASSIGN_W_SHIFT:
				PRINT1("\t\t%p : match and assign expr\n", c); 

				p2 = m_stack->pop();

				if (!m_decode_stack->
					  match_expr_shift(p2, TO_SHORT(&c[1+2]), TO_SHORT(&c[1]) )) 
				{
					c = code + m_decode_stack->get_next_pattern_addr();
					goto fast_jmp;
				}

				c +=  sizeof(short) + sizeof(short) + FJ_INC;
				goto fast_jmp;
				break;

			case OP_SHIFT_ALL:
				PRINT2("\t\t%p : shift all: %d\n", c, TO_SHORT(&c[1])); 
				p1 = m_decode_stack->get_tail();
				m_local->set(TO_SHORT(&c[1]), p1);
				
				c += sizeof(short) + FJ_INC;
				goto fast_jmp;
				break;

			case OP_CUT_LIST: 
				PRINT3("\t\t%p : cut list: %d:%d\n", 
						c, TO_SHORT(&c[1]), TO_SHORT(&c[1+2])); 

				p1 = m_decode_stack->get_pattern();

				flag = false;
				if (is<TYPE_OBJ>(p1)) {
					orcaVirtList* vp;
					orcaSbf* sp;
					orcaList* lp;

					if (islist(p1)) {
						lp = static_cast<orcaList*>(p1.o());
						if (lp->size() == 0) {
							m_local->set(TO_SHORT(&c[1]), new orcaList());
							m_local->set(TO_SHORT(&c[1 + 2]), new orcaList());

							flag = true;
						}
						else if (lp->size() == 1) {
							p2 = lp->at(0);
							m_local->set(TO_SHORT(&c[1]), p2 );
							m_local->set(TO_SHORT(&c[1 + 2]), new orcaList());

							flag = true;
						}
						else if (vp = dynamic_cast<orcaVirtList*>(p1.o())) {
							p2 = vp->at(0);
							
							m_local->set(TO_SHORT(&c[1]), p2 );
							m_local->set(TO_SHORT(&c[1 + 2]), vp->cut_head());

							flag = true;
						}
						else if (sp = dynamic_cast<orcaSbf*>(p1.o())) {
							p2 = sp->at(0);
							m_local->set(TO_SHORT(&c[1]), p2 );

							vp = new orcaVirtList();
							vp->init(sp);
							m_local->set(TO_SHORT(&c[1 + 2]), vp);

							flag = true;
						}
						else if (lp = dynamic_cast<orcaList*>(p1.o())) {
							p2 = lp->at(0);
							m_local->set(TO_SHORT(&c[1]), p2 );

							vp = new orcaVirtList();
							vp->init(lp);
							m_local->set(TO_SHORT(&c[1 + 2]), vp);
							m_decode_stack->set_iter(lp->end());
							flag = true;
						}
					}
				}

				if (flag == false) {
					c = code + m_decode_stack->get_next_pattern_addr();
					goto fast_jmp;
				}
				
				c += sizeof(short) + sizeof(short) + FJ_INC;
				goto fast_jmp;
				break;

			case OP_DECODE_CHECK_REMAIN:
				PRINT1("\t\t%p : check remain\n", c); 

				if (!m_decode_stack->check_remain()) {
					c = code + m_decode_stack->get_next_pattern_addr();
					goto fast_jmp;
				}

				break;

			case OP_SWITCH: 
				PRINT1("\t\t%p : switch start\n", c);
				p1 = m_stack->pop();
				m_switch_stack->push(p1);

				p2.mark_switch();
				m_local->push_back(p2);
				break;

			case OP_SWITCH_END: 
				PRINT1("\t\t%p : switch end\n", c); 
				m_switch_stack->pop();
				m_local->clean_mark(MARK_SWITCH);
				break;

			case OP_SWITCH_CASE: {
				PRINT2("\t\t%p : case pattern start (%d)\n", c, c[1]); 

				int count = c[1];
				bool found = false;
				for (int i=0; i<count; i++) {
					p1 = m_stack->pop();
					if (found) continue; // to consume remain stack

					if (m_switch_stack->compare(p1) == true) {
						found = true;
					}
				}

				if (found == false) {
					c = code + TO_INT(&c[2]);
					goto fast_jmp;
				}
				else {
					c += sizeof(char) + sizeof(int) + FJ_INC;
					goto fast_jmp;
				}

				break;
			}

			case OP_SBF: {
				PRINT4("\t\t%p : sbf: code: %d, gen: %d, rule: %d\n", 
						c, TO_INT(&c[1]), TO_INT(&c[1+sizeof(int)]),
						TO_INT(&c[1+2*sizeof(int)])); 

				orcaSbf* lp = new orcaSbf();
				int result = TO_INT(&c[1]);
				int gen = TO_INT(&c[1+sizeof(int)]);
				int rule = TO_INT(&c[1+sizeof(int)+sizeof(int)]);

				char* new_code = const_cast<char*>(code);
				if (g_parser->is_interactive() || g_parser->is_eval()) {
					int size = c - code;
					new_code = g_codes->new_code(size);
					memcpy(new_code, code, size);
				}

				lp->set_result(new_code + result);
				lp->set_code(new_code);
				lp->set_vm(this);

				c += 1 + 3 * sizeof(int);
				for(int i=0; i<gen; i++) {
					int addr = TO_INT(&c[i*sizeof(int)]);

					exec_code(new_code, new_code+addr);
					m_cptr = &c;

					p1 = m_stack->pop();
					if (p1.i() == 1) {
						p4 = m_stack->pop();
						p3 = m_stack->pop();
						p2 = m_stack->pop();
						p1 = m_stack->pop();

						lp->push_gen(p4.i(), p1, p2, p3);
					}
					else if (p1.i() == 2) {
						p2 = m_stack->pop();
						p1 = m_stack->pop();

						if (!dynamic_cast<orcaList*>(p1.Object())) {
							throw orcaException(this, "orca.type", "abnormal type for SBF");
						}

						lp->push_gen(p2.i(), static_cast<orcaList*>(p1.o()));
					}
				
				}
				c += gen * sizeof(int);
				
				for(int i=0; i<rule; i++) {
					int addr = TO_INT(&c[i*sizeof(int)]);
					lp->push_rule(new_code + addr);
				}
				c += rule * sizeof(int);

				m_stack->push(lp);

				//c += FJ_INC;	// already increased
				goto fast_jmp;
				break;
			  }

			case OP_PARALLEL_START:
				PRINT2("\t\t%p : parallel start: %d\n", c, TO_INT(&c[1])); 
				parallel_do(code, 1 + c + sizeof(int));

				c = code + TO_INT(&c[1]);
				goto fast_jmp;
				break;

			case OP_PARALLEL_END:
				PRINT1("\t\t%p : parallel end\n", c);
				return;
				break;

			case OP_PARALLEL_FOR: {
				PRINT3("\t\t%p : parallel for start: (lv:%d), %d\n", c, 
						TO_SHORT(&c[1]), TO_INT(&c[1 + sizeof(short)])); 

				short lv = TO_SHORT(&c[1]);
				/* int offset = TO_INT(&c[... */

				int per = m_stack->pop().Integer();
				int by = m_stack->pop().Integer();
				p1 = m_stack->pop();	// list
				if (!is<TYPE_OBJ>(p1)) {
					throw orcaException(this, "orca.type", 
						string("abnormal type at for statement loop factor: ") + 
						p1.dump_str());
				}

				orcaObject* iterator = NULL;
				orcaData next;

				orcaTuple* tp = NULL;
				orcaTupleIter* tit = NULL;

				orcaList* lp = NULL;
				orcaListIterator* lit = NULL;
				bool iterator_done = false;

				if (isobj<orcaTuple>(p1)) {
					tp = castobj<orcaTuple>(p1);
					iterator = tit = new orcaTupleIter(tp->begin(), tp, false);
				}
				else if (isobj<orcaList>(p1)) {
					lp = castobj<orcaList>(p1);
					iterator = lit = new orcaListIterator(lp->begin(), lp->begin(), lp->end(), false);
				}
				else {
					orcaData out;
					iterator = p1.o();
					if (iterator->has_member((char*)"iter", out) == true) {
						m_stack->push(out);
						call(0); // iter()
						iterator = m_stack->pop().Object();
					}

					if (iterator->has_member((char*)"next", next) == false) {
						throw orcaException(this, "orca.type", "not iteratable");
					}
				}

				int cpu_num = port_cpu_num();
				if (cpu_num == 1) cpu_num++; // at least 2

				if (by > 0) {
					cpu_num = by;
				}

				iterator->rc_inc();
				next.rc_inc();
				int run_count = 0;
				do {
					g_thread_pool->m_cond_mutex.lock();
					while (run_count >= cpu_num) {
						g_thread_pool->m_cond_done.wait(&g_thread_pool->m_cond_mutex);
					}
					g_thread_pool->m_cond_mutex.unlock();

					if (tit && tit->get_iter() == tp->end() ||
						lit && lit->get_iter() == lp->end() ||
						iterator_done == true)
					{
						g_thread_pool->m_cond_mutex.lock();
						while (run_count > 0) {
							g_thread_pool->m_cond_done.wait(&g_thread_pool->m_cond_mutex);
						}
						g_thread_pool->m_cond_mutex.unlock();
						break;
					}

					orcaObject* new_it = iterator->clone(NULL);
					parallel_for(code, c + 1 + sizeof(short) + sizeof(int),
								&run_count, new_it, per);

					int count = per;
					try {
						if (tit) {
							while (tit->get_iter() != tp->end() && count-- > 0) {
								tit->ex_next(this, 0);
							}
						}
						else if (lit) {
							while (lit->get_iter() != lp->end() && count-- > 0) {
								lit->ex_next(this, 0);
							}
						}
						else {
							while (count-- > 0) {
								m_stack->push(next);
								call(0); // iter.next();
								m_stack->pop();
							}
						}
					}
					catch (...) {
						iterator_done = true;
					}
				} while(true);

				iterator->rc_dec();
				next.rc_dec();

				c = code + TO_INT(&c[1 + sizeof(short)]);
				goto fast_jmp;
				break;
			}

			case OP_PARALLEL_CALL: {
				PRINT2("\t\t%p : parallel call (param: %d)\n", c, c[1]); 
				vector<orcaData> params;
				for (int i=0; i<c[1]; i++) {
					orcaData p = m_stack->pop();
					params.push_back(p);
				}

				orcaData f = m_stack->pop();
				parallel_call(f, params);

				c += 1 + FJ_INC;
				goto fast_jmp;
				break;
			}

			case OP_RC_INC: 
				PRINT1("\t\t%p : rc inc\n", c);
				m_stack->top().rc_inc();
				break;

			case OP_RC_DEC: 
				PRINT1("\t\t%p : rc dec\n", c);
				m_stack->top().rc_dec();
				break;

			case OP_CHANNEL_IN:
				PRINT2("\t\t%p : channel in check (jump to: %x)\n", c, TO_INT(&c[1]));
				d = m_stack->pop();
				p1 = channel_in(d);

				if (is<TYPE_NIL>(p1) == false) { // this ensure d is Object
					m_channel_stack.push_back(d.o());
					
					m_stack->push(p1); // "<-" function
					c += sizeof(int) + FJ_INC;
					goto fast_jmp;
				}
				else  {
					c = code + TO_INT(&c[1]);
					goto fast_jmp;
				}
				break;

			case OP_CHANNEL_OUT: {
				PRINT3("\t\t%p : channel out check (jump to: %x, count: %d)\n", c, TO_INT(&c[1]), TO_INT(&c[1+4]));
				d = m_stack->pop();
				int num = TO_INT(&c[1+sizeof(int)]);
				if (channel_out(d, num)) {
					c += sizeof(int) + sizeof(int) + FJ_INC;
					goto fast_jmp;
				}
				else  {
					c = code + TO_INT(&c[1]);
					goto fast_jmp;
				}
				break;
			  }

			case OP_EXTRACT: {
				PRINT1("\t\t%p : extract\n", c);
				p1 = m_stack->pop();

				orcaObject* o = NULL;

				if (isobj<orcaList>(p1) == true) {
					p2 = TO_LIST(p1.o())->ex_tuple(this, 0);
					o = p2.o();
				}
				else if (isobj<orcaTuple>(p1) == true) {
					o = p1.Object();
					o->rc_inc(); // rc_dec will be called by orcaLocal copy_from_stack
								 // (to process above case - generated by this opcode)
				}
				else {
					o = p1.o();
					if (o->has_member("->", p2) == false) {
						throw orcaException(this, "orca.type", "not extractable type");
					}

					if (is<TYPE_NIL>(p2)) {
						throw orcaException(this, "orca.type", "not extractable type");
					}

					m_stack->push(p2);
					m_stack->push(0);
					call(1);
					orcaData ret = m_stack->pop();

					if (isobj<orcaTuple>(ret)) {
						o = ret.o();
					}
					else {
						orcaTuple* tp = new orcaTuple();
						tp->push_back(ret);
						o = tp;
					}
				}

				d.extract_set(o);
				m_stack->push(d);
				break;
			  }

			case OP_SELECT_PREPARE: 
				PRINT1("\t\t%p : select prepare\n", c);
				m_select_stack->push();

				p2.mark_select();
				m_local->push_back(p2);
				break;

			case OP_SELECT_START: {
				PRINT1("\t\t%p : select start\n", c);
				SELECT *sp = m_select_stack->top();

				do {
					sp->mutex.lock();
					for (int i=0; i<sp->cases.size(); i++) {
						CASE *ca = &sp->cases[i];
						if (ca->src == NULL) { // default
							c = ca->code;
							sp->mutex.unlock();
							goto fast_jmp; // out from this loop
						}

						if (ca->src->has_member("size", d) == false) {
							sp->mutex.unlock();
							throw orcaException(this, "orca.select", string("unselectable item: ")
								+ ca->src->dump_str());
						}

						m_stack->push(d);
						call(0);
						if (m_stack->pop().Integer() <= 0) { // not ready yet
							continue;
						}

						if (channel_out(ca->src, ca->out_num)) {
							c = ca->code;
							sp->mutex.unlock();
							goto fast_jmp; // out from this loop
						}
						else {
							sp->mutex.unlock();
							throw orcaException(this, "orca.select", string("channel out failed: ")
								+ ca->src->dump_str());
						}
					}

					int maxfd = sp->efd;
					fd_set fd_rd;
					FD_ZERO(&fd_rd);
					FD_SET(sp->efd, &fd_rd);

					for (int i=0; i<sp->cases.size(); i++) {
						orcaSocket* so = dynamic_cast<orcaSocket*>(sp->cases[i].src);
						if (so) {
							int sock = so->get_handle();
							FD_SET(sock, &fd_rd);
							maxfd = max(maxfd, sock);
						}

						orcaSelector* sel = dynamic_cast<orcaSelector*>(sp->cases[i].src);
						if (sel) {
							int fd = sel->set_fd(&fd_rd);
							maxfd = max(maxfd, fd);
						}
					}

					g_select.regist(sp);
					sp->mutex.unlock();

					int ret = select(maxfd+1, &fd_rd, NULL, NULL, NULL);
					if (ret) {
						if (FD_ISSET(sp->efd, &fd_rd)) {
							uint64_t u;
							ret = read(sp->efd, &u, sizeof(uint64_t));
						}
					}

					sp->mutex.lock();
					g_select.unregist(sp);
					sp->mutex.unlock();
				} while(true);

				break;
			  }

			case OP_SELECT_END: 
				PRINT1("\t\t%p : select end\n", c); 
				m_select_stack->pop();
				m_local->clean_mark(MARK_SELECT);
				break;

			case OP_SELECT_CASE: {
				p1 = m_stack->pop();
				const char *nc = code + TO_INT(&c[1]);
				const char *ac = c + 1 + sizeof(int) + sizeof(char);
				unsigned char num = (unsigned char)c[1+sizeof(int)];
				PRINT4("\t\t%p : select case start: %p, %p, %d\n", c, nc, ac, num); 
				m_select_stack->push_case(p1.Object(), num, ac);
				c = nc;
				goto fast_jmp;
				break;
			  }

			case OP_SELECT_DEFAULT: {
				PRINT1("\t\t%p : select default start\n", c);
				const char *nc = code + TO_INT(&c[1]);
				const char *ac = c + 1 + sizeof(int);
				m_select_stack->push_case(NULL, 0, ac);
				c = nc;
				goto fast_jmp;
				break;
			  }

			case OP_SELECT_SIGNAL: {
				PRINT1("\t\t%p : channel signal\n", c);
				orcaObject* op = m_channel_stack[m_channel_stack.size() - 1];
				m_channel_stack.pop_back();
				channel_signal(op);
				break;
			  }

			default:
				throw orcaException(this, "orca.lang", "unknown opcode");
				break;
			}
		}
		catch (orcaException& e) {
			m_cptr = &c;
			do {
				d = handle_throw(e.who());
				if (is<TYPE_NIL>(d)) {
					break;
				}

				CatchList* cl = (CatchList*)d.mark().vp;
				catch_t* ct;
				ct = cl->compare(e.who());
				if (ct != NULL) {
					for (int i=1; i<ct->lv.size(); i++) {
						if (i > e.params.size()) {
							m_local->set(ct->lv[i], NIL);
						}
						else {
							m_local->set(ct->lv[i], e.params[i-1]);
						}
					}
 
					if (ct->lv[0] >= 0) { // set as NAME
						orcaExceptionObject* eo = new orcaExceptionObject();
						eo->e = e;	
						m_local->set(ct->lv[0], eo);
					}
					else {
						e.rc_dec(); // not refered by object
					}

					m_curr = cl->m_my;
					c = code + ct->address;
					cl->clear();	// to avoid re-catch in same block
	
					m_cptr = &c; // recover
					goto fast_jmp;
				}

				// delete push_backed exception (by mark try)
				m_local->clean_mark(MARK_CATCH);
				delete cl;

			} while (true);

			// not found.. on this frame
			throw e;
		}
		catch(...) {
			printf("unknown exception...\n");
		}
	}
}
/*}}}*/

orcaData orcaVM::do_context(const char* ctx_mod, const char* name, const char* cp, time_t last_write_time, vector<const char*>& params, map<string, int>& pos_map)/*{{{*/
{
	orcaData out;
	orcaObject* ctx_modp;
	bool ret;
	char buff[1024];
	strncpy(buff, ctx_mod, 1024);

	const char *o_name = strtok((char*)ctx_mod, ".");
	orcaObject* curr = g_root;
	while (o_name) {
		ret = curr->has_member(o_name, out);
		if (ret == false) {
			if (curr->has_member(".")) {
				out = curr->get_member(o_name);
			}
			else {
				printf("ERROR: module %s (for context) not found\n", o_name);
				return NIL;
			}
		}

		curr = out.Object();
		o_name = strtok(NULL, ".");
	}

	// set modp
	ctx_modp = curr;

	// set last write time
	orcaDatetime* ts = new orcaDatetime(last_write_time);

	// set params
	orcaTuple* tp = new orcaTuple(params.size());
	for (int i=0; i<params.size(); i++) {
		orcaData d = params[i];
		tp->update(i, d);
	}

	// set pos
	orcaMap *mp = new orcaMap();
	map<string, int>::iterator it;
	for (it = pos_map.begin(); it != pos_map.end(); ++it) {
		orcaData key = it->first;
		orcaData value = it->second;
		mp->update(key, value);
	}

	// now let's compile
	push_stack(ctx_modp);
	push_param(name);
	push_param(ts);
	push_param(cp);
	push_param(tp);
	push_param(mp);
	call(5);

	out = m_stack->pop();
	if (is<TYPE_OBJ>(out) == false) {
		throw orcaException(this, "orca.context", "context parser return invalid object");
	}

	return out;
}
/*}}}*/

static OrcaHeader read_header(FILE* fp_kw)/*{{{*/
{
	int ret;

	OrcaHeader header;
	fseek(fp_kw, 0, SEEK_SET);
	ret = fread(&header, 1, sizeof(header), fp_kw);
	header.magic = ntohl(header.magic);
	header.version = ntohl(header.version);
	header.def_size = ntohl(header.def_size);
	header.code_size = ntohl(header.code_size);
	header.debug_size = ntohl(header.debug_size);

	return header;
}
/*}}}*/

static FILE* open_check_kw_file(const string& candidate_path, const string& kw_path)/*{{{*/
{
	FILE* fp_kw = fopen(kw_path.c_str(), "rb");
	if (fp_kw == NULL) {
		return NULL;
	}

	if (fs::last_write_time(fs::path(candidate_path))			// check time
		> fs::last_write_time(fs::path(kw_path)))
	{
		fclose(fp_kw);
		return NULL;
	}
	else {												// check version
		OrcaHeader header = read_header(fp_kw);
		if (header.magic != MAGIC_NO || header.version != ORCA_VERSION) {
			fclose(fp_kw);
			return NULL;
		}
	}

	return fp_kw;
}
/*}}}*/

bool orcaVM::load_helper(const string& mod_name, const string& candidate_path,/*{{{*/
						 const string& sub_postfix, const string& kw_path,
						 orcaObject* owner, string owner_path)
{
	bool ret;

	if (sub_postfix != "orca") { // load for context compile
		// in case 'html.js' load html
		int idx = sub_postfix.find(".");
		if (idx > 0) {
			load(sub_postfix.substr(0, idx));
		}
		else {
			load(sub_postfix, g_root);
		}
	}

	FILE *fp_kw = open_check_kw_file(candidate_path, kw_path);
	if (fp_kw == NULL) {
		bool back = g_parser->is_interactive();
		g_parser->set_interactive(false);
		if (sub_postfix == "orca") {	
			ret = g_parser->parse(candidate_path);
		}
		else {
			ret = g_parser->parse_context_file(candidate_path, mod_name, sub_postfix);
		}
		g_parser->set_interactive(back);

		if (!ret) {
			printf("compile error: %s\n", candidate_path.c_str());
			return false;
		}

		fp_kw = fopen(kw_path.c_str(), "rb");
		if (fp_kw == NULL) {
			printf("compiled file '%s' open failed...\n", kw_path.c_str());
			exit(0);
		}
	}

	time_t last_write_time = fs::last_write_time(fs::path(kw_path));
	OrcaHeader header = read_header(fp_kw);
	char* define = g_codes->new_define(header.def_size);
	char* code = g_codes->new_code(header.code_size);
	ret = fread(define, 1, header.def_size, fp_kw);
	ret = fread(code, 1, header.code_size, fp_kw);

	if (sub_postfix == "orca") {
		for (int i=0; i<header.debug_size; i+=sizeof(int)*2) {
			int addr, line;
			char buff[128];
			char *tmp;

			ret = fread(&addr, 1, sizeof(int), fp_kw);
			ret = fread(&line, 1, sizeof(int), fp_kw);
			tmp = fgets(buff, sizeof(buff), fp_kw);
			m_debug[code + addr] = line;
			m_debug_line[code + addr] = buff;
		}

		m_debug_name[code] = candidate_path;
	}
	fclose(fp_kw);

	// and recursively define
	orcaObject* old_curr = m_curr;
	string parent_path = fs::path(candidate_path).parent_path().string();
	orcaObject* op = exec_define(define, header.def_size, code, owner, last_write_time, parent_path);

	string mod_path;
	if (owner_path == "") {
		mod_path = mod_name;
	}
	else if (mod_name == "CODE") {
		mod_path = owner_path;
	}
	else {
		mod_path = owner_path + "." + mod_name;
	}
	g_codes->regist_define(mod_path, define);
	g_codes->regist_code(mod_path, code, header.code_size);
	m_curr = old_curr;

	return true;
}
/*}}}*/

string orcaVM::find_file(const string& candidate_path, const string& mod_name)
{
	if (fs::exists(candidate_path)) {
		return candidate_path;
	}

	string parent_path = fs::path(candidate_path).parent_path().string();
	if (parent_path == "") parent_path = ".";
	if (!fs::exists(parent_path)) return "";

	fs::directory_iterator end, it(parent_path);
	for (; it != end; ++it) {
		string path = it->path().string();
		string basename = fs::path(path).filename().string();
		vector<string> toks = kyString::split(basename, ".", 2);
		if (toks.size() >= 2 && toks[0] == mod_name && toks[1] == "orca") {
			return path;
		}
	}

	return "";
}

void orcaVM::load_directory(const string& found_file, const string& mod_name, orcaObject* owner, string owner_path)
{
	orcaObject* op = new orcaObject();
	const char* cp = const_strdup(mod_name.c_str());
	op->set_name(cp);
	owner->insert_member(cp, op);

	fs::directory_iterator m_end, m_iter = fs::directory_iterator(found_file);
	for (; m_iter != m_end; ++m_iter) {
		string str = m_iter->path().string();

		if (fs::is_directory(*m_iter)) {
			if (str.substr(str.length()-5) != ".orca") continue; // skip normal directory
		}
		else {
			string base_name = fs::path(str).filename().string();
			if (base_name[0] == '.') continue; // skip hidden system file
		
			vector<string> toks = kyString::split(base_name, ".", 2);
			if (toks.size() < 2 || toks[1] != "orca") continue;
		}

		string new_owner_path = mod_name;
		if (owner_path != "") {
			new_owner_path = owner_path + "." + mod_name;
		}

		load(m_iter->path().string().c_str(), op, new_owner_path);
	}
}

bool orcaVM::load(const string& input_path, orcaObject* owner, string owner_path) /*{{{*/
{
	//printf(">> load: %s\n", input_path.c_str());
	string base_name;   // file basename from inputname (without directory)
	string mod_name;	// module name (not path) without suffix
	string main_postfix; // should be orca
	string sub_postfix;  // could be orca, html & others
	string kw_path;	    // result module path with .kw suffix
	string mod_path;	// module path without suffix

	base_name = fs::path(input_path).filename().string();
	mod_name = base_name.substr(0, base_name.find_first_of('.')); 
	string parent_path = fs::path(input_path).parent_path().string();
	mod_path = parent_path + "/" + mod_name;

	// #1. check if already loaded
	if (owner == NULL) owner = g_root;
	if (owner->has_member(mod_name.c_str())) {	// alreay loaded
		return true;
	}

	// #2. set candidate_path & find from current working directory
	string found_file  = find_file(input_path, mod_name);
	//printf(">> found in current: '%s'\n", found_file.c_str());

	// #3. find module from current & mod_pathes
	if (found_file == "") {
		// iterate module path and find
		vector<fs::path>::iterator it = m_module_path.begin();
		for(; it != m_module_path.end(); ++it) {
			string candidate_path = (*it).string() + "/" + mod_path;
			//printf(">> candidate: %s\n", candidate_path.c_str());
			found_file = find_file(candidate_path, mod_name);
			if (found_file != "") {
				break;
			}
		}
	}

	// #4. Try to cpp at last
	if (found_file == "") {
		if (load_cpp(input_path)) { // check cpp module 
			return true;
		}

		cout << "module " << input_path << " not exists" << endl;
		exit(0);
	}
	
	//printf(">> found: %s\n", found_file.c_str());
	// #5. make target path
	base_name = fs::path(found_file).filename().string();
	parent_path = fs::path(found_file).parent_path().string();
	if (parent_path.length() > 0) {
		kw_path = parent_path + "/" + mod_name + ".kw";
		mod_path = parent_path + "/" + mod_name;
	}
	else {
		kw_path = mod_name + ".kw";
		mod_path = mod_name;
	}

	// #6. set main_postfix, sub_postfix & kw_path.
	vector<string> toks = kyString::split(base_name, ".", 2);
	switch (toks.size())
	{
	case 3:	main_postfix = toks[1];
			sub_postfix = toks[2];
			break;
	case 2:	main_postfix = toks[1];
			sub_postfix = toks[1];
			break;
	case 1: main_postfix = "orca";
			sub_postfix = "orca";
			break;
	}

	if (main_postfix != "orca") {
		printf("load failed abnormal name: %s\n", input_path.c_str());
		return false;
	}

	// #7. load
	if (fs::is_directory(found_file)) {
		if (kyString::ends_with(found_file, ".orca")) {
			load_directory(found_file, mod_name, owner, owner_path);
		}
	}
	else {
		load_helper(mod_name, found_file, sub_postfix, kw_path, owner, owner_path);
	}

	// #8. do init_once
	if (mod_name == "CODE") {
		return true;
	}

	orcaObject* op = owner->get_member(mod_name.c_str()).o();
	orcaData init_once;
	if (op->has_member("init_once", init_once)) {
		try {
			m_stack->push(init_once);
			init_once.rc_inc();
			// cause init refer p1 (by owner)
			// and it can gc on that
			call(0);
			m_stack->dummy_pop();
			init_once.set_rc(init_once.get_rc()-1);
		}
		catch(orcaException& e) {
			printf("uncaught exception while module loading (at init_once): %s - %s\n", e.who(), e.what());
			cout << e.m_stack_trace << endl;
			m_stack->dump();
			m_local->dump();
			exit(-1);
		}
	}

	return true;
}
/*}}}*/

bool orcaVM::load_cpp(const string& mod_name) /*{{{*/
{
	if (g_root->has_member(mod_name.c_str())) {	// alreay loaded
		return true;
	}

	string mod_path = dl_get_filename(mod_name);
	DLHANDLE handle = dlopen(mod_path.c_str(), RTLD_NOW);

	if (handle == NULL) {
		return false;
	}

	typedef void* (*fp_t)(void);

	fp_t pfunc = (fp_t)dlsym(handle, (string("get_")+mod_name).c_str());
	if (pfunc == NULL) {
		throw orcaException(this, "orca.module", string("invalid module file") + mod_path);
	}

	orcaObject* obj = (orcaObject*)(*pfunc)();
	g_root->insert_member(const_strdup(mod_name.c_str()), obj);


	return true;
}
/*}}}*/

orcaData orcaVM::get_param(int idx)/*{{{*/
{
	return m_local->get(idx);
}
/*}}}*/

void orcaVM::need_param(int exp)/*{{{*/
{
	if (exp < 0) {
		throw orcaException(this, "orca.param", "insufficient parameters");
	}

	throw orcaException(this, "orca.param", kyString::sprintf("invalid param number. (required:%d)", exp));
}
/*}}}*/

void orcaVM::set_param(int i, orcaData d)/*{{{*/
{
	m_local->set(i, d);
}
/*}}}*/

void orcaVM::push_param(orcaData d)/*{{{*/
{
	m_stack->push(d);
}
/*}}}*/

void orcaVM::push_stack(orcaData d)/*{{{*/
{
	m_stack->push(d);
}
/*}}}*/

orcaData orcaVM::pop_stack()/*{{{*/
{
	return m_stack->pop();
}
/*}}}*/

void orcaVM::reserve_local()/*{{{*/
{
	int size = m_local->get_size();
	size /= 2;
	m_local->increase(size);
}
/*}}}*/
 
orcaData orcaVM::get_caller()/*{{{*/
{
	return m_local->get(IDX_CALLER);
}
 /*}}}*/

void orcaVM::set_caller(orcaObject* o)/*{{{*/
{
	m_local->force_set(IDX_CALLER, o);
	//m_local->set(IDX_CALLER, o);
}
/*}}}*/

orcaData orcaVM::channel_in(orcaData d)/*{{{*/
{
	if (is<TYPE_OBJ>(d) == false) {
		return NIL;
	}

	orcaObject* o = d.o();
	orcaData ret;
	if (o->has_member("<-", ret)) {
		if (is<TYPE_NIL>(ret)) {
			return NIL;
		}
		
		return ret;
	}
	else { // not exists
		return NIL;
	}

	return NIL;
}
/*}}}*/

bool orcaVM::channel_out(orcaData d, int num)/*{{{*/
{
	if (is<TYPE_OBJ>(d) == false) {
		return false;
	}

	orcaObject* o = d.o();
	orcaData ret, fun;
	if (o->has_member("->", fun) == false) {
		return false;
	} 

	if (is<TYPE_NIL>(fun)) {
		return false;
	}

	bool flag_argv = false;
	int param = num;
	if (num <= 0) { // indicate argv exists
		flag_argv = true;
		num *= -1;
		param = 0;
	}

	m_stack->push(fun);
	m_stack->push(param);
	call(1);
	ret = m_stack->pop();

	if (isobj<orcaTuple>(ret)) {
		orcaTuple* tp = TO_TUPLE(ret.o());
		int tsize = tp->size();

		if (flag_argv == true) { // make argv
			int argc = tsize - num;
			if (argc < 0) {
				argc = 0;
			}

			orcaTuple* argv = new orcaTuple(argc);
			for(int i=0; i<argc; i++) {
				argv->update(i, tp->at(num+i));
			}

			m_stack->push(argv);
		}

		for (int i=num-1; i>=0; i--) {
			if (i<tsize) {
				m_stack->push(tp->at(i));
			}
			else {
				m_stack->push(NIL);
			}
		}
	}
	else {
		if (flag_argv == true) {
			orcaTuple* argv = new orcaTuple();
			m_stack->push(argv); // empty tuple for argv, num not include argv
		}

		for (int i=0; i<num-1; i++) {
			m_stack->push(NIL);
		}

		m_stack->push(ret);
	}

	return true;
}
/*}}}*/

void orcaVM::channel_signal(orcaObject* op)/*{{{*/
{
	SELECT* sp = g_select.find_select(op);
	if (sp != NULL) {
		sp->signal();
	}
}
/*}}}*/

int orca_launch_module(orcaVM* vm, char* module, int argc, char** argv)/*{{{*/
{
	int ret;
	g_parser->set_interactive(false);

	g_parser->init();

	vm->m_module = g_root;
	vm->m_curr = g_root;

	fs::path cwd = fs::current_path();
	fs::path mod_path(module);
	bool flag_cd = false;

	if (mod_path.branch_path() != cwd) {
		ret = chdir(mod_path.branch_path().string().c_str());
		flag_cd = true;
	}

	if (vm->load(mod_path.filename().c_str()) == false) {
		cout << module << " compile error" << endl;
		if (flag_cd) {
			ret = chdir(cwd.string().c_str());
		}
		return 0;
	}

	string mod_name = mod_path.filename().string();
	if (mod_name.find(".") > 0) 
		mod_name = mod_name.substr(0, mod_name.find("."));

	vm->m_module = g_root->get_member(mod_name.c_str()).o();
	if (!vm->m_module) {
		cout << module << " does not exist" << endl;
		if (flag_cd) {
			ret = chdir(cwd.string().c_str());
		}

		return 0;
	}
	try {
		const char* cp = vm->m_module->get_code();
		int cursize = 1;
		if (cp != NULL) {
			cursize = ((CodeHeader*)(cp))->frame_size;
		}

		vm->m_local->set(IDX_CURSIZE, cursize);

		// set argv
		if (argc > 0) {
			orcaTuple* tp = new orcaTuple(argc);

			for(int i=0; i<argc; i++) {
				tp->update(i, argv[i]);
			}

			vm->m_local->set(0, tp);
		}

		(*vm->m_module)(vm, 0);
	}
	catch(orcaException& e) {
		if (flag_cd) {
			ret = chdir(cwd.string().c_str());
		}

		printf("uncaught exception: %s - %s\n", e.who(), e.what());
		cout << e.m_stack_trace << endl;
#if 0
		for (int i=0; i<e.params.size(); i++) {
			e.params[i].dump();
		}
		vm->m_stack->dump();
		vm->m_local->dump();
#endif

		exit(-1);
	}

	g_parser->cleanup();
	if (flag_cd) {
		ret = chdir(cwd.string().c_str());
	}
	return 1;
}
/*}}}*/

int orca_launch_interpreter(orcaVM* vm)/*{{{*/
{
	g_parser->set_interactive(true);
	vm->reserve_local();

	g_parser->init();

	vm->m_module = g_root;
	vm->m_curr = g_root;

	g_parser->interpret(vm);

	g_parser->cleanup();
	return 1;
}
/*}}}*/

OrcaHeader::OrcaHeader(int d, int c, int debug) /*{{{*/
{
	memset(this, 0x00, sizeof(OrcaHeader));
	strcpy(name, "orca");
	magic = htonl(MAGIC_NO);
	version = htonl(ORCA_VERSION);
	def_size = htonl(d);
	code_size = htonl(c);
	debug_size = htonl(debug);
}
/*}}}*/

orcaData get_collection_at(orcaData& src, orcaData& idx, bool ir, orcaVM* vm)/*{{{*/
{
	orcaData ret, d;

	if (is<TYPE_STR>(src)) {
		if (is<TYPE_INT>(idx)) {
			int i = idx.i();
			if (i < 0) {
				i += src.s().length();
			}
			if (i < 0 || i >=  src.s().length()) {
				throw orcaException(vm, "orca.index", string("out of index: ") + lexical_cast<string>(idx.i()));
			}
			ret.s_set(src.s().substr(i, 1));
		}
		else if (is<TYPE_PAIR>(idx)) {
			ret.s_set(orcaString::slice(src.s(), idx.sl().from, idx.sl().to, ir));
		}
		else {
			throw orcaException(vm, "orca.type", 
				string("invalid parameter at string index: ") + idx.dump_str());
		}
	}
	else if (isobj<orcaList>(src)) {
		if (is<TYPE_INT>(idx)) {
			ret = TO_LIST(src.o())->at(idx.i());
		}
		else if (is<TYPE_PAIR>(idx)) {
			ret = TO_LIST(src.o())->slice(idx.sl().from, idx.sl().to, ir);
		}
		else {
			throw orcaException(vm, "orca.type", 
				string("invalid parameter at list index: ") + idx.dump_str());
		}
	}
	else if (isobj<orcaTuple>(src)) {
		if (is<TYPE_INT>(idx)) {
			ret = TO_TUPLE(src.o())->at(idx.i());
		}
		else if (is<TYPE_PAIR>(idx)) {
			ret = TO_TUPLE(src.o())->slice(idx.sl().from, idx.sl().to, ir);
		}
		else {
			throw orcaException(vm, "orca.type", 
				string("invalid parameter at tuple index: ") + idx.dump_str());
		}
	}
	else if (isobj<orcaMap>(src)) {
		ret = TO_MAP(src.o())->at(idx);
	}
	else if (is<TYPE_OBJ>(src) && src.o()->has_member("[]", d)) {
		if (vm == NULL) {
			vm = get_current_vm();
		}

		vm->push_stack(d);
		vm->push_param(idx);
		vm->call(1);
		ret = vm->pop_stack();
	}
	else {
		throw orcaException(vm, "orca.type", 
			string("invalid indexible type object: ") + src.dump_str());
	}

	return ret;
}
/*}}}*/

bool set_collection_at(orcaData& src, orcaData& idx, orcaData& val, orcaData& out, bool ir, orcaVM* vm)/*{{{*/
{
	orcaData d;

	if (isobj<orcaList>(src)) {
		if (is<TYPE_INT>(idx)) {
			TO_LIST(src.o())->update(idx.i(), val);
		}
		else if (is<TYPE_PAIR>(idx)) {
			TO_LIST(src.o())->update_range(idx.sl().from, idx.sl().to, ir, val);
		}
		else {
			throw orcaException(vm, "orca.type", "invalid slice");
		}
	}
	else if (isobj<orcaTuple>(src)) {
		if (is<TYPE_INT>(idx)) {
			TO_TUPLE(src.o())->update(idx.i(), val);
		}
		else if (is<TYPE_PAIR>(idx)) {
			TO_TUPLE(src.o())->update_range(idx.sl().from, idx.sl().to, ir, val);
		}
		else {
			throw orcaException(vm, "orca.type", "invalid slice");
		}
	}
	else if (isobj<orcaMap>(src)) {
		TO_MAP(src.o())->update(idx, val);
	}
	else if (is<TYPE_OBJ>(src) && src.o()->has_member("[]=", d)) {
		if (vm == NULL) {
			vm = get_current_vm();
		}

		vm->push_stack(d);
		vm->push_param(idx);
		vm->push_param(val);
		vm->call(2);
		out = vm->pop_stack();
		return true;
	}
	else {
		throw orcaException(vm, "orca.type", "assignment target is abnormal");
	}

	return false;
}
/*}}}*/

