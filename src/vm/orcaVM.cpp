/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaVM.cpp - main orcaVM routine

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/


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
#include <boost/tokenizer.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
namespace fs = boost::filesystem;
#include <gmpxx.h>

#include "porting.h"

// common
#include "orcaGlobal.h"
#include "orca_opcode.h"

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
#include "orcaRoot.h"

// vm
#include "orcaLocal.h"
#include "orcaStack.h"
#include "orcaForStack.h"
#include "orcaDecodeStack.h"
#include "orcaException.h"
#include "orcaPure.h"
#include "orcaOnce.h"
#include "orcaParserObject.h"
#include "orcaObjectMembers.h"
#include "orcaObjectParents.h"

// parser
#include "parser_common.h"
#include "parserParse.h"

// core
#include "orcaPack.h"
#include "orcaDatetime.h"

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

	set_current_vm(this);
	NIL.set_type(TYPE_NIL);

	m_for_stack = new orcaForStack();
	m_local = new orcaLocal();
	m_decode_stack = new orcaDecodeStack(this);
	m_stack = new orcaStack(m_local);
	m_trace = new orcaTrace(this);
	m_pure = new orcaPure(this);
	m_once = new orcaOnce();
}
/*}}}*/

void orcaVM::cleanup()/*{{{*/
{
	delete m_for_stack;
	delete m_decode_stack;
	delete m_stack;
	delete m_local;
	delete m_trace;
	delete m_pure;
	delete m_once;
}
/*}}}*/

struct auto_trace/*{{{*/
{
	auto_trace(const char* name, orcaVM* vm, const char* filename, const char* cp) {
		vp = vm;
		vp->m_trace->push(name, cp);
	}

	~auto_trace() {
		vp->m_trace->pop();
	}

	orcaVM* vp;
};
/*}}}*/

orcaData orcaVM::invoke_internal_func(InternalFunction& in) /*{{{*/
{
	int code = in.idx;
	u_internal d = in.owner;
	orcaData r;

	switch(code) 
	{
	case FI_STR_LENGTH:	
		r = g_string.length(this, d.so->s);
		break;

	case FI_STR_FIND:	
		r = g_string.find(this, d.so->s); 
		break;

	case FI_STR_FIND_ALL:	
		r = g_string.find_all(this, d.so->s); 
		break;

	case FI_STR_STRIP:	
		r = g_string.strip(this, d.so->s); 
		break;

	case FI_STR_LSTRIP:	
		r = g_string.lstrip(this, d.so->s); 
		break;

	case FI_STR_REPLACE:	
		r = g_string.replace(this, d.so->s); 
		break;

	case FI_STR_RSTRIP:	
		r = g_string.rstrip(this, d.so->s); 
		break;

	case FI_STR_TO_INT:	
		r = g_string.integer(this, d.so->s); 
		break;

	case FI_STR_TO_FLOAT:	
		r = g_string.float_(this, d.so->s); 
		break;

	case FI_STR_TO_STR:	
		r = g_string.to_string(this, d.so->s); 
		break;

	case FI_STR_STARTSWITH:	
		r = g_string.starts_with(this, d.so->s); 
		break;

	case FI_STR_ENDSWITH:	
		r = g_string.ends_with(this, d.so->s); 
		break;

	case FI_STR_HASH:	
		r = g_string.hash(this, d.so->s); 
		break;

	case FI_STR_CHOMP:	
		r = g_string.chomp(this, d.so->s); 
		break;

	case FI_STR_PUSH_BACK:	
		g_string.push_back(this, d.so->s); 
		r.__so_set__(d.so);
		break;

	case FI_STR_CHAR:	
		r = g_string.char_(this, d.so->s); 
		break;

	case FI_STR_UPPER:	
		r = g_string.upper(this, d.so->s); 
		break;

	case FI_STR_LOWER:	
		r = g_string.lower(this, d.so->s); 
		break;

	case FI_INT_TO_INT:	
		r = g_integer.integer(this, d.i); 
		break;

	case FI_BN_TO_INT:	
		r = g_big_integer.integer(this, d.bo->bn); 
		break;

	case FI_INT_TO_STR:	
		r = g_integer.string_(this, d.i); 
		break;

	case FI_BN_TO_STR:	
		r = g_big_integer.string_(this, d.bo->bn); 
		break;

	case FI_INT_TO_FLOAT:	
		r = g_integer.float_(this, d.i); 
		break;

	case FI_BN_TO_FLOAT:	
		r = g_big_integer.float_(this, d.bo->bn); 
		break;

	case FI_FLOAT_TO_INT:	
		r = g_float.integer(this, d.r); 
		break;

	case FI_FLOAT_TO_FLOAT:	
		r = g_float.float_(this, d.r); 
		break;

	case FI_FLOAT_TO_STR:	
		r = g_float.string_(this, d.r); 
		break;

	case FI_BOOL_TO_STR:	
		r = g_boolean.string_(this, d.i); 
		break;

	case FI_BOOL_TO_INT:	
		r = g_boolean.integer(this, d.i); 
		break;

	case FI_BOOL_TO_FLOAT:	
		r = g_boolean.float_(this, d.i); 
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

void orcaVM::call(int param_n, const char* addr)/*{{{*/
{
#ifdef _VM_DEBUG_
	char buff[1024]; // for debug message
#endif
	orcaData f = m_stack->at(param_n);
	orcaData r;
	if (is<TYPE_INTERNAL>(f)) {
		PRINT1("\t\t  internal function called: %x\n", f.i());
		{{	auto_local al(param_n, m_local);

			m_local->copy_from_stack(m_stack, param_n);
			set_caller(m_curr);
			m_stack->pop();

			r = invoke_internal_func(f.internal());
			m_stack->push(r);
		}}
	}
	else if (is<TYPE_NATIVE>(f)) {
		PRINT0("\t\t  native code called\n");
		{{	auto_local al(param_n, m_local);

			m_local->copy_from_stack(m_stack, param_n);
			set_caller(m_curr);
			m_stack->pop();

			r = f.native_call(this, param_n);
			m_stack->push(r);
		}}
	}
	else if (is<TYPE_OBJ>(f)) {
#ifdef _VM_DEBUG_
		char buff[256];
		PRINT1("\t\t  object called: %s\n", f.o()->dump(buff));
#endif
		int inc_size=param_n;
		if (f.o()->m_code != NULL) {
			int frame_size = l2s(f.o()->m_code);
			if (frame_size > param_n) 
				inc_size = frame_size;
		}

		if (!f.o()->is_pure()) {
			{{	auto_local al(inc_size, m_local);

				m_local->copy_from_stack(m_stack, param_n);
				set_caller(m_curr);
				m_stack->pop();

				{{	auto_trace at(m_curr->get_name(), this, m_module->get_name(), addr); 
					m_trace->top_name = f.o()->get_name();
					orcaData ret = (*f.o())(this, param_n);
					m_local->mark_return(ret);
					m_stack->push(ret);
				}}
			}}
		}
		else {
			orcaData d;
			vector<orcaData> params;
			if (m_pure->find(f.o(), m_stack, param_n, d) == false) {
				{{	auto_local al(inc_size, m_local);

					for (int i=0; i<param_n; i++) params.push_back(m_stack->at(i));

					m_local->copy_from_stack(m_stack, param_n);
					set_caller(m_curr);
					m_stack->pop();

					{{	auto_trace at(m_curr->get_name(), this, m_module->get_name(), addr); 
						m_trace->top_name = f.o()->get_name();
						orcaData ret = (*f.o())(this, param_n);
						m_local->mark_return(ret);
						m_stack->push(ret);
					}}

					m_pure->add(f.o(), params, m_stack->top());
				}}
			}
			else {	// use stored
				for (int i=0; i<param_n+1; i++) {
					m_stack->pop();
				}

				m_stack->push(d);
			}
		}
	}
	else if (is<TYPE_TYPE>(f)) {
		{{	auto_local al(param_n, m_local);
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
		{{	auto_local al(param_n, m_local);

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
				orcaData f = o->get_member("scope_end");
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

orcaObject* orcaVM::exec_define(const char* c, int size, const char* code, orcaObject* parent, time_t last_write_time)/*{{{*/
{
	vector<orcaObject*> v;
	orcaObject* current = parent;
	orcaObject* o;
	orcaData d;
	int count, j;

	orcaObject* mod = NULL;

	if (current == NULL) current = g_root;

	for(int i=0; i<size; i++) {
		switch((unsigned char)c[i])
		{
		case OP_DEF_START: // this, flag, len, cp
			o = new orcaObject();
			o->make_original();
			d.o_set(o);
			d.o()->set_name(&c[i+1+1+1]);

			PRINT2("\t\t DEF start: %s, (%p)\n", &c[i+1+1+1], d.o());

			if (c[i+1] & BIT_DEFINE_STATIC)
				current->insert_static(d.o()->get_name(), d);
			else
				current->insert_member(d.o()->get_name(), d);

			d.o()->set_flag(c[i+1]);

			v.push_back(current);
			current = d.o();
			i += c[i+1+1] + 1;

			if (mod == NULL) mod = current;
			break;

		case OP_DEF_END:
			PRINT0("\t\t DEF END\n");
			o = v[v.size()-1];
			current = o;
			v.pop_back();
			break;

		case OP_REG: // this, flag, len, cp
			PRINT1("\t\t  regist orcaObject: %s\n", &c[i+1+1+1]);
			if (c[i+1] & BIT_DEFINE_STATIC)
				current->insert_static(&c[i+1+1+1], NIL);
			else
				current->insert_member(&c[i+1+1+1], NIL);

			i += c[i+1+1] + 1;
			break;

		case OP_DEF_CODE:
			PRINT1("\t\t  define code: %lld\n", TO_LONGLONG(&c[i+1]));
			current->m_code = code + TO_LONGLONG(&c[i+1]);
			i += sizeof(long long);
			break;

		case OP_DEF_INIT:
			PRINT1("\t\t  define init code: %lld\n", TO_LONGLONG(&c[i+1]));
			m_curr = current;
			exec_code (code, code + TO_LONGLONG(&c[i+1]));
			m_stack->dummy_pop();
			i += sizeof(long long);
			break;

		case OP_DEF_SUPER:
			PRINT2("\t\t  super define: %d, %x\n", c[i+1], TO_INT(&c[i+2]));
			exec_code(code + TO_INT(&c[i+2]));
			count = c[i+1];
			for(j=0; j<count; j++) {
				if (!is<TYPE_OBJ>(m_stack->top())) {
					throw orcaException(this, "orca.type", 
						string("parent ") + m_stack->pop().dump_str() + 
						" must be object type");
				}
				else {
					orcaObject* op = current->make_super(m_stack->pop().o());
					if (op->has_member("init", d)) {
						m_stack->push(d);
						d.rc_inc();
						// cause init refer p1 (by owner)
						// and it can gc on that
						call(0, code);
						m_stack->dummy_pop();
						d.set_rc(d.get_rc()-1);
					}
				}
			}
			i += 5;
			break;

		case OP_USING: {
				PRINT1("\t\t  using: %s\n", &c[i+2]);
				char buff[256];

				for(j=0; c[i+2 + j] != '.' && j<c[i+1]; j++) 
					buff[j] = c[i+2 + j];

				buff[j] = 0;
				if (load(buff) == false) {
					printf("module (%s) load failure\n", buff);
					throw orcaException(this, "orca.module", "module launch failure");
				}
			}
			i += c[i+1] + 1;
			break;

		case OP_USING_EXT: {
				PRINT2("\t\t  using external: %s, %s\n", &c[i+3], &c[i+2 + c[i+1] + 1]);

				char buff[256];
				const char *by = &c[i+2 + c[i+1]+1];

				for(j=0; c[i+3 + j] != '.' && j<c[i+1]; j++) 
					buff[j] = c[i+3 + j];

				buff[j] = 0;

				if (strcmp(by, "cpp") == 0) {
					load_cpp(buff);
				}
				else {
					throw orcaException(this, "orca.module", "unknown external parser");
				}
			}

			i += 1 + c[i+1] + 1 + c[i+2];
			break;

		case OP_PARSE: {
				orcaParserObject* op = new orcaParserObject(this);
				current->insert_member("parse", op);
				
				int width = TO_INT(&c[i+1]);
				int depth = TO_INT(&c[i+1 + sizeof(int)]);
				int rules = TO_INT(&c[i+1 + 2*sizeof(int)]);
				i += 3 * sizeof(int);

				PRINT2("\t\t  parse object: %d x %d\n", width, depth);
				// term, nonterm
				for (int j=0; j<width; j++) { 
					char type = c[i+1];
					i++;

					char is_re = 0;
					if (type == BNF_TERMINAL || type == BNF_WS) {
						is_re = c[i+1];
						i++;
					} 

					int len = c[i+1];
					i++;

					const char* str = &c[i+1];

					if (type == BNF_TERMINAL) {
						if (is_re) {
							op->push_re(str, j);
						}
						else {
							op->push_str(str, j);
						}
					}
					else if (type == BNF_WS) {
						if (is_re) {
							op->push_re_ws(str, j);
						}
						else {
							op->push_str_ws(str, j);
						}
					}
					else {
						op->push_nonterminal(str, j);
					}

					i += len+1;
				}

				// table
				op->resize_table(width + 1, depth);	// 1 for action
				for (int j=0; j<depth; j++) {
					for (int k=0; k<=width; k++) {

						char action = c[i+1];
						short to = TO_SHORT(&c[i+1+1]);
						i += 1 + sizeof(short);
						op->set_table(j, k, action, to);
					}
				}

				// rules
				for (int j=0; j<rules; j++) {
					short left = TO_SHORT(&c[i+1]);
					i += sizeof(short);
					short right = TO_SHORT(&c[i+1]);
					i += sizeof(short);
					op->new_rule(left, right);
				}
			}
			break;

		case OP_CONTEXT: {
				int mod_len = c[i+1];
				const char* mod = &c[i+2];

				int name_len = c[i+2+mod_len];
				const char* name = &c[i+2+mod_len+1];

				int code_len  = TO_INT(&c[i+2+mod_len+name_len+1]);
				const char* code = &c[i+2+mod_len+name_len+1+sizeof(int)];

				i += 1+1+sizeof(int)+mod_len+name_len+code_len;
				PRINT3("\t\t  context object: %s, %s, %s\n", mod, name, code);

				orcaData out = do_context(mod, name, code, last_write_time);
				current->insert_member(name, out);
			}

		} // switch
	} // for

	return mod;
}
/*}}}*/

THREAD_RET parallel_thread_entry(void* ap)/*{{{*/
{
	thread_arg_t arg = *(thread_arg_t*)ap;
	g_thread_pool.work(arg);
	return 0;
}
/*}}}*/

void orcaVM::parallel_do(const char* code, const char* offset, int* run_count, orcaObject* op, int per, bool is_iterator)/*{{{*/
{
	g_thread_pool.m_mutex_start.lock();

	static thread_arg_t arg;
	arg.vm_main = this;
	arg.code = code;
	arg.offset = offset;
	arg.run_count = run_count;
	arg.iter = op;
	arg.per = per;
	arg.is_iterator = is_iterator;

	bool ret = g_thread_pool.signal_restart(arg);
	if (ret == false) {
		pthread_create(&arg.tid, NULL, parallel_thread_entry, &arg); 
	}

	g_thread_pool.m_cond_start.wait(&g_thread_pool.m_mutex_start);
	g_thread_pool.m_mutex_start.unlock();
}
/*}}}*/

void orcaVM::exec_code(const char* code, const char* offset)/*{{{*/
{
	register const char *c;
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

	for(;;c++) {
fast_jmp:
		try {
			PRINT1("[%02x] ", (unsigned char)*c);
			switch((unsigned char)*c)
			{
			case OP_NOP:	
				PRINT1("\t\t%p : NOP\n", c);
				break;

			case OP_CALL: 
				PRINT2("\t\t%p : call (param: %d)\n", c, c[1]); 
				j = c[1];
				call(j, c);
				c += 1 + FJ_INC;
				goto fast_jmp;
				break; 

			case OP_CALL_: 
				PRINT2("\t\t%p : call fast (param: %d)\n", c, c[1]); 
				j = c[1];
				call(j, c);
				m_stack->dummy_pop();
				c += 1 + FJ_INC;
				goto fast_jmp;
				break; 

			case OP_ASSIGN_LOCAL:	
				PRINT2("\t\t%p : assign local (%d)\n", c, TO_SHORT(&c[1]));
				j = TO_SHORT(&c[1]);
				p1 = m_stack->pop();
				m_local->set(j, p1);
				m_stack->push(m_local->get(j));
				c += sizeof(short) + FJ_INC;
				goto fast_jmp;
				break;

			case OP_ASSIGN_LOCAL_:
				PRINT2("\t\t%p : assign local fast (%d)\n", c, TO_SHORT(&c[1]));
				j = TO_SHORT(&c[1]);
				p1 = m_stack->pop();
				m_local->set(j, p1);
				c += sizeof(short) + FJ_INC;
				goto fast_jmp;
				break;

			case OP_ASSIGN_MEMBER:	
				PRINT2("\t\t%p : assign member (%s)\n", c, &c[2]);
				p2 = m_stack->pop();
				p1 = m_stack->top();
				m_stack->replace( p1.o()->update_member(&c[2], p2) );
				c += c[1] + 1 + FJ_INC;
				goto fast_jmp;
				break;				

			case OP_ASSIGN_MEMBER_:	
				PRINT2("\t\t%p : assign member fast(%s)\n", c, &c[2]);
				p2 = m_stack->pop();
				p1 = m_stack->pop();
				p1.o()->update_member(&c[2], p2);
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
					if (p1.o()->m_owner) p1.o()->m_owner->rc_dec();
					p1.o()->m_owner = p2.o();
					p1.o()->m_owner->rc_inc();
					break;

				case OP_PUSH_CALLER:
					set_caller(p2.o());
					break;
				}

				c += 1 + FJ_INC;
				goto fast_jmp;
				break;				

			case OP_ASSIGN_RESERVED_:
				PRINT2("\t\t%p : assign reserved (%d)\n", c, c[1]);
				p2 = m_stack->pop();
				p1 = m_stack->pop();
				switch(c[1])
				{
				case OP_PUSH_OWNER:
					if (p1.o()->m_owner) p1.o()->m_owner->rc_dec();
					p1.o()->m_owner = p2.o();
					p1.o()->m_owner->rc_inc();
					break;

				case OP_PUSH_CALLER:
					set_caller(p2.o());
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
				goto do_assign_list; // pros & cons

			case OP_ASSIGN_LIST_:	
			case OP_ASSIGN_LIST_IR_:	
				if ((unsigned char)*c == OP_ASSIGN_LIST_IR_)
					flag = true;
				else
					flag = false;

				PRINT2("\t\t%p : assign list (include right?: %d)\n", c, flag);

				p3 = m_stack->pop();
				p2 = m_stack->pop();
				p1 = m_stack->pop();

do_assign_list:
				if (isobj<orcaList>(p1)) {
					if (is<TYPE_INT>(p2)) {
						TO_LIST(p1.o())->update(p2.i(), p3);
					}
					else if (is<TYPE_PAIR>(p2)) {
						TO_LIST(p1.o())->update_range(p2.sl().from, p2.sl().to, flag, p3);
					}
					else {
						throw orcaException(this, "orca.type", "invalid slice");
						break;
					}
				}
				else if (isobj<orcaTuple>(p1)) {
					if (is<TYPE_INT>(p2)) {
						TO_TUPLE(p1.o())->update(p2.i(), p3);
					}
					else if (is<TYPE_PAIR>(p2)) {
						TO_TUPLE(p1.o())->update_range(p2.sl().from, p2.sl().to, flag, p3);
					}
					else {
						throw orcaException(this, "orca.type", "invalid slice");
						break;
					}
				}
				else if (isobj<orcaMap>(p1)) {
					TO_MAP(p1.o())->update(p2, p3);
				}
				else if (is<TYPE_OBJ>(p1) && p1.o()->has_member("[]=", d)) {
					if ((unsigned char)*c == OP_ASSIGN_LIST || 
						(unsigned char)*c == OP_ASSIGN_LIST_IR )
					{
						m_stack->replace(d);
					}
					else {
						m_stack->push(d);
					}
					m_stack->push(p2);
					m_stack->push(p3);
					call(2, c);
					break;
				}
				else {
					throw orcaException(this, "orca.type", "assignment target is abnormal");
					break;
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

			case OP_DUP:
				PRINT1("\t\t%p : dup\n", c);
				m_stack->dup();
				break;

			case OP_DUP2:
				PRINT1("\t\t%p : dup2\n", c);
				m_stack->dup2();
				break;

			case OP_NOT:
				PRINT1("\t\t%p : not\n", c);
				if (m_stack->pop().i() == 1) {
					m_stack->push(false);
				}
				else {
					m_stack->push(true);
				}
				
				break;

			case OP_JMP_TRUE:	
				PRINT2("\t\t%p : jmp if true (to: %x)\n", c, TO_INT(&c[1]));
				if (m_stack->pop().i() == 1) {
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
				if (m_stack->pop().i() == 0) {
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
					if (strcmp(&c[2], "type") == 0)
					{
						d.type_set(p1);
					}
					else if (strcmp(&c[2], "typename") == 0 ||  
							 strcmp(&c[2], "name") == 0)
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
					else if (strcmp(&c[2], "id") == 0) {
						d = p1.id();
					}
					else if (strcmp(&c[2], "rc") == 0) {
						d = p1.get_rc();
					}
					else if (strcmp(&c[2], "members") == 0) {
						orcaObjectMembers* mp = new orcaObjectMembers(p1);
						d = mp;
					}
					else if (strcmp(&c[2], "static_members") == 0) {
						orcaObjectMembers* mp = new orcaObjectMembers(p1);
						mp->set_static();
						d = mp;
					}
					else if (strcmp(&c[2], "parents") == 0) {
						orcaObjectParents* pp = new orcaObjectParents(p1);
						d = pp;
					}
					else if (strcmp(&c[2], "original") == 0) {
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
									throw orcaException(this, "orca.type",
														string("find member (") +
														&c[2] + ") from nil ");
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
					for(j=0; j<len; j++) 
						lp->push_front(m_stack->pop());
				}
				else if (len < 0) {
					if (len == -3)
						p3 = m_stack->pop();
					else
						p3 = 1;

					p2 = m_stack->pop();
					p1 = m_stack->pop();

					d = 0;
					if (p3 <= d)
						throw orcaException(this, "orca.list", "list step is invalid (plus value required)");

					if (p1 < p2) {
						for(d=p1; d<=p2; d = d + p3) 
							lp->push_back(d);
					}
					else {
						for(d=p1; d>=p2; d = d - p3) 
							lp->push_back(d);
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


				orcaTuple* tp;
				if (len > 0) {
					tp = new orcaTuple(len);
					for (j=len-1; j>=0; j--) {
						orcaData d = m_stack->top();
						tp->update(j, d);
						m_stack->pop();
					}
				}
				else if (len < 0) {
					tp = new orcaTuple();
					if (len == -3)
						p3 = m_stack->pop();
					else
						p3 = 1;

					p2 = m_stack->pop();
					p1 = m_stack->pop();

					d = 0;
					if (p3 <= d)
						throw orcaException(this, "orca.tuple", "tuple step is invalid (plus value required)");

					if (p1 < p2) {
						for(d=p1; d<=p2; d = d + p3)
							tp->push_back(d);
					}
					else {
						for(d=p1; d>=p2; d = d - p3)
							tp->push_back(d);
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
						call(c[1], c);
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
				if ((unsigned char)*c == OP_LIST_AT_IR)
					flag = true;
				else
					flag = false;

				PRINT2("\t\t%p : list at (include right?: %d)\n", c, flag); 

				p1 = m_stack->at(1);
				p2 = m_stack->top();

				if (is<TYPE_STR>(p1)) {
					if (is<TYPE_INT>(p2)) {
						int idx = p2.i();
						if (idx < 0) {
							idx += p1.s().length();
						}
						if (idx < 0 || idx >=  p1.s().length()) {
							throw orcaException(this, "orca.index", string("out of index: ") + lexical_cast<string>(p2.i()));
						}
						p3.s_set(p1.s().substr(idx, 1));
					}
					else if (is<TYPE_PAIR>(p2))
					
						p3.s_set(orcaString::slice(p1.s(), p2.sl().from, p2.sl().to, flag));
					else {
						m_stack->pop();
						m_stack->pop();
						throw orcaException(this, "orca.type", 
							string("invalid parameter at string index: ") + p2.dump_str());
					}
				}
				else if (isobj<orcaList>(p1)) {
					if (is<TYPE_INT>(p2))
						p3 = TO_LIST(p1.o())->at(p2.i());
					else if (is<TYPE_PAIR>(p2))
						p3 = TO_LIST(p1.o())->slice(p2.sl().from, p2.sl().to, flag);
					else {
						m_stack->pop();
						m_stack->pop();
						throw orcaException(this, "orca.type", 
							string("invalid parameter at list index: ") + p2.dump_str());
					}
				}
				else if (isobj<orcaTuple>(p1)) {
					if (is<TYPE_INT>(p2))
						p3 = TO_TUPLE(p1.o())->at(p2.i());
					else if (is<TYPE_PAIR>(p2))
						p3 = TO_TUPLE(p1.o())->slice(p2.sl().from, p2.sl().to, flag);
					else {
						m_stack->pop();
						m_stack->pop();
						throw orcaException(this, "orca.type", 
							string("invalid parameter at tuple index: ") + p2.dump_str());
					}
				}
				else if (isobj<orcaMap>(p1)) {
					p3 = TO_MAP(p1.o())->at(p2);
				}
				else if (is<TYPE_OBJ>(p1) && p1.o()->has_member("[]", d)) {
					m_stack->set(1, d);
					call(1, c);
					break;
				}
				else {
					m_stack->pop();
					m_stack->pop();
					throw orcaException(this, "orca.type", 
						string("invalid list type object: ") + p1.dump_str());
				}

				m_stack->pop();
				m_stack->replace(p3);
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
				PRINT3("\t\t%p : for (%d), %d\n", c, TO_SHORT(&c[1]), TO_INT(&c[1 + sizeof(short)]));
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

			case OP_FOR_SUB: {
				PRINT3("\t\t%p : for sub (%d), %d\n", c, TO_SHORT(&c[1]), TO_INT(&c[1 + sizeof(short)]));
				int lv = TO_SHORT(&c[1]);
				int addr = TO_INT(&c[1 + sizeof(short)]);

				p3 = m_stack->pop();	// is_iterator
				p2 = m_stack->pop();	// per
				p1 = m_stack->pop();	// iter
				if (!is<TYPE_OBJ>(p1)) {
					throw orcaException(this, "orca.type", 
						string("abnormal type at for statement loop factor : ") + 
						p1.dump_str());
				}

				if (m_for_stack->push_sub(c + sizeof(short) + sizeof(int), lv, p1.o(), d, m_curr, p2.Integer(), p3.Boolean()) == false) {
					
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
				int lv;
				const char* cont = m_for_stack->cont(&lv, &d);
				if (cont > 0) { // continue
					m_local->set(lv, d);
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
				if (is_interactive()) {
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
				d.mark_scope(m_stack->top().o());
				m_local->push_back(d);

				d = m_stack->top().o()->get_member("scope_start");
				m_stack->replace(d);
				call(0, c);
				m_stack->dummy_pop();
				break;

			case OP_SCOPE_END:
				PRINT1("\t\t%p : scope end\n", c);
				p1 = m_local->get_mark(MARK_SCOPE);
				d = ((orcaObject*)p1.mark().vp)->get_member("scope_end");
				m_stack->push(d);
				m_local->clean_mark(MARK_SCOPE);

				call(0, c);
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

			case OP_SBF: 
			  {
				PRINT4("\t\t%p : sbf: code: %d, gen: %d, rule: %d\n", 
						c, TO_INT(&c[1]), TO_INT(&c[1+sizeof(int)]),
						TO_INT(&c[1+2*sizeof(int)])); 

				orcaSbf* lp = new orcaSbf();
				int result = TO_INT(&c[1]);
				int gen = TO_INT(&c[1+sizeof(int)]);
				int rule = TO_INT(&c[1+sizeof(int)+sizeof(int)]);

				char* new_code = const_cast<char*>(code);
				if (is_interactive()) {
					int size = c - code;
					new_code = g_codes.new_code(size);
					memcpy(new_code, code, size);
				}

				lp->set_result(new_code + result);
				lp->set_code(new_code);
				lp->set_vm(this);

				c += 1 + 3 * sizeof(int);
				for(int i=0; i<gen; i++) {
					int addr = TO_INT(&c[i*sizeof(int)]);

					exec_code(new_code, new_code+addr);
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
				PRINT3("\t\t%p : parallel for start: %d\n", c, 
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
				orcaTupleIter* tit = NULL;
				orcaListIterator* lit = NULL;
				orcaTuple* tp = NULL;
				orcaList* lp = NULL;
				bool iterator_done = false;
				bool is_iterator = true;

				if (isobj<orcaTuple>(p1)) {
					tp = castobj<orcaTuple>(p1);
					iterator = tit = new orcaTupleIter(tp->begin(), tp);
					is_iterator = false;
				}
				else if (isobj<orcaList>(p1)) {
					lp = castobj<orcaList>(p1);
					iterator = lit = new orcaListIterator(lp->begin(), lp->begin(), lp->end());
					is_iterator = false;
				}
				else {
					iterator = p1.o();
				}

				int cpu_num = port_cpu_num();
				if (cpu_num == 1) cpu_num++; // at least 2

				if (by > 0) {
					cpu_num = by;
				}

				int run_count = 0;
				do {
					g_thread_pool.m_mutex_done.lock();
					while (run_count >= cpu_num) {
						g_thread_pool.m_cond_done.wait(&g_thread_pool.m_mutex_done);
					}
					g_thread_pool.m_mutex_done.unlock();

					if (tit && tit->get_iter() == tp->end() ||
						lit && lit->get_iter() == lp->end() ||
						iterator_done == true)
					{
						g_thread_pool.m_mutex_done.lock();
						while (run_count > 0) {
							g_thread_pool.m_cond_done.wait(&g_thread_pool.m_mutex_done);
						}
						g_thread_pool.m_mutex_done.unlock();

						if (tit) delete tit;
						if (lit) delete lit;
						break;
					}

					orcaObject* new_iterator = iterator->clone(NULL);
					parallel_do(code, c + 1 + sizeof(short) + sizeof(int),
								&run_count, new_iterator, per, is_iterator);

					int count = per;
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
						orcaData next, value;
						if (iterator->has_member((char*)"next", next) == false) {
							throw orcaException(this, "orca.type",
												string("not iteratable type ") + 
												iterator->dump_str());
						}

						try {
							while (count-- > 0) {
								m_stack->push(next);
								call(0); // iter.next();
								call(0); // iter()
								m_stack->pop();
							}
						}
						catch (...) {
							iterator_done = true;
						}
					}
				} while(true);

				c = code + TO_INT(&c[1 + sizeof(short)]);
				goto fast_jmp;
				break;
			}

			case OP_PARSE_INIT: {
				PRINT1("\t\t%p : parse init start\n", c);
				int addr = TO_INT(&c[1]);

				orcaParserObject* op = 
					dynamic_cast<orcaParserObject*>(m_curr->get_member("parse").Object());
				if (op == NULL) {
					throw orcaException(this, "orca.parse", "invalid parsing object");
				}

				if (op->get_action_size() > 0) {
					// maybe, already set up
					c  = code + addr;
					goto fast_jmp;
				}

				c += 1 + sizeof(int);
				goto fast_jmp;
				break;
			}

			case OP_PARSE: {
				PRINT2("\t\t%p : parse start (actions: %d)\n", c, TO_SHORT(&c[1]));
				short actions = TO_SHORT(&c[1]);

				orcaParserObject* op = 
					dynamic_cast<orcaParserObject*>(m_curr->get_member("parse").Object());
				if (op == NULL) {
					throw orcaException(this, "orca.parse", "invalid parsing object");
				}

				if (op->get_action_size() == 0) {
					PRINT1("  parsing actions setup: %d\n", actions);
					op->resize_action(actions);
					for (int i=actions-1; i>=0; i--) {
						op->set_action(i, m_stack->pop().Object());
					}
				}

				p1 = m_stack->pop(); // parameter
				p2 = m_curr->get_member("parse");
				m_stack->push(p2);
				m_stack->push(p1);
				call(1);
				c += 1 + sizeof(short);
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

			case OP_ONCE: {
				PRINT2("\t\t%p : once start (id: %d)\n", c, TO_INT(&c[1]));
				int id = TO_INT(&c[1]);
				int addr = TO_INT(&c[1 + sizeof(int)]);
				// check
				if (m_once->find(m_module, id, d)) {
					m_stack->push(d);
					c = code + addr;
					goto fast_jmp;
				}

				c += 1 + sizeof(int) + sizeof(int);
				goto fast_jmp;
				break;
			  }

			case OP_ONCE_END: {
				PRINT2("\t\t%p : once end (id: %d)\n", c, TO_INT(&c[1]));
				int id = TO_INT(&c[1]);
				m_once->add(m_module, id, m_stack->top());

				c += 1 + sizeof(int);
				goto fast_jmp;
				break;
			  }

			default:
				PRINT2("\t\t%p : UNKNOWN: %x\n", c, *c); 
				break;
			}
		}
		catch (orcaException& e) {
			do {
				d = handle_throw(e.who());
				if (is<TYPE_NIL>(d)) {
					break;
				}

				CatchList* cl = (CatchList*)d.mark().vp;
				catch_t* ct;
				ct = cl->compare(e.who());
				if (ct != NULL) {
					for(int i=e.argc()-1; i>=0; i--) {
						if (i >= ct->lv.size()) {
							m_stack->pop();
							continue;
						}
						m_local->set(ct->lv[i], m_stack->pop());
					}

					m_curr = cl->m_my;
					c = code + ct->address;
					cl->clear();	// to avoid re-catch in same block
	
					goto fast_jmp;
				}
				else {
					for(int i=e.argc()-1; i>=0; i--) {
						m_stack->pop();
					}
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

orcaData orcaVM::do_context(const char* mod, const char* name, const char* cp, time_t last_write_time)/*{{{*/
{
	orcaData out;
	orcaObject* modp;
	bool ret;

	ret = g_root->has_member(mod, out);
	if (ret == false) return NIL;
	modp = out.Object();

	// set last write time
	orcaDatetime* dp = new orcaDatetime(last_write_time);

	// now let's compile
	push_stack(modp);
	push_param(name);
	push_param(dp);
	push_param(cp);
	call(3);

	return m_stack->pop();
}
/*}}}*/

static OrcaHeader read_header(FILE* fp_kw)/*{{{*/
{
	OrcaHeader header;
	fseek(fp_kw, 0, SEEK_SET);
	fread(&header, 1, sizeof(header), fp_kw);
	header.magic = ntohl(header.magic);
	header.version = ntohl(header.version);
	header.def_size = ntohl(header.def_size);
	header.code_size = ntohl(header.code_size);
	header.debug_size = ntohl(header.debug_size);

	return header;
}
/*}}}*/

bool orcaVM::load(const string& input_name, orcaObject* parent) /*{{{*/
{
	time_t last_write_time;

	string mod_wo_suffix;	// module name (not path) without suffix
	string mod_path;	// result module path (with suffix)
	string once_path;	// result once path (with suffix)
	string new_name;	// source file path (with or without suffix)

	if (parent == NULL) parent = g_root;
	mod_wo_suffix = fs::path(input_name).filename().string();

	mod_wo_suffix = mod_wo_suffix.substr(0, mod_wo_suffix.find_first_of('.')); 
	if (parent->has_member(mod_wo_suffix.c_str())) {	// alreay loaded
		return true;
	}

	// ## mod.orca -> mod.kw, mod -> mod.kw/*{{{*/
	int last_idx = input_name.find_last_of('.');
	if (last_idx > 1) {
		mod_path = input_name.substr(0, last_idx) + ".kw";
	}
	else {
		mod_path = input_name + ".kw";
	}/*}}}*/

	// ## name -> name.orca/*{{{*/
	fs::path new_path = new_name = input_name;
	if (!fs::exists(new_path)) {	// if not, change name ( + .orca)
		new_name += ".orca";
		new_path = new_name;
	}/*}}}*/

	// find module
	if (!fs::exists(new_path)) {
		bool flag = false;/*{{{*/

		// iterate module path and find
		vector<fs::path>::iterator it = m_module_path.begin();
		for(; it != m_module_path.end(); ++it) {
			new_name = (*it).string() + "/" + mod_wo_suffix;
			mod_path = new_name + ".kw";
			new_path = new_name;

			if (!fs::exists(new_path)) {
				new_name += ".orca";
				new_path = new_name;
			}

			if (fs::exists(new_path)) {
				flag = true;
				break;
			}
		}

		if (flag == false) {
			if (load_cpp(input_name)) // check cpp module 
				return true;

			cout << input_name << " not exists" << endl;
			exit(0);
		}/*}}}*/
	}


	if (fs::is_directory(new_path)) {
		orcaObject* op = new orcaObject();/*{{{*/

		if (fs::exists(new_path / "init_once.orca")) {
			const char* cp = const_strdup(mod_wo_suffix.c_str());
			op->set_name(cp);
			parent->insert_member(cp, op);

			fs::directory_iterator m_end, m_iter = fs::directory_iterator(new_path);
			for (; m_iter != m_end; ++m_iter) {
				if (m_iter->path().string()[0] == '.') continue;
				if (!fs::is_directory(*m_iter)) {
					string str = m_iter->path().string();
					if (str.substr(str.length()-5) != ".orca")
						continue;
				}

				load(m_iter->path().string().c_str(), op);
			}
		}
/*}}}*/
	}
	else {
		bool need_recompile = false;/*{{{*/

		FILE *fp_kw = fopen(mod_path.c_str(), "rb");
		if (fp_kw == NULL)  {
			need_recompile = true;
		}
		else {
			if (fs::last_write_time(fs::path(new_name))			// check time
				> fs::last_write_time(fs::path(mod_path)))
			{
				need_recompile = true;
			}
			else {												// check version
				OrcaHeader header = read_header(fp_kw);
				if (header.magic != MAGIC_NO || header.version != ORCA_VERSION) 
					need_recompile = true;
			}
		}

		if (need_recompile) {
			if (fp_kw) fclose(fp_kw);

			bool back = is_interactive();
			set_interactive(false);
			bool ret = parse(new_name);
			set_interactive(back);

			if (!ret) {
				cout << "compile error: " << input_name << endl;
				return false;
			}

			fp_kw = fopen(mod_path.c_str(), "rb");
		}

		if (fp_kw == NULL) {
			printf("file open failure...\n");
			exit(0);
		}

		last_write_time = fs::last_write_time(fs::path(mod_path));
			
		once_path = complete(new_path).string() + ".once";

		OrcaHeader header = read_header(fp_kw);
		char* define = g_codes.new_define(header.def_size);
		char* code = g_codes.new_code(header.code_size, mod_wo_suffix);
		fread(define, 1, header.def_size, fp_kw);
		fread(code, 1, header.code_size, fp_kw);

		// read debug info
		for (int i=0; i<header.debug_size; i+=sizeof(int)*2) {
			int addr, line;
			char buff[128];

			fread(&addr, 1, sizeof(int), fp_kw);
			fread(&line, 1, sizeof(int), fp_kw);
			fgets(buff, sizeof(buff), fp_kw);
			m_debug[code + addr] = line;
			m_debug_line[code + addr] = buff;
		}

		m_debug_name[code] = new_path.string();
		fclose(fp_kw);

		// and recursively define
		orcaObject* op = exec_define(define, header.def_size, code, parent, last_write_time);
		m_once->reg(op, once_path);

		// read once if possible
		portFile f_once;
		if (!need_recompile && f_once.open(once_path)) {
			char* buff = f_once.read();
			char* src = buff;
			orcaData d = g_pack->load(&buff);
			m_once->load(op, (orcaMap*)d.Object());

			delete[] src;
			f_once.close();
		}
/*}}}*/
	}

	// ## do init_once/*{{{*/
	orcaObject* op = parent->get_member(mod_wo_suffix.c_str()).o();
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
			printf("uncaugted exception while module loading (at init_once): %s - %s\n", e.who(), e.what());
			cout << e.m_stack_trace << endl;
			m_stack->dump();
			m_local->dump();
			exit(-1);
		}
	}/*}}}*/

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
		throw orcaException(this, "orca.module", string("module file ") + mod_path + " not exists");
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

void orcaVM::need_param()/*{{{*/
{
	throw orcaException(this, "orca.param", "insufficient parameters");
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

int orca_launch_module(orcaVM* vm, char* module, int argc, char** argv)/*{{{*/
{
	set_interactive(false);

	parse_init();

	vm->m_module = g_root;
	vm->m_curr = g_root;

	fs::path cwd = fs::current_path();
	fs::path mod_path(module);
	bool flag_cd = false;

	if (mod_path.branch_path() != cwd) {
		chdir(mod_path.branch_path().string().c_str());
		flag_cd = true;
	}

	if (vm->load(mod_path.filename().c_str()) == false) {
		cout << module << " compile error" << endl;
		if (flag_cd) chdir(cwd.string().c_str());
		return 0;
	}

	string mod_name = mod_path.filename().string();
	if (mod_name.find(".") > 0) 
		mod_name = mod_name.substr(0, mod_name.find("."));

	vm->m_module = g_root->get_member(mod_name.c_str()).o();
	if (!vm->m_module) {
		cout << module << " does not exist" << endl;
		if (flag_cd) chdir(cwd.string().c_str());
		return 0;
	}
	try {
		const char* cp = vm->m_module->get_code();
		int cursize = 1;
		if (cp != NULL) {
			cursize = l2s(cp);
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
		if (flag_cd) chdir(cwd.string().c_str());

		printf("uncaugted exception: %s - %s\n", e.who(), e.what());
		cout << e.m_stack_trace << endl;
		vm->m_stack->dump();
		vm->m_local->dump();

		exit(-1);
	}

	parse_cleanup();
	if (flag_cd) chdir(cwd.string().c_str());
	return 1;
}
/*}}}*/

int orca_launch_interpreter(orcaVM* vm)/*{{{*/
{
	set_interactive(true);
	vm->reserve_local();

	parse_init();

	vm->m_module = g_root;
	vm->m_curr = g_root;

	interpret(vm);

	parse_cleanup();
	return 1;
}
/*}}}*/

OrcaHeader::OrcaHeader(int d, int c, int debug) /*{{{*/
{
	strcpy(name, "orca");
	magic = htonl(MAGIC_NO);
	version = htonl(ORCA_VERSION);
	def_size = htonl(d);
	code_size = htonl(c);
	debug_size = htonl(debug);
}
/*}}}*/

