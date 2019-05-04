/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaPack.cpp -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <set>

#include "orcaException.h"
#include "orcaPack.h"
#include "orcaList.h"
#include "orcaMap.h"
#include "orcaGlobal.h"
#include "base64.h"
#include "kyString.h"
#include "orcaRoot.h"

orcaPack* g_pack;

orcaPack::orcaPack()/*{{{*/
{
	set_name("pack");
	insert_static_native_function("dump_code", (object_fp)&orcaPack::ex_dump_code);
	insert_static_native_function("load_code", (object_fp)&orcaPack::ex_load_code);
	insert_static_native_function("list_code", (object_fp)&orcaPack::ex_list_code);
	insert_static_native_function("check_code", (object_fp)&orcaPack::ex_check_code);

	insert_native_function("save", (object_fp)&orcaPack::ex_save);
	insert_native_function("load", (object_fp)&orcaPack::ex_load);
}
/*}}}*/

string orcaPack::save(orcaData d)/*{{{*/
{
	orcaObject obj;

	switch(d.get_type())
	{
	case TYPE_INT:
		return string("i") + d.string_(NULL) + "\n";

	case TYPE_BIGNUM:
		return string("b") + d.string_(NULL) + "\n";
		
	case TYPE_REAL:
		return string("f") + d.string_(NULL) + "\n";

	case TYPE_BOOL:
		if (d.i())
			return "1\n";
		else
			return "0\n";

	case TYPE_STR:
		return string("s") + kyString::to_escape(d.string_(NULL)) + "\n";

	case TYPE_REGEX:
		return string("r") + d.re_str() + "\n";

	case TYPE_NIL:
		return string("n\n");

	case TYPE_NATIVE:
		return string("N") + d.n().owner->get_path_name() + "." 
				+ d.n().name + "\n";

	case TYPE_OBJ: {
		string str;

		if (isobj<orcaList>(d)) {
			str += "l\n";

			orcaList* lp = static_cast<orcaList*>(d.o());
			orcaListIter li = lp->begin();

			for(; li != lp->end(); ++li) {
				str += save(*li);
			}
			
			str += ".\n";
			return str;	
		}
		else if (isobj<orcaTuple>(d)) {
			str += "t\n";

			orcaTuple* tp = static_cast<orcaTuple*>(d.o());
			for(int i=0; i < tp->size(); i++) {
				str += save(tp->at(i));
			}
			
			str += ".\n";
			return str;	
		}
		else if (isobj<orcaMap>(d)) {
			str += "m\n";

			orcaMap* mp = static_cast<orcaMap*>(d.o());
			map<orcaData, orcaData, data_cmp>::iterator mi;
			mi = mp->begin();

			for(; mi != mp->end(); ++mi) {
				str += save(mi->first);
				str += save(mi->second);
			}
			
			str += ".\n";
			return str;	
		}
		else if (typeid(*d.o()) != typeid(obj)) { // native object
			return string("O") + d.o()->get_path_name() + 
				   d.o()->pack_save() + "\n";
		}

		// else
		orcaObject* op = d.o();
		cp_map<orcaData>::Type::iterator mi;
		cp_map<orcaData>::Type* mp;

		str += string("o") + op->get_name() + "\n";

		// traverse static
		mp = op->get_static();
		if (mp) {
			for (mi = mp->begin(); mi != mp->end(); ++mi) {
				str += "S";
				str += mi->first;
				str += "\n";
				str += save(mi->second);
			}
		}

		// traverse member
		mp = op->get_member();
		if (mp) {
			for (mi = mp->begin(); mi != mp->end(); ++mi) {
				str += "M";
				str += mi->first;
				str += "\n";
				str += save(mi->second);
			}
		}

		// traverse parenet
		list<orcaObject*>* lp = op->get_parent();
		if (lp) {
			list<orcaObject*>::iterator it = lp->begin();
			for (; it != lp->end(); ++it) {
				str += "P\n";
				str += save(*it);
			}
		}

		// dump codes
		if (op->get_code() != NULL) {
			const char* code = op->get_code();
			string name = g_codes->get_name(code);
			int offset = code - g_codes->get_base(code);
			str += "C";
			str += name;
			str += "\n";
			str += lexical_cast<string>(offset);
			str += "\n";
		}

		str += ".\n";
		return str;
	}
	default:
		assert(0);
		throw orcaException(NULL, "orca.type", "abnormal type for pack");
	}



}
/*}}}*/

const char* orcaPack::getline(char** cp) {/*{{{*/
	if (*cp == NULL)
		return NULL;

	const char* ret = (const char*)*cp;

	while ( **cp != '\n' ) {
		(*cp)++;
		if ( **cp == '\0') {
			return ret;
		}
	}

	**cp = '\0';
	(*cp)++;
	return ret;	
}
/*}}}*/

orcaData orcaPack::load(char** cp)/*{{{*/
{
	const char* c = getline(cp);

	switch(c[0])
	{
	case 'i':
		return atoi(&c[1]);

	case 'b': {
		orcaData ret;
		ret.bn_set(&c[1]);
		return ret;
	}
	case 'f':
		return atof(&c[1]);

	case '0':
		return false;

	case '1':
		return true;

	case 's':
		return kyString::from_escape(&c[1]);

	case 'r': {
		orcaData ret;
		ret.re_set(&c[1]);
		return ret;
	}
	case 'n': 
		return NIL;

	case 'N': {
		string str = &c[1];
		vector<string> path = kyString::split(str, ".");
		orcaData curr = g_root;
		for (int i=0; i<path.size(); i++) {
			if (is<TYPE_OBJ>(curr) == false)
				return NIL;

			orcaObject* op = curr.o();
			if (op->has_member(path[i].c_str(), curr) == false) 
				return NIL;
		}

		return curr;
	}

	case 'O': {
		string str = &c[1];
		int idx = kyString::find(str, ",");
		string path_name = str;
		string init = "";
		if (idx > 0) {
			path_name = str.substr(0, idx);
			init = str.substr(idx+1);
		}

		vector<string> path = kyString::split(path_name, ".");
		orcaData curr = g_root;
		for (int i=0; i<path.size(); i++) {
			if (is<TYPE_OBJ>(curr) == false)
				return NIL;

			if (curr.o()->has_member(path[i].c_str(), curr) == false) 
				return NIL;
		}

		orcaObject* op = curr.o()->clone(g_root);
		op->pack_load(init);

		return op;
	}

	case 'l': {
		orcaList* lp = new orcaList;

		do {
			if (**cp == '.') {
				getline(cp);
				break;
			}

			lp->push_back(load(cp));
		} while(true);
		
		return lp;	
	}
	case 't': {
		orcaTuple* tp = new orcaTuple;

		do {
			if (**cp == '.') {
				getline(cp);
				break;
			}

			tp->push_back(load(cp)); 

		} while(true);
		
		return tp;	
	}
	case 'm': {
		orcaMap* mp = new orcaMap;

		do {
			if (**cp == '.') {
				getline(cp);
				break;
			}

			orcaData key = load(cp);
			orcaData val = load(cp);

			mp->update(key, val);
		} while(true);
		
		return mp;	
	}
	case 'o': {
		orcaObject* op = new orcaObject;
		op->set_name(&c[1]);

		const char* name;
		
		do {
			const char* line = getline(cp);
			if (line[0] == '.') {
				break;
			}

			switch(line[0])
			{
			case 'S':
				name = &line[1];
				op->insert_static(const_strdup(name), load(cp));
				continue;

			case 'M':
				name = &line[1];
				op->insert_member(const_strdup(name), load(cp));
				continue;

			case 'P':
				op->insert_parent(load(cp).Object());
				continue;

			case 'C': {
				name = &line[1];
				const char* addr = g_codes->get_addr(name);
				if (addr == NULL) {
					throw orcaException(NULL, "orca.pack", "code not exists");
				}

				const char* line = getline(cp);
				int offset = atoi(line);
				op->set_code((char*)addr + offset);
				continue;
				}

			default:
				throw orcaException(NULL, "orca.type", "abnormal type for unpack");
			}
		} while(true);

		return op;
	}
	default:
		throw orcaException(NULL, "orca.type", "abnormal type for unpack");
	}
}
/*}}}*/

orcaData orcaPack::ex_save(orcaVM* vm, int n) /*{{{*/
{
	if (n < 1) vm->need_param();

	return save(vm->get_param(0));
}
/*}}}*/

orcaData orcaPack::ex_load(orcaVM* vm, int n) /*{{{*/
{
	if (n < 1) vm->need_param();

	string str = vm->get_param(0).String();

	char* cp = (char*)str.c_str();
	orcaData ret = load(&cp);
	return ret;
}
/*}}}*/

orcaData orcaPack::ex_dump_code(orcaVM* vm, int n) /*{{{*/
{
	if (n < 1) vm->need_param();

	string str = vm->get_param(0).String();

	int size;
	const char* cp = g_codes->get_addr(str, &size);

	string b64 = base64_encode((unsigned char*)cp, size);

	return b64;
}
/*}}}*/

orcaData orcaPack::ex_load_code(orcaVM* vm, int n) /*{{{*/
{
	if (n < 2) vm->need_param();

	string name = vm->get_param(0).String();
	string b64 = vm->get_param(1).String();

	string code = base64_decode(b64);
	int size = code.length();

	char* cp = const_cast<char*>(g_codes->new_code(size));
	if (cp == NULL) {
		throw orcaException(vm, "orca.lang", "code already exists");
	}

	memcpy(cp, code.c_str(), size);

	return NIL;
}
/*}}}*/

orcaData orcaPack::ex_list_code(orcaVM* vm, int n) /*{{{*/
{
	if (n < 1) vm->need_param();

	string str = vm->get_param(0).String();
	match_results<string::const_iterator> mr;
	boost::regex re;
	std::string::const_iterator start, end; 
	start = str.begin();
	end = str.end();

	re = "^C[a-zA-Z_][a-zA-Z_0-9]+";
	
	set<string> codes;
	do {
		if ( !regex_search(start, end, mr, re) ) {
			break;
		}

		codes.insert(string(mr[0]).substr(1));
		start = mr[0].second;

	} while (true);

	orcaList* lp = new orcaList();
	for (set<string>::iterator si = codes.begin(); si!=codes.end(); ++si) {
		lp->push_back(*si);
	}

	return lp;
}
/*}}}*/

orcaData orcaPack::ex_check_code(orcaVM* vm, int n) /*{{{*/
{
	if (n < 1) vm->need_param();

	orcaList* clist = static_cast<orcaList*>(ex_list_code(vm, n).o());
	orcaList* lp = new orcaList();
	for(orcaListIter it = clist->begin(); it!=clist->end(); ++it) {
		if (g_codes->get_addr((*it).s()) == NULL)
			lp->push_back(*it);
	}

	delete clist;
	return lp;
}
/*}}}*/

