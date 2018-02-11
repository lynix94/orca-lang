/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaData.cpp - basic orca data types

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include "porting.h"

#include "orcaGlobal.h"
#include "orcaData.h"
#include "orcaObject.h"
#include "orcaException.h"
#include "orcaStack.h"
#include "orcaList.h"
#include "orcaTuple.h"
#include "orcaMap.h"


#ifdef WIN32
#define snprintf _snprintf
#endif

LIBORCA_API orcaData NIL;

string format_str(orcaVM* vm, string& format, vector<orcaData>& params)/*{{{*/
{
	string out;
	vector<orcaData>::iterator it = params.begin();
	for (int i=0; i<format.length(); i++) {
		if (format[i] == '%')
		{
			string new_format;
			string new_out;

			int count = 0;
			bool loop = true;
			bool flag = true;
			char type = 0;
			do {
				new_format += format[i];

				loop = false;
				switch(format[i])
				{
				case 'd':
				case 'i':
				case 'u':
				case 'x':
				case 'X':
				case 'o':
				case 'c':
					type = 'i';
					break;

				case 'e':
				case 'E':
				case 'g':
				case 'G':
				case 'f':
				case 'F':
					type = 'f';
					break;

				case 's':
					type = 's';
					break;

				case 'p':
					type = 'p';
					break;

				case '$':
					throw orcaException(vm, "orca.param", 
										string("invalid format parameters ") + "$");
					break;

				case '%':
				case '.':
				case '+':				
				case '-':
				case '#':
					if (count != 0) {
						flag = false;
					}
					else {
						loop = true;
					}
					count++;
					break;

				default: 
					if (isdigit(format[i])) loop = true;
					else flag = false;
				}

				i++;
			} while (loop);

			if (flag == false) {
				// not format
				out += new_format;
				i--;
				continue;
			}

			i--;
			char buff[1024];
			if (it == params.end()) {
				throw orcaException(vm, "orca.param", "insufficient param in format arguments");
			}

			orcaData d = (*it);

			int p_i;
			string p_s;
			double p_d;
			void* p_p;
			switch(type)
			{
			case 'i': 
				if (d.get_type() != TYPE_BIGNUM) {
					switch(d.get_type()) {
						case TYPE_INT: p_i = d.i(); break;
						case TYPE_REAL: p_i = (int)d.r(); break;
						case TYPE_STR: p_i = atoi(d.s().c_str()); break;
						case TYPE_BOOL: p_i = d.i(); break;
						default: p_i = 0;
					}
					snprintf(buff, sizeof(buff), new_format.c_str(), p_i);
				}
				else {
					new_format = new_format.replace(0, 1, "%Z"); 
					gmp_snprintf(buff, sizeof(buff), new_format.c_str(), d.bn());
				}
				break;


			case 'f': 
				switch(d.get_type()) {
					case TYPE_INT: p_d = d.i(); break;
					case TYPE_BIGNUM: p_d = get_bn_double(d.bn()); break;
					case TYPE_REAL: p_d = d.r(); break;
					case TYPE_STR: p_d = atof(d.s().c_str()); break;
					case TYPE_BOOL: p_d = d.i(); break;
					default: p_d = 0;
				}
				snprintf(buff, sizeof(buff), new_format.c_str(), p_d);
				break;

			case 's':
				p_s = d.string_(vm);
				snprintf(buff, sizeof(buff), new_format.c_str(), p_s.c_str());
				break;

			case 'p':
				p_p = NULL;
				if (is<TYPE_OBJ>(d)) {
					p_p = d.o();
				}

				snprintf(buff, sizeof(buff), new_format.c_str(), p_p);
				
#ifdef WINDOWS
				{
					char buff_tmp[32];
					strncpy(buff_tmp, buff, 32);
					snprintf(buff, sizeof(buff), "0x%s", buff_tmp);
				}
#endif
				break;

			default:
				break;
			}

			it++;
			out += buff;
		}
		else {
			out += format[i];
		}
	}

	return out;
}
/*}}}*/

string format_str(orcaVM* vm, string& format, orcaData d)/*{{{*/
{
	vector<orcaData> params;
	params.push_back(d);

	return format_str(vm, format, params);
}
/*}}}*/

string get_bn_string(mpz_t& bn) /*{{{*/
{
	char* cp = (char*)malloc(mpz_sizeinbase(bn, 10) + 2);
	mpz_get_str(cp, 10, bn);
	string str = cp;
	free(cp);

	return str;
}
/*}}}*/

double get_bn_double(mpz_t& bn) /*{{{*/
{
	return mpz_get_d(bn);
}
/*}}}*/

orcaData::orcaData(orcaObject* o, object_fp fp, const char* name) /*{{{*/
{ 
//	v.n = new Native(); // permanant life
	t = TYPE_NATIVE;
	v.n.owner = o;
	v.n.fp = fp;
	v.n.name = name;
}
/*}}}*/

orcaData orcaData::clone(orcaObject* owner) /*{{{*/
{
	orcaData ret;
	ret.t = this->t;

	switch(t)
	{
	case TYPE_STR:
		ret.s_set(this->s());
		break;

	case TYPE_REGEX:
		ret.v.ro = new ReObject();
		ret.v.ro->re = this->re();
		break;

	case TYPE_BIGNUM:
		ret.bn_set(this->bn());
		break;

	case TYPE_OBJ:
		ret.v.o = this->v.o->clone(owner);
		break;

	case TYPE_NATIVE:
		ret = *this;
		ret.n().owner = owner;
		break;

	default:
		ret = *this;
		break;
	}

	return ret;
}
/*}}}*/

string orcaData::string_(orcaVM* vm) const/*{{{*/
{
	string ret;
	string_(vm, ret);

	return ret;
}
/*}}}*/

void orcaData::string_(orcaVM* vm, string& str) const/*{{{*/
{
	char buff[20];

	switch(t)
	{
	case TYPE_INT: 
		sprintf(buff, "%d", v.i);
		str += buff;
		break;

	case TYPE_BIGNUM: 
		str += get_bn_string(v.bo->bn);
		break;

	case TYPE_REAL: 
		sprintf(buff, "%g", v.r);
		str += buff;
		break;

	case TYPE_BOOL:
		str += v.i?"true":"false";
		break;

	case TYPE_STR:
		str += s();
		break;

	case TYPE_REGEX:
		str += string("r\'") + re_str() + "\'";
		break;

	case TYPE_OBJ:
		v.o->string_(vm, str);
		break;

	case TYPE_NIL:
		str += "nil";
		break;

	case TYPE_NATIVE:
		str += v.n.name;
		break;

	case TYPE_INTERNAL: 
		str += v.internal.name;
		break;

	case TYPE_TYPE:
		switch(v.type.t)
		{
		case TYPE_INT:
		case TYPE_BIGNUM:
			str += "<type int>";	break;
		case TYPE_REAL:
			str += "<type float>";	break;
		case TYPE_BOOL:
			str += "<type bool>";	break;
		case TYPE_STR:
			str += "<type string>";	break;
		case TYPE_REGEX:
			str += "<type regex>";	break;
		case TYPE_OBJ:
			if (v.type.vp == NULL)
				str += "<type object>";
			else {
				orcaObject* op = (orcaObject*)v.type.vp;
				str += string("<type object ") + op->get_name() + " >";
			}
			break;
		case TYPE_NIL:
			str += "<type nil>";	break;
		case TYPE_NATIVE:
			str += "<type native function>";	break;
		case TYPE_INTERNAL: 
			str += "<type internal function>";	break;

		default:
			str += "<type unknown>";
		}
		break;

	default:
		orca_error("unknown type(%d)...\n", t);
	}
}
/*}}}*/

void orcaData::dump() const/*{{{*/
{
	char buff[4096 * 10];
	printf("%s\n", dump(buff));
}
/*}}}*/

string orcaData::dump_str() const/*{{{*/
{
	char buff[4096 * 10];
	return dump(buff);
}
/*}}}*/

char* orcaData::dump(char* buff) const/*{{{*/
{
	switch(t) 
	{
	case TYPE_INT:
		sprintf(buff, "integer: %d", v.i);
		break;

	case TYPE_BIGNUM: 
		sprintf(buff, "integer(big): %s", get_bn_string(v.bo->bn).c_str());
		break;

	case TYPE_REAL:
		sprintf(buff, "float: %g", v.r);
		break;

	case TYPE_BOOL:
		sprintf(buff, "boolean: %d", v.i);
		break;

	case TYPE_STR:
		sprintf(buff, "string: %s", s().c_str());
		break;

	case TYPE_REGEX:
		sprintf(buff, "regex: r'%s'", re_str().c_str());
		break;

	case TYPE_INTERNAL:
		sprintf(buff, "Internal: %d", v.i);
		break;

	case TYPE_NATIVE:
		sprintf(buff, "Native");
		break;

	case TYPE_OBJ:
		if (v.o) {
			sprintf(buff, "orcaObject: (null)");
			v.o->dump(buff);	// return directly
		}
		else {
			sprintf(buff, "orcaObject: (null)");
		}
		break;

	case TYPE_NIL:
		sprintf(buff, "nil");
		break;

	case TYPE_MARK:
		sprintf(buff, "marker: %d", v.mark.type);
 		break;

	case TYPE_TYPE:
		sprintf(buff, "type: %d", v.type.t);
 		break;

	default:
		orca_error("unknown type(%d)...\n", t);
	}

	return buff;
}
/*}}}*/

orcaData orcaData::native_call(orcaVM* vm, int param_n) /*{{{*/
{
	orcaObject* o = n().owner;
	orcaData (orcaObject::*fp)(orcaVM*, int) = n().fp;

	orcaData ret = (o->*fp)(vm, param_n);
	vm->m_local->mark_return(ret);

	return ret;
}
/*}}}*/

long long orcaData::id()/*{{{*/
{
	switch(get_type())
	{
	case TYPE_INT:		return 0;
	case TYPE_BIGNUM:	return (long long)&bn();
	case TYPE_REAL:		return 0;
	case TYPE_STR:		return (long long)&s();
	case TYPE_OBJ:		return (long long)o();
	default:			return 0;
	}
}
/*}}}*/

void orcaData::rc_inc() /*{{{*/
{
	switch(t)
	{
	case TYPE_OBJ:
	case TYPE_REGEX:
	case TYPE_STR:
	case TYPE_BIGNUM:
		((RC_Object*)v.o)->rc_inc();

	case TYPE_INTERNAL:
		break;
	}
}
/*}}}*/

void orcaData::rc_dec() {/*{{{*/
	switch(t)
	{
	case TYPE_OBJ:
	case TYPE_REGEX:
	case TYPE_STR:
	case TYPE_BIGNUM:
		((RC_Object*)v.o)->rc_dec();

	case TYPE_INTERNAL:
		break;
	}
}
/*}}}*/

int orcaData::get_rc() {/*{{{*/
	switch(t)
	{
	case TYPE_OBJ:
	case TYPE_REGEX:
	case TYPE_STR:
	case TYPE_BIGNUM:
		return ((RC_Object*)v.o)->get_rc();
	}

	// should? check
	return 100;
}
/*}}}*/

void orcaData::set_rc(int rc) {/*{{{*/
	switch(t)
	{
	case TYPE_OBJ:
	case TYPE_REGEX:
	case TYPE_STR:
	case TYPE_BIGNUM:
		((RC_Object*)v.o)->set_rc(rc);
	}
}
/*}}}*/

bool orcaData::operator<(const orcaData& r) const/*{{{*/
{
	 orcaVM* vm = NULL;
	 if (this->get_type() == TYPE_OBJ || is<TYPE_OBJ>(r)) {
		vm = get_current_vm();
	 }
	 
	 orcaData rhs = r;
	 orcaData lhs = *this;
	 return lhs.operator_lt(vm, rhs).Boolean();
}
/*}}}*/

bool orcaData::operator<(orcaData& r)/*{{{*/
{
	return operator_lt(NULL, r).Boolean();
}
/*}}}*/

bool orcaData::operator<=(orcaData& r) /*{{{*/
{
	return operator_le(NULL, r).Boolean();
}
/*}}}*/

bool orcaData::operator>(orcaData& r) /*{{{*/
{
	return operator_gt(NULL, r).Boolean();
}
/*}}}*/

bool orcaData::operator>=(orcaData& r) /*{{{*/
{
	return operator_ge(NULL, r).Boolean();
}
/*}}}*/

bool orcaData::operator==(orcaData& r) /*{{{*/
{
	return operator_eq(NULL, r).Boolean();
}
/*}}}*/

bool orcaData::operator!=(orcaData& r)/*{{{*/
{
	return operator_neq(NULL, r).Boolean();
}
/*}}}*/

orcaData orcaData::operator_lt(orcaVM* vm, orcaData& rhs) /*{{{*/
{
	if (is<TYPE_INT>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT:		return i() < rhs.i();
		case TYPE_BIGNUM:	return mpz_cmp_si(rhs.bn(), i()) > 0;
		case TYPE_REAL:		return i() < rhs.r();
		case TYPE_STR:		return true;
		case TYPE_OBJ:		break;
		default:			return false;
		}
	}
	else if (is<TYPE_STR>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT:
		case TYPE_BIGNUM:
		case TYPE_REAL:		return false;
		case TYPE_STR:		return s() < rhs.s();
		case TYPE_OBJ:		break;
		default:			return false;
		}
	}
	else if (is<TYPE_BIGNUM>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT:		return mpz_cmp_si(bn(), rhs.i()) < 0;
		case TYPE_BIGNUM:	return mpz_cmp(bn(), rhs.bn()) < 0;
		case TYPE_REAL:		return mpz_cmp_d(bn(), rhs.r()) < 0;
		case TYPE_STR:		return true;
		case TYPE_OBJ:		break;
		default:			return false;
		}
	}
	else if (is<TYPE_REAL>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT:		return r() < rhs.i();
		case TYPE_BIGNUM:	return mpz_cmp_d(rhs.bn(), r()) > 0;
		case TYPE_REAL:		return r() < rhs.r();
		case TYPE_STR:		return true;
		case TYPE_OBJ:		break;
		default:			return false;
		}
	}

	if (is<TYPE_TYPE>(*this) && type_get().t == TYPE_OBJ) {
		orcaObject* o1 = (orcaObject*)type_get().vp;
		orcaObject* o2 = NULL;

		if (is<TYPE_OBJ>(rhs)) {
			o2 = rhs.o();
		}
		else if (is<TYPE_TYPE>(rhs) && rhs.type_get().t == TYPE_OBJ) {
			o2 = (orcaObject*)rhs.type_get().vp;
		}

		if (o1 == NULL || o2 == NULL) return false;

		return o1->issubclassof(o2);
	}

	if (is<TYPE_OBJ>(*this)) {
		orcaData d = o()->operator_lt(vm, rhs);
		if (!is<TYPE_NIL>(d)) {
			return d;
		}
	}
	else if (is<TYPE_OBJ>(rhs)) {
		orcaData d= rhs.o()->operator_ge(vm, *this);
		if (is<TYPE_BOOL>(d)) {
			return !d.Boolean();
		}
	}

	return NIL;
}
/*}}}*/

orcaData orcaData::operator_le(orcaVM* vm, orcaData& rhs) /*{{{*/
{
	if (is<TYPE_TYPE>(*this) && type_get().t == TYPE_OBJ) {
		orcaObject* o1 = (orcaObject*)type_get().vp;
		orcaObject* o2 = NULL;

		if (is<TYPE_OBJ>(rhs)) {
			o2 = rhs.o();
		}
		else if (is<TYPE_TYPE>(rhs) && rhs.type_get().t == TYPE_OBJ) {
			o2 = (orcaObject*)rhs.type_get().vp;
		}

		bool ret = false;
		if (o1 != NULL && o2 != NULL) {
			ret = o1->isinstanceof(o2);
		}

		return ret;
	}

	// try redefined operator first
	if (is<TYPE_OBJ>(*this)) {
		if (o()->has_member("<=")) {
			orcaData d = o()->operator_le(vm, rhs);
			if (!is<TYPE_NIL>(d)) {
				return d;
			}
		}
	}

	orcaData ret = operator_lt(vm, rhs).Boolean();
	if (ret.Boolean() == false) {
		ret = operator_eq(vm, rhs).Boolean();
	}

	return ret;
}
/*}}}*/

orcaData orcaData::operator_gt(orcaVM* vm, orcaData& rhs) /*{{{*/
{
	// try redefined operator first
	if (is<TYPE_OBJ>(*this)) {
		if (o()->has_member(">")) {
			orcaData d = o()->operator_gt(vm, rhs);
			if (!is<TYPE_NIL>(d)) {
				return d;
			}
		}
	}

	return !this->operator_le(vm, rhs).Boolean();
}
/*}}}*/

orcaData orcaData::operator_ge(orcaVM* vm, orcaData& rhs) /*{{{*/
{
	// try redefined operator first
	if (is<TYPE_OBJ>(*this)) {
		if (o()->has_member(">=")) {
			orcaData d = o()->operator_ge(vm, rhs);
			if (!is<TYPE_NIL>(d)) {
				return d;
			}
		}
	}

	return !this->operator_lt(vm, rhs).Boolean();
}
/*}}}*/

orcaData orcaData::operator_eq(orcaVM* vm, orcaData& rhs) /*{{{*/
{
	if (is<TYPE_INT>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT:		return i() == rhs.i();
		case TYPE_BIGNUM:	return mpz_cmp_si(rhs.bn(), i()) == 0;
		case TYPE_REAL:		return i() == rhs.r();
		case TYPE_TYPE:	
		case TYPE_OBJ:		break;
		default:			return false;
		}
	}
	else if (is<TYPE_REAL>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT:		return r() == rhs.i();
		case TYPE_BIGNUM:	return mpz_cmp_d(rhs.bn(), r()) == 0;
		case TYPE_REAL:		return r() == rhs.r();
		case TYPE_TYPE:	
		case TYPE_OBJ:		break;
		default:			return false;
		}
	}
	else if (is<TYPE_STR>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_STR:		return s() == rhs.s();
		case TYPE_REGEX:	return boost::regex_match(s(), rhs.re());
		case TYPE_TYPE:	
		case TYPE_OBJ:		break;
		default:			return false;
		}
	}
	else if (is<TYPE_BIGNUM>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT:		return mpz_cmp_si(bn(), rhs.i()) == 0;
		case TYPE_BIGNUM:	return mpz_cmp(bn(), rhs.bn()) == 0;
		case TYPE_REAL:		return mpz_cmp_d(bn(), rhs.r()) == 0;
		case TYPE_TYPE:	
		case TYPE_OBJ:		break;
		default:			return false;
		}
	}
	else if (is<TYPE_REGEX>(*this) && is<TYPE_STR>(rhs)) {
		return boost::regex_match(rhs.s(), re());
	}
	else if (is<TYPE_NIL>(*this) && is<TYPE_NIL>(rhs)) {
		return true;
	}

	if (is<TYPE_TYPE>(*this) || is<TYPE_TYPE>(rhs)) {
		orcaData p1 = *this;
		orcaData p2 = rhs;

		if (!is<TYPE_TYPE>(p1)) {
			p2 = *this;
			p1 = rhs;
		}

		type_t t = p1.type_get();
		if (is<TYPE_TYPE>(p2)) {
			if (t.t == TYPE_OBJ && p2.type_get().t == TYPE_OBJ) {
				orcaObject* o1 = (orcaObject*)t.vp;
				orcaObject* o2 = (orcaObject*)p2.type_get().vp;

				if (dynamic_cast<orcaList*>(o1) && 
					dynamic_cast<orcaList*>(o2))
				{
					return true;
				}
				else if (dynamic_cast<orcaTuple*>(o1) && 
					dynamic_cast<orcaTuple*>(o2))
				{
					return true;
				}
				else if (dynamic_cast<orcaMap*>(o1) && 
					dynamic_cast<orcaMap*>(o2))
				{
					return true;
				}
	
				return o1->get_original() == o2->get_original();
			}

			bool ret =  t.t == p2.type_get().t;
			if (!ret) {
				if (t.t == TYPE_INT && p2.type_get().t == TYPE_BIGNUM)
					ret = true;
				if (t.t == TYPE_BIGNUM && p2.type_get().t == TYPE_INT)
					ret = true;
			}

			return ret;
		}
		else if (t.t == TYPE_OBJ && is<TYPE_OBJ>(p2)) {
			if (t.t == TYPE_OBJ && t.vp == NULL) return true;
			if (((orcaObject*)t.vp)->get_original() == p2.o()->get_original())
				return true;
		}
		else {
			bool ret =  p1.type_get().t == p2.get_type();
			if (!ret) {
				if (p1.type_get().t == TYPE_INT && is<TYPE_BIGNUM>(p2)) {
					ret = true;
				}
				if (p1.type_get().t == TYPE_BIGNUM && is<TYPE_INT>(p2)) {
					ret = true;
				}
			}

			return ret;
		}
	}

	if (is<TYPE_OBJ>(*this)) {
		orcaData d = o()->operator_eq(vm, rhs);
		if (!is<TYPE_NIL>(d)) {
			return d;
		}
	}
	else if (is<TYPE_OBJ>(rhs)) {
		orcaData d = rhs.o()->operator_eq(vm, *this);
		if (!is<TYPE_NIL>(d)) {
			return d;
		}
	}

	return false;
}
/*}}}*/

orcaData orcaData::operator_neq(orcaVM* vm, orcaData& rhs) /*{{{*/
{
	// try redefined operator first
	if (is<TYPE_OBJ>(*this)) {
		if (o()->has_member("!=")) {
			orcaData d = o()->operator_neq(vm, rhs);
			if (!is<TYPE_NIL>(d)) {
				return d;
			}
		}
	}

	return !operator_eq(vm, rhs).Boolean();
}
/*}}}*/

orcaData orcaData::operator_and(orcaVM* vm, orcaData& rhs) /*{{{*/
{
	if (is<TYPE_OBJ>(*this)) {
		orcaData d = o()->operator_and(vm, rhs);
		if (!is<TYPE_NIL>(d)) {
			return d;
		}
	}
	else if (is<TYPE_OBJ>(rhs)) {
		orcaData d = rhs.o()->operator_and(vm, *this);
		if (!is<TYPE_NIL>(d)) {
			return d;
		}
	}

	bool bl=false, br=false;
	switch(this->get_type())
	{
	case TYPE_INT: 
	case TYPE_BOOL: bl = i()?true:false; break;
	case TYPE_BIGNUM: bl = mpz_cmp_si(bn(), 0)?true:false; break;
	}

	if (!bl) return false;

	switch(rhs.get_type())
	{
	case TYPE_INT: 
	case TYPE_BOOL: br = i()?true:false; break;
	case TYPE_BIGNUM: br = mpz_cmp_si(bn(), 0)?true:false; break;
	}

	return bl && br;
}
/*}}}*/

orcaData orcaData::operator_or(orcaVM* vm, orcaData& rhs) /*{{{*/
{
	if (is<TYPE_OBJ>(*this)) {
		orcaData d = o()->operator_or(vm, rhs);
		if (!is<TYPE_NIL>(d)) {
			return d;
		}
	}
	else if (is<TYPE_OBJ>(rhs)) {
		orcaData d = rhs.o()->operator_or(vm, *this);
		if (!is<TYPE_NIL>(d)) {
			return d;
		}
	}

	bool bl=false, br=false;
	switch(this->get_type())
	{
	case TYPE_INT: 
	case TYPE_BOOL: bl = i()?true:false; break;
	case TYPE_BIGNUM: bl = mpz_cmp_si(bn(), 0)?true:false; break;
	}

	if (bl) return true;

	switch(rhs.get_type())
	{
	case TYPE_INT: 
	case TYPE_BOOL: br = i()?true:false; break;
	case TYPE_BIGNUM: br = mpz_cmp_si(bn(), 0)?true:false; break;
	}

	return bl || br;
}
/*}}}*/

orcaData orcaData::operator_add(orcaVM* vm, orcaData& rhs) /*{{{*/
{
	mpz_t b;
	orcaData d;
	int j;

	if (is<TYPE_INT>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT: {
			j = i() + rhs.i();
			if (i()>0 && rhs.i()>0 && j<0) {
				mpz_init(b);
				mpz_set_si(b, i());
				mpz_add_ui(b, b, rhs.i());
				d.bn_set(b);
				mpz_clear(b);
				return d;
			}

			return j;
		  }
		case TYPE_BIGNUM: {	
			mpz_init(b); 

			if (i() > 0) 
					mpz_add_ui(b, rhs.bn(), i());
			else	mpz_sub_ui(b, rhs.bn(), abs(i()));

			if (mpz_fits_sint_p(b)) {
				j = mpz_get_si(b);
				mpz_clear(b);
				return j;
			}

			d.bn_set(b);
			mpz_clear(b);
			return d;
		  }
		case TYPE_REAL:	
			return i() + rhs.r();

		case TYPE_STR:
			return boost::lexical_cast<string>(i()) + rhs.s();

		case TYPE_OBJ:		break;
		default:
			return NIL;
		}
	}
	else if (is<TYPE_REAL>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT:		
			return r() + rhs.i();

		case TYPE_BIGNUM:	
			return r() + mpz_get_d(rhs.bn());

		case TYPE_REAL:		
			return r() + rhs.r();

		case TYPE_STR:		
			return boost::lexical_cast<string>(r()) + rhs.s();

		case TYPE_OBJ:		break;

		default:			
			return NIL;
		}
	}
	else if (is<TYPE_STR>(*this)) {
		return s() + rhs.s();
	}
	else if (is<TYPE_BIGNUM>(*this)) {

		switch(rhs.get_type())
		{
		case TYPE_INT:
			mpz_init(b);
			if (rhs.i() > 0) 
					mpz_add_ui(b, bn(), rhs.i());
			else	mpz_sub_ui(b, bn(), abs(rhs.i()));

			if (mpz_fits_sint_p(b)) {
				j = mpz_get_si(b);
				mpz_clear(b);
				return j;
			}
			break;

		case TYPE_BIGNUM:
			mpz_init(b);
			mpz_add(b, bn(), rhs.bn());

			if (mpz_fits_sint_p(b)) {
				j = mpz_get_si(b);
				mpz_clear(b);
				return j;
			}
			break;
		
		case TYPE_REAL:
			return mpz_get_d(bn()) + rhs.r();

		case TYPE_STR: 
			return get_bn_string(bn()) + rhs.s();

		case TYPE_OBJ:		
			break;

		default:
			return NIL;
		}

		d.bn_set(b);
		mpz_clear(b);
		return d;
	}

	if (is<TYPE_OBJ>(*this)) {
		if (vm == NULL) vm = get_current_vm();
		orcaData ret = o()->operator_add(vm, rhs);
		if (!is<TYPE_NIL>(ret)) {
			return ret;
		}
	}

	if (is<TYPE_OBJ>(rhs)) {
		if (vm == NULL) vm = get_current_vm();
		return rhs.o()->operator_add(vm, *this);
	}

	return NIL;
}
/*}}}*/

orcaData orcaData::operator_sub(orcaVM* vm, orcaData& rhs) /*{{{*/
{
	mpz_t b;
	orcaData d;
	int j;

	if (is<TYPE_INT>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT: {
			j = i() - rhs.i();
			if (i()<0 && rhs.i()>0 && j>0) {
				mpz_init(b);
				mpz_set_si(b, i());
				mpz_sub_ui(b, b, rhs.i());
				d.bn_set(b);
				mpz_clear(b);
				return d;
			}

			return j;
		  }
		case TYPE_BIGNUM: {	
			mpz_init(b); 

			if (i() > 0) {
				mpz_sub_ui(b, rhs.bn(), i());
				mpz_neg(b, b);
			}
			else {
				mpz_add_ui(b, rhs.bn(), abs(i()));
				mpz_neg(b, b);
			}

			if (mpz_fits_sint_p(b)) {
				j = mpz_get_si(b);
				mpz_clear(b);
				return j;
			}

			d.bn_set(b);
			mpz_clear(b);
			return d;
		  }
		case TYPE_REAL:	
			return i() - rhs.r();
		case TYPE_OBJ:		break;
		default:
			return NIL;
		}
	}
	else if (is<TYPE_REAL>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT:		
			return r() - rhs.i();

		case TYPE_BIGNUM:	
			return r() - mpz_get_d(rhs.bn());

		case TYPE_REAL:		
			return r() - rhs.r();

		case TYPE_OBJ:	
			break;

		default:			
			return NIL;
		}
	}
	else if (is<TYPE_BIGNUM>(*this)) {

		switch(rhs.get_type())
		{
		case TYPE_INT:
			mpz_init(b);
			if (rhs.i() > 0) 
					mpz_sub_ui(b, bn(), rhs.i());
			else	mpz_add_ui(b, bn(), abs(rhs.i()));

			if (mpz_fits_sint_p(b)) {
				j = mpz_get_si(b);
				mpz_clear(b);
				return j;
			}

			break;

		case TYPE_BIGNUM:
			mpz_init(b);
			mpz_sub(b, bn(), rhs.bn());

			if (mpz_fits_sint_p(b)) {
				j = mpz_get_si(b);
				mpz_clear(b);
				return j;
			}
			break;
		
		case TYPE_REAL:
			return mpz_get_d(bn()) - rhs.r();

		case TYPE_OBJ:
			break;

		default:
			return NIL;
		}

		d.bn_set(b);
		mpz_clear(b);
		return d ;
	}

	if (is<TYPE_OBJ>(*this)) {
		if (vm == NULL) vm = get_current_vm();
		orcaData ret = o()->operator_sub(vm, rhs);
		if (!is<TYPE_NIL>(ret)) {
			return ret;
		}
	}

	if (is<TYPE_OBJ>(rhs)) {
		if (vm == NULL) vm = get_current_vm();
		return rhs.o()->operator_sub_rev(vm, *this);
	}

	return NIL;
}
/*}}}*/

orcaData orcaData::operator_mul(orcaVM* vm, orcaData& rhs) /*{{{*/
{
	mpz_t b;
	orcaData d;
	int j;

	if (is<TYPE_INT>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT: {
			long long j = (long long)i() * (long long)rhs.i();
			if (j > INT_MAX) {
				mpz_t b;
				mpz_init(b);
				mpz_set_si(b, i());
				mpz_mul_si(b, b, rhs.i());
				d.bn_set(b);
				mpz_clear(b);
				return d;
			}

			return static_cast<int>(j);
		  }
		case TYPE_BIGNUM: {	
			mpz_init(b); 
			mpz_mul_si(b, rhs.bn(), i());

			if (mpz_fits_sint_p(b)) {
				j = mpz_get_si(b);
				mpz_clear(b);
				return j;
			}

			d.bn_set(b);
			mpz_clear(b);
			return d;
		  }
		case TYPE_REAL:		
			return i() * rhs.r();
		case TYPE_OBJ:		
			break;
		default:			
			return NIL;
		}
	}
	else if (is<TYPE_REAL>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT:		
			return r() * rhs.i();
		case TYPE_BIGNUM:	
			return r() * mpz_get_d(rhs.bn());
		case TYPE_REAL:		
			return r() * rhs.r();
		case TYPE_OBJ:		
			break;
		default:			
			return NIL;
		}
	}
	else if (is<TYPE_BIGNUM>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT:
			mpz_init(b);
			mpz_mul_si(b, bn(), rhs.i());

			if (mpz_fits_sint_p(b)) {
				j = mpz_get_si(b);
				mpz_clear(b);
				return j;
			}
			break;

		case TYPE_BIGNUM:
			mpz_init(b);
			mpz_mul(b, bn(), rhs.bn());

			if (mpz_fits_sint_p(b)) {
				j = mpz_get_si(b);
				mpz_clear(b);
				return j;
			}
			break;
		
		case TYPE_REAL:
			return mpz_get_d(bn()) * rhs.r();

		case TYPE_OBJ:		
			break;

		default:
			return NIL;
		}

		d.bn_set(b);
		mpz_clear(b);
		return d ;
	}
	else if (is<TYPE_STR>(*this)) {
		string str = "";
		switch(rhs.get_type())
		{
		case TYPE_INT:
			for (int i=0; i<rhs.i(); i++) {
				str += s();
			}
			return str;

		default:
			break;
		}
	}


	if (is<TYPE_OBJ>(*this)) {
		if (vm == NULL) vm = get_current_vm();
		orcaData ret = o()->operator_mul(vm, rhs);
		if (!is<TYPE_NIL>(ret)) {
			return ret;
		}
	}

	if (is<TYPE_OBJ>(rhs)) {
		if (vm == NULL) vm = get_current_vm();
		return rhs.o()->operator_mul(vm, *this);
	}

	return NIL;
}
/*}}}*/

orcaData orcaData::operator_div(orcaVM* vm, orcaData& rhs) /*{{{*/
{
	mpz_t b, b_tmp;
	orcaData d;

	if (is<TYPE_INT>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT: 
			if (rhs.i() == 0) {
				throw orcaException(vm, "rt.math", "divide by 0");
			}

			return i() / rhs.i();

		case TYPE_BIGNUM: 
			mpz_init(b); 
			mpz_init(b_tmp);

			mpz_set_si(b_tmp, i());
			mpz_tdiv_q(b, b_tmp, rhs.bn());

			if (mpz_fits_sint_p(b)) {
				int j = mpz_get_si(b);
				mpz_clear(b);
				return j;
			}
			d.bn_set(b);
			mpz_clear(b);
			mpz_clear(b_tmp);
			return d;

		case TYPE_REAL:	
			if (rhs.r() == 0.0) {
				throw orcaException(vm, "rt.math", "divide by 0");
			}

			return i() / rhs.r();

		case TYPE_OBJ:		
			break;
		default:			
			return NIL;
		}
	}
	else if (is<TYPE_REAL>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT:
			if (rhs.i() == 0) {
				throw orcaException(vm, "rt.math", "divide by 0");
			}
	
			return r() / rhs.i();

		case TYPE_BIGNUM:
			return r() / mpz_get_d(rhs.bn());

		case TYPE_REAL:		
			if (rhs.r() == 0.0) {
				throw orcaException(vm, "rt.math", "divide by 0");
			}

			return r() / rhs.r();

		case TYPE_OBJ:		
			break;
		default:			
			return NIL;
		}
	}
	else if (is<TYPE_BIGNUM>(*this)) {

		switch(rhs.get_type())
		{
		case TYPE_INT:
			mpz_init(b);
			mpz_tdiv_q_ui(b, bn(), rhs.i());
			break;

		case TYPE_BIGNUM:
			mpz_init(b);
			mpz_tdiv_q(b, bn(), rhs.bn());
			break;
		
		case TYPE_REAL:
			return mpz_get_d(bn()) / rhs.r();

		case TYPE_OBJ:		
			break;
		default:			
			return NIL;
		}

		if (mpz_fits_sint_p(b)) {
			int j = mpz_get_si(b);
			mpz_clear(b);
			return j;
		}
		d.bn_set(b);
		mpz_clear(b);
		return d;
	}

	if (is<TYPE_OBJ>(*this)) {
		if (vm == NULL) vm = get_current_vm();
		orcaData ret = o()->operator_div(vm, rhs);
		if (!is<TYPE_NIL>(ret)) {
			return ret;
		}
	}

	if (is<TYPE_OBJ>(rhs)) {
		if (vm == NULL) vm = get_current_vm();
		return rhs.o()->operator_div_rev(vm, *this);
	}

	return NIL;
}
/*}}}*/

orcaData orcaData::operator_mod(orcaVM* vm, orcaData& rhs) /*{{{*/
{
	mpz_t b, b_tmp;
	orcaData d;

	if (is<TYPE_INT>(*this)) {
		switch(rhs.get_type())
		{
		case TYPE_INT: 
			if (rhs.i() == 0) {
				throw orcaException(vm, "rt.math", "divide by 0");
			}

			return i() % rhs.i();

		case TYPE_BIGNUM: 
			mpz_init(b); 
			mpz_init(b_tmp);

			mpz_set_si(b_tmp, i());
			mpz_mod(b, b_tmp, rhs.bn());

			if (mpz_fits_sint_p(b)) {
				int j = mpz_get_si(b);
				mpz_clear(b);
				return j;
			}

			d.bn_set(b);
			mpz_clear(b);
			mpz_clear(b_tmp);
			return d;

		default:			
			throw orcaException(vm, "orca.type", string("Integer type expected: ") + dump_str());
		}
	}
	else if (is<TYPE_BIGNUM>(*this)) {

		switch(rhs.get_type())
		{
		case TYPE_INT:
			mpz_init(b);
			mpz_mod_ui(b, bn(), rhs.i());
			break;

		case TYPE_BIGNUM:
			mpz_init(b);
			mpz_mod(b, bn(), rhs.bn());
			break;
		
		default:			
			throw orcaException(vm, "orca.type", string("Integer type expected: ") + rhs.dump_str());
		}

		if (mpz_fits_sint_p(b)) {
			int j = mpz_get_si(b);
			mpz_clear(b);
			return j;
		}

		d.bn_set(b);
		mpz_clear(b);
		return d;
	}
	else if (is<TYPE_STR>(*this)) {
		vector<orcaData> params;
		if (isobj<orcaTuple>(rhs)) {
			orcaTuple* tp = (orcaTuple*)rhs.o();
			orcatuple_iterator it = tp->begin();
			for(; it != tp->end(); ++it) {
				params.push_back(*it);
			}
		}
		else {
			params.push_back(rhs);
		}

		if (vm == NULL) vm = get_current_vm();
		return format_str(vm, this->s(), params);
	}
	else {
		throw orcaException(vm, "orca.type", string("Integer/string/type type expected: ") + dump_str());
	}

	return NIL;
}
/*}}}*/

orcaData orcaData::operator+(orcaData& rhs) /*{{{*/
{
	return operator_add(NULL, rhs);
}
/*}}}*/

orcaData orcaData::operator-(orcaData& rhs) /*{{{*/
{
	return operator_sub(NULL, rhs);
}
/*}}}*/

orcaData orcaData::operator*(orcaData& rhs) /*{{{*/
{
	return operator_mul(NULL, rhs);
}
/*}}}*/

orcaData orcaData::operator/(orcaData& rhs) /*{{{*/
{
	return operator_div(NULL, rhs);
}
/*}}}*/

orcaData orcaData::operator%(orcaData& rhs) /*{{{*/
{
	return operator_mod(NULL, rhs);
}
/*}}}*/

void orcaData::type_set(orcaData d)/*{{{*/
{
	t=TYPE_TYPE;
	v.type.t = d.get_type();
	switch (d.get_type())
	{
	case TYPE_OBJ:
		v.type.vp = d.o();
		break;

	default:
		v.type.vp = NULL;
	}
}
/*}}}*/

type_t& orcaData::type_get()/*{{{*/
{
	return v.type;
}
/*}}}*/

int orcaData::Integer()/*{{{*/
{
	switch(t)
	{
	case TYPE_INT:
		return i();

	case TYPE_REAL:
		return (int)r();

	case TYPE_STR:
		try {
			int i = boost::lexical_cast<int>(s());
			return i;
		}
		catch(...) {
			// fall through
		}
	}

	throw orcaException(NULL, "orca.type", string("Integer type expected: ") + dump_str());
	return 0;
}
/*}}}*/

double orcaData::Double()/*{{{*/
{
	switch(t)
	{
	case TYPE_INT:
		return (double)i();

	case TYPE_BIGNUM:
		return get_bn_double(bn());

	case TYPE_REAL:
		return r();

	case TYPE_STR:
		try {
			double r = boost::lexical_cast<double>(s());
			return r;
		}
		catch(...) {
			// fall through
		}
	}

	throw orcaException(NULL, "orca.type", string("floating type expected: ") + dump_str());
	return 0;
}
/*}}}*/

string& orcaData::String()/*{{{*/
{
	if (t != TYPE_STR) {
		throw orcaException(NULL, "orca.type", string("String type expected: ") + dump_str());
	}

	return s();
}
/*}}}*/

bool orcaData::Boolean()/*{{{*/
{
	if (t != TYPE_BOOL) {
		throw orcaException(NULL, "orca.type", string("Boolean type expected: ") + dump_str());
	}

	return i()?true:false;
}
/*}}}*/

orcaObject* orcaData::Object()/*{{{*/
{
	if (t != TYPE_OBJ) {
		throw orcaException(NULL, "orca.type", string("Object type expected: ") + dump_str());
	}

	return o();
}
/*}}}*/

bool orcaData::has_member(const char* c)/*{{{*/
{
	const string name = c;
	switch(get_type())
	{
	case TYPE_BOOL:
		if (name == "string")
			return true;
		break;

	case TYPE_BIGNUM:
	case TYPE_INT:
		if (name == "string" ||
			name == "float")
			return true;
		break;

	case TYPE_REAL:
		if (name == "string" ||
			name == "integer")
			return true;
		break;

	case TYPE_STR:
		if (name == "length" ||
			name == "find" ||
			name == "find_all" ||
			name == "strip" ||
			name == "lstrip" ||
			name == "rstrip" ||
			name == "integer" ||
			name == "float" ||
			name == "replace" ||
			name == "startWith")
			return true;
		break;

	case TYPE_OBJ:
		return o()->has_member(c);
	}

	return false;
}
/*}}}*/

void RC_Object::cleanup()/*{{{*/
{
		delete this;
}
/*}}}*/

void RC_Object::rc_inc() /*{{{*/
{
	pthread_mutex_lock(&g_rc_mutex);
	m_rc++;
	pthread_mutex_unlock(&g_rc_mutex);
}
/*}}}*/

void RC_Object::rc_dec() /*{{{*/
{
	pthread_mutex_lock(&g_rc_mutex);
	m_rc--;
	pthread_mutex_unlock(&g_rc_mutex);
	if (m_rc <= 0) {
		cleanup();
	}
}
/*}}}*/

int RC_Object::get_rc() /*{{{*/
{
	return m_rc;
}
/*}}}*/

void RC_Object::set_rc(int rc) /*{{{*/
{
	pthread_mutex_lock(&g_rc_mutex);
	m_rc = rc;
	pthread_mutex_unlock(&g_rc_mutex);
}
/*}}}*/

void RC_Object::reuse() 	// use carefully !!!/*{{{*/
{
	pthread_mutex_lock(&g_rc_mutex);
	m_rc++;
	pthread_mutex_unlock(&g_rc_mutex);
}
/*}}}*/

void ReObject::reset(const string& s)			/*{{{*/
{ 
	try {
		re = str = s; 
	}
	catch(...) {
		throw orcaException(NULL, "orca.regex", "regex format is invalid");
	}
}
/*}}}*/




