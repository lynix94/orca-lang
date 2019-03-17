/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaString.cpp - string type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <limits.h>

#include <boost/lexical_cast.hpp>

using namespace boost;

#include "orcaString.h"
#include "orcaTuple.h"
#include "orcaList.h"
#include "orcaVM.h"
#include "orcaException.h"

#include "kyString.h"

static string g_white_string = " \t\r\n";
orcaString g_string;


orcaString::orcaString() 
{
	// this is the only one copy
	make_original();

	orcaData d;
	d.set_type(TYPE_INTERNAL);

	d.internal(FI_STR_ADD, "+");						insert_static("+", d);
	d.internal(FI_STR_MUL, "*");						insert_static("*", d);
	d.internal(FI_STR_MOD, "%");						insert_static("%", d);
	d.internal(FI_STR_EQ, "==");						insert_static("==", d);
	d.internal(FI_STR_NEQ, "!=");						insert_static("!=", d);
	d.internal(FI_STR_GT, ">");							insert_static(">", d);
	d.internal(FI_STR_GE, ">=");						insert_static(">=", d);
	d.internal(FI_STR_LT, "<");							insert_static("<", d);
	d.internal(FI_STR_LE, "<=");						insert_static("<=", d);
	d.internal(FI_STR_LENGTH, "length");				insert_static("length", d);
	d.internal(FI_STR_FIND,"find");						insert_static("find", d);
	d.internal(FI_STR_FIND_ALL,"find_all");				insert_static("find_all", d);
	d.internal(FI_STR_STRIP,"strip");					insert_static("strip", d);
	d.internal(FI_STR_LSTRIP,"lstrip");					insert_static("lstrip", d);
	d.internal(FI_STR_RSTRIP,"rstrip");					insert_static("rstrip", d); 
	d.internal(FI_STR_REPLACE,"replace");				insert_static("replace", d); 
	d.internal(FI_STR_STARTSWITH,"starts_with");		insert_static("starts_with", d); 
	d.internal(FI_STR_ENDSWITH,"ends_with");			insert_static("ends_with", d); 
	d.internal(FI_STR_HASH,"hash");						insert_static("hash", d); 
	d.internal(FI_STR_SPLIT,"split");					insert_static("split", d); 
	d.internal(FI_STR_PUSH_BACK,"push_back");			insert_static("push_back", d); 
	d.internal(FI_STR_CHAR,"char");						insert_static("char", d); 
	d.internal(FI_STR_TO_INT,"integer");				insert_static("integer", d); 
	d.internal(FI_STR_TO_FLOAT,"float");				insert_static("float", d); 
	d.internal(FI_STR_TO_STR,"string");					insert_static("string", d); 
	d.internal(FI_STR_TO_REPR,"repr");					insert_static("repr", d); 
	d.internal(FI_STR_UPPER,"upper");					insert_static("upper", d); 
	d.internal(FI_STR_LOWER,"lower");					insert_static("lower", d); 
	d.internal(FI_STR_LIST_FORMAT,"list_format");		insert_static("list_format", d);
}


static char char_upper(char in)
{
	return toupper(in);
}


orcaData orcaString::ex_upper(orcaVM* vm, string& str, int param_n) 
{ 
	string ret;
	ret.resize(str.length());


	transform(str.begin(), str.end(), ret.begin(), char_upper);
	return ret;
}


static char char_lower(char in)
{
	return tolower(in);
}

orcaData orcaString::ex_add(orcaVM* vm, string& str, int param_n)
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(str).operator_add(vm, rhs);
}

orcaData orcaString::ex_mul(orcaVM* vm, string& str, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(str).operator_mul(vm, rhs);
}

orcaData orcaString::ex_mod(orcaVM* vm, string& str, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(str).operator_mod(vm, rhs);
}


orcaData orcaString::ex_eq(orcaVM* vm, string& str, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(str).operator_eq(vm, rhs);
}

orcaData orcaString::ex_neq(orcaVM* vm, string& str, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(str).operator_neq(vm, rhs);
}

orcaData orcaString::ex_gt(orcaVM* vm, string& str, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(str).operator_gt(vm, rhs);
}

orcaData orcaString::ex_ge(orcaVM* vm, string& str, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(str).operator_ge(vm, rhs);
}

orcaData orcaString::ex_lt(orcaVM* vm, string& str, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(str).operator_lt(vm, rhs);
}

orcaData orcaString::ex_le(orcaVM* vm, string& str, int param_n) 
{
	if (param_n != 1) vm->need_param(1);
	orcaData rhs = vm->get_param(0);
	return orcaData(str).operator_le(vm, rhs);
}


orcaData orcaString::ex_lower(orcaVM* vm, string& str, int param_n) /*{{{*/
{ 
	string ret;
	ret.resize(str.length());

	transform(str.begin(), str.end(), ret.begin(), char_lower);
	return ret;
}
/*}}}*/

orcaData orcaString::ex_char(orcaVM* vm, string& str, int param_n) /*{{{*/
{ 
	if (param_n != 1) vm->need_param(1);
	int v = str[vm->get_param(0).Integer()];
	return v;
}
/*}}}*/

orcaData orcaString::ex_length(orcaVM* vm, string& str, int param_n) /*{{{*/
{ 
	return str.length();
}
/*}}}*/

orcaTuple* orcaString::_find_regex(string& str, regex& re, int s, int e)/*{{{*/
{	
	if (e > str.length())
		e = str.length();

	match_results<string::const_iterator> mr;
	string::const_iterator start, end; 
	start = str.begin() + s;
	end = str.begin() + e;

	if ( regex_search(start, end, mr, re) ) {
		if (mr.size() == 1) {
			orcaTuple* tp = new orcaTuple(3);
			tp->update(0, string(mr[0]));
			tp->update(1, static_cast<int>(mr[0].first - str.begin()));
			tp->update(2, static_cast<int>(mr[0].second - str.begin()));

			return tp;
		}
		else {
			orcaTuple* grp = new orcaTuple(mr.size());
			
			for (int i=0; i<mr.size(); i++) {
				orcaTuple* tp = new orcaTuple(3);
				tp->update(0, string(mr[i]));
				tp->update(1, static_cast<int>(mr[i].first - str.begin()));
				tp->update(2, static_cast<int>(mr[i].second - str.begin()));

				grp->update(i, tp);
			}

			return grp;
		}
	}
	
	return NULL;
}
/*}}}*/

orcaData orcaString::ex_find(orcaVM* vm, string& str, int param_n)/*{{{*/
{	
	int s, e;

	if (is<TYPE_NIL>(vm->get_param(1))) 
		s = 0;
	else
		s = vm->get_param(1).Integer();

	if (is<TYPE_NIL>(vm->get_param(2))) 
		e = INT_MAX;
	else 
		e = vm->get_param(2).Integer();


	orcaData d;
	orcaData p = vm->get_param(0);
	if (is<TYPE_STR>(p)) {
		d.i_set(kyString::find(str, p.s(), s, e));
	}
	else if (is<TYPE_REGEX>(p)) {
		orcaTuple* tp = _find_regex(str, p.re(), s, e);
		if (tp == NULL) {
			d = NIL;
		}
		else {
			d.o_set(tp);
		}
	}
	else {
		throw orcaException(vm, "string.param", string("invalid parameter for string find") + p.dump_str());
	}

	return d;
}
/*}}}*/

orcaData orcaString::ex_starts_with(orcaVM* vm, string& str, int param_n)/*{{{*/
{	
	orcaData d;
	orcaData p = vm->get_param(0);
	if (is<TYPE_STR>(p)) {
		d = kyString::starts_with(str, p.s());
	}
	else if (is<TYPE_REGEX>(p)) {
		d = kyString::starts_with(str, p.re());
	}
	else {
		throw orcaException(vm, "string.param", string("invalid parameter for string starts_with") + p.dump_str());
	}

	return d;
}
/*}}}*/

orcaData orcaString::ex_ends_with(orcaVM* vm, string& str, int param_n) /*{{{*/
{	
	orcaData d;
	orcaData p = vm->get_param(0);
	if (is<TYPE_STR>(p)) {
		d = kyString::ends_with(str, p.s());
	}
	else if (is<TYPE_REGEX>(p)) {
		d = kyString::ends_with(str, p.re());
	}
	else {
		throw orcaException(vm, "string.param", string("invalid parameter for string starts_with") + p.dump_str());
	}

	return d;
}
/*}}}*/

orcaData orcaString::ex_hash(orcaVM* vm, string& str, int param_n)/*{{{*/
{	
	orcaData p = vm->get_param(0);
	int mod = INT_MAX;
	
	if (!is<TYPE_NIL>(p)) {
		mod = p.Integer();
	}

	return kyString::hash(str, mod);
}
/*}}}*/

orcaData orcaString::ex_split(orcaVM* vm, string& str, int param_n)/*{{{*/
{	
	//int sss=0, count=INT_MAX;
	orcaData p = vm->get_param(0);
	orcaList* lp = new orcaList();
	int start = 0;
	int count = INT_MAX;
	if (!is<TYPE_NIL>(vm->get_param(1))) {
		count= vm->get_param(1).Integer();
	}

	if (is<TYPE_STR>(p) || is<TYPE_NIL>(p)) {
		string by;
		if (is<TYPE_NIL>(p)) by = " ";
		else by = p.s();

		do {
			int r = str.find(by, start);
			if (r < 0) {
				lp->push_back(str.substr(start));
				break;
			}

			if (r-start == 0) {
				lp->push_back("");
			}
			else {
				lp->push_back(str.substr(start, r - start));
			}
			start = r+by.length();

			count--;
			if (count <= 0) {
				lp->push_back(str.substr(start));
				break;
			}
		}while(true);
	}
	else if (is<TYPE_REGEX>(p)) {
		do {
			match_results<string::const_iterator> mr;
			string::const_iterator siter, eiter; 
			siter = str.begin() + start;
			eiter = str.begin() + str.length();

			if ( regex_search(siter, eiter, mr, p.re()) ) {
				if ((mr[0].first - str.begin() - start) == 0) {
					lp->push_back("");
				}
				else {
					lp->push_back(str.substr(start, (mr[0].first - str.begin()) - start));
				}
			}
			else {
				lp->push_back(str.substr(start));
				break;
			}

			start = (mr[0].second - str.begin());

			count--;
			if (count <= 0) {
				lp->push_back(str.substr(start));
				break;
			}
		}while(true);
	}
	else {
		throw orcaException(vm, "string.param", string("invalid parameter for split : ") + p.dump_str());
	}

	return lp;
}
/*}}}*/

orcaData orcaString::ex_find_all(orcaVM* vm, string& str, int param_n)/*{{{*/
{
	int s, e;
	if (is<TYPE_NIL>(vm->get_param(1))) 
		s = 0;
	else
		s = vm->get_param(1).Integer();

	if (is<TYPE_NIL>(vm->get_param(2))) 
		e = INT_MAX;
	else 
		e = vm->get_param(2).Integer();

	orcaData p = vm->get_param(0);
	orcaList* lp = new orcaList();
	int start = s;

	if (is<TYPE_STR>(p)) {
		do {
			int r = kyString::find(str, p.s(), start, e);
			if (r < 0)
				break;

			lp->push_back(r);
			start = r+1;
		}while(true);
	}
	else if (is<TYPE_REGEX>(p)) {
		do {
			orcaTuple* tp = _find_regex(str, p.re(), start, e);
			if (tp == NULL)
				break;

			lp->push_back(tp);

			if (isobj<orcaTuple>(tp->at(0))) {
				tp = static_cast<orcaTuple*>(tp->at(0).o());
			}

			start = tp->at(2).i();

		}while(true);
	}
	else {
		throw orcaException(vm, "string.param", string("invalid parameter for find all : ") + p.dump_str());
	}

	return lp;
}
/*}}}*/

orcaData orcaString::ex_replace(orcaVM* vm, string& str, int param_n)/*{{{*/
{	
	int s, e;

	if (is<TYPE_NIL>(vm->get_param(2))) 
		s = 0;
	else
		s = vm->get_param(2).Integer();

	if (is<TYPE_NIL>(vm->get_param(3))) 
		e = INT_MAX;
	else 
		e = vm->get_param(3).Integer();

	string to = vm->get_param(1).string_(vm);

	orcaData p = vm->get_param(0);
	if (is<TYPE_STR>(p)) {
		return kyString::replace(str, p.s(), to, s, e);
	}
	else if (is<TYPE_REGEX>(p)) {
		return kyString::replace(str, p.re(), to, s, e);
	}
	else {
		throw orcaException(vm, "string.param", string("invalid parameter for replace: ") + p.dump_str());
	}

	return NIL;
}
/*}}}*/

orcaData orcaString::ex_strip(orcaVM* vm, string& str, int param_n)/*{{{*/
{ 
	string what;

	if (is<TYPE_NIL>(vm->get_param(0))) 
		what = g_white_string;
	else
		what = vm->get_param(0).String();

	return kyString::strip(str, what);
}
/*}}}*/

orcaData orcaString::ex_lstrip(orcaVM* vm, string& str, int param_n) /*{{{*/
{ 
	string what;
	
	if (is<TYPE_NIL>(vm->get_param(0))) 
		what = g_white_string;
	else
		what = vm->get_param(0).String();

	return kyString::lstrip(str, what);
}
/*}}}*/

orcaData orcaString::ex_rstrip(orcaVM* vm, string& str, int param_n) /*{{{*/
{ 
	string what;
	
	if (is<TYPE_NIL>(vm->get_param(0))) 
		what = g_white_string;
	else
		what = vm->get_param(0).String();

	return kyString::rstrip(str, what);
}
/*}}}*/

orcaData orcaString::ex_integer(orcaVM* vm, string& s, int param_n) /*{{{*/
{
	orcaData d;
	orcaData zero = 0;

	string str = kyString::strip(s);;
	if (str.length() > 9)  {
		d.bn_set(str.c_str());
		if (d.operator_eq(vm, zero).Boolean()) {
			for (int i=0; i<str.length(); i++) {
				if (!isdigit(str[i])) {
					if (i == 0 && str[0] == '-') continue;
		
					throw orcaException(vm, "orca.type", string("invalid format to integer: ") + str);
				}

			}
		}
	}
	else {
		try {
			d.i_set(lexical_cast<int>(str)); 
		}
		catch(...) {
			throw orcaException(vm, "orca.type", string("invalid format to integer: ") + str);
		}
	}

	return d;
}
/*}}}*/

orcaData orcaString::ex_float(orcaVM* vm, string& s, int param_n) /*{{{*/
{
	orcaData d;
	string str = kyString::strip(s);;

	try {
		d.r_set(lexical_cast<double>(str)); 
	}
	catch(...) {
		throw orcaException(vm, "orca.type", string("invalid format to float: ") + str);
	}

	return d;
}
/*}}}*/

orcaData orcaString::ex_string(orcaVM* vm, string& s, int param_n) 
{
	return s;
}

orcaData orcaString::ex_repr(orcaVM* vm, string& s, int param_n) 
{
	return string("\"") + kyString::to_escape(s) + "\"";
}

string orcaString::slice(string& s, int start, int end, bool include_right) /*{{{*/
{
	int len = s.length();
	bool reverse;

	if (start < 0) start += len;
	if (end < 0) end += len;

	if ( start <= end) {
		reverse = false;
	}
	else {
		reverse = true;
		int tmp = start;
		start = end + 1;
		end = tmp + 1;
	}

	if (start < 0) start =0;
	if (end < 0) end = 0;
	if (start > len) start = len;
	if (end > len) end = len;

	if (!reverse) {
		if (include_right) {
			end++;
			if (end > len) end = len;
		}

		return s.substr(start, end - start);
	}
	else {
		string ret;
		if (include_right) {
			start--;
			if (start < 0) start =0;
		}

		string str = s.substr(start, end - start);
		copy(str.rbegin(), str.rend(), back_inserter(ret));
		return ret;
	}
}
/*}}}*/

orcaData orcaString::ex_push_back(orcaVM* vm, string& str, int param_n) // int
{	
	orcaData p = vm->get_param(0);
	p.string_(vm, str);
	return 0; // return value is made in orcaVM.cpp (caller)
}

orcaData orcaString::ex_list_format(orcaVM* vm, string& str, int param_n) 
{ 
	int s=0;
	int e=INT_MAX;

	orcaList* lp = new orcaList();
	int start = s;

	for (int i=0; i<str.length()-1; i++) {
		if (str[i] == '%' && str[i+1] == '{') {
			int j = i+2;
			for (; j<str.length() && str[j] != '}'; j++) {
				if (iswspace(str[j])) break;
				if (str[j] == '%') break;
			}
	
			if (str[j] == '}') {
				lp->push_back(str.substr(i+2, j-(i+2)));
				i=j;
			}
			else {
				i = j-1;
			}
		}
	}

	return lp;
}

