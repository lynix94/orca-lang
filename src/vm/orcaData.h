/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaData.h - basic orca data types

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_DATA
#define _DEF_ORCA_DATA

#include "porting.h"

#include <string>
#include <boost/regex.hpp>
#include <gmp.h>

#include "orca_common.h"

using namespace std;

class orcaObject;
struct CatchList;
class orcaVM;
struct orcaData;

#define SIZE_INTERNAL_VALUE	(sizeof(orcaType) + sizeof(double))

enum orcaType 
{
	TYPE_NIL = 0,
	TYPE_INT,
	TYPE_BIGNUM,
	TYPE_REAL,
	TYPE_BOOL,
	TYPE_STR,
	TYPE_REGEX,
	TYPE_OBJ,
	TYPE_PAIR,
	TYPE_INTERNAL,
	TYPE_NATIVE,
	TYPE_TYPE,
	TYPE_EXTRACT,

	TYPE_MARK,
};

struct IntPair 
{
	int from;
	int to;
};

struct Native 
{
	orcaObject* owner;
	orcaData (orcaObject::*fp)(orcaVM* vm, int param_n);
	const char* name;
};


class orcaObject;
class StringObject;
class ReObject;
class BnObject;
union u_internal
{
	int i;
	double r;
	orcaObject* o;
	
	StringObject* so;
	ReObject* ro;
	BnObject* bo;
};

struct InternalFunction
{
	int idx;
	const char* name;
	u_internal owner;
};

class LIBORCA_API RC_Object /*{{{*/
{
public:
	RC_Object() : m_rc(0) { }
	virtual ~RC_Object() { }

	void rc_inc();
	void rc_dec();
	int get_rc();
	void set_rc(int rc);
	void reuse();

	virtual void cleanup();

protected:
	int m_rc;
};
/*}}}*/

class StringObject : public RC_Object /*{{{*/
{
public:
	StringObject()					{ }
	virtual ~StringObject()			{ }

	StringObject(string& s)			{ this->s = s; }

	StringObject(const string& s)	{ this->s = s; }
	StringObject(char* s)			{ this->s = s; }
	StringObject(char* s, int len)	{ 
		this->s.resize(len);
		copy(s, s+len, &this->s[0]);
	}

	string s;
};
/*}}}*/

class ReObject : public RC_Object/*{{{*/
{
public:
	ReObject()					{ }
	virtual ~ReObject()			{ }

	ReObject(string& s)			{ reset(s); }
	ReObject(const string& s)	{ reset(s); }
	ReObject(char* s)			{ reset(s); }

	void set(string& s)			{ reset(s); }
	void set(const string& s)	{ reset(s); }
	void set(char* s)			{ reset(s); }

	void reset(const string& s);
	boost::regex re;
	string str;
};
/*}}}*/

class BnObject : public RC_Object/*{{{*/
{
public:
	BnObject()			{ mpz_init(bn); }
	virtual ~BnObject()	{ mpz_clear(bn); }

	BnObject(mpz_t& b)	{ mpz_init(bn); mpz_set(bn, b); }
	BnObject(long long ll)	
	{
		mpz_init(bn); 
		if (ll < INT_MAX) {
			mpz_set_si(bn, (int)ll); 
		}
		else {
			char buff[128];
			sprintf(buff, "%lld", ll);
			mpz_set_str(bn, buff, 10);
		}
	}

	BnObject(const char* s)	
	{
		mpz_init(bn);

		bool minus = false;
		if (*s == '+') s++;
		else if (*s == '-') {
			minus = true;
			s++;
		}

		mpz_set_str(bn, s, 10);
		if (minus) {
			mpz_neg(bn, bn);
		}
	}

	mpz_t bn;
};
/*}}}*/

enum mark_e
{
	MARK_CATCH,
	MARK_SCOPE,
	MARK_FOR,
	MARK_DECODE,
	MARK_STACK,
	MARK_SWITCH,
	MARK_SELECT,
};

struct mark_t 
{
	mark_e type;
	void* vp;
};

struct type_t
{
	orcaType t;
	void* vp;
};


union Value 
{
	int i;
	double r;
	orcaObject* o;
	
	StringObject* so;
	ReObject* ro;
	BnObject* bo;

	// internal
	IntPair sl;
	Native n;
	InternalFunction internal;
	type_t type;

	mark_t mark;
};

typedef orcaData (orcaObject::*object_fp)(orcaVM* vm, int param_n);

struct LIBORCA_API orcaData 
{
	friend class orcaTypes;

	// con & des
	orcaData() : t(TYPE_NIL)						{ }
	orcaData(int val) : t(TYPE_INT)					{ v.i = val; }
	orcaData(size_t val) : t(TYPE_INT)				{ v.i = val; }
	orcaData(double val) : t(TYPE_REAL)				{ v.r = val; }
	orcaData(bool val) : t(TYPE_BOOL)				{ v.i = val?1:0; }
	orcaData(const orcaData& d) : t(d.t)			{ v = d.v; }
	orcaData(orcaObject* val) : t(TYPE_OBJ)			{ v.o = val; }
	orcaData(string &s) : t(TYPE_STR)				{ v.so = new StringObject(s); }
	orcaData(const string &s) : t(TYPE_STR)			{ v.so = new StringObject(s); }
	orcaData(char* s) : t(TYPE_STR)					{ v.so = new StringObject(s); }
	orcaData(const char* s) : t(TYPE_STR)			{ v.so = new StringObject((char*)s); }
	orcaData(char* s, int len) : t(TYPE_STR)		{ v.so = new StringObject(s, len); }
	orcaData(const char* s, int len) : t(TYPE_STR)	{ v.so = new StringObject((char*)s, len); }
	orcaData(mpz_t& bn) : t(TYPE_BIGNUM)				{ v.bo = new BnObject(bn); }
	orcaData(long long ll) : t(TYPE_BIGNUM)			{ v.bo = new BnObject(ll); }
	orcaData(orcaObject* o, object_fp fp, const char* name);

	void rc_inc();
	void rc_dec();
	int get_rc();
	void set_rc(int rc);

	// object management
	orcaData clone(orcaObject* owner = NULL);
	orcaData clone_object(orcaObject* owner = NULL);
	long long id();

	// printing & debugging
	void string_(orcaVM* vm, string& str) const;
	string string_(orcaVM* vm) const;
	void repr(orcaVM* vm, string& str) const;
	string repr(orcaVM* vm) const;
	void dump() const;
	char* dump(char* buff) const;
	string dump_str() const;

	// data read
	int& ir()						{ return v.i; }	// for fast mod
	int i()							{ return v.i; }
	double r()						{ return v.r; }
	bool b()						{ return v.i == 1 ? true : false; }
	orcaObject* o()					{ return v.o; }
	StringObject* so()				{ return v.so; }
	string& s()	const				{ return v.so->s; }
	Native& n()						{ return v.n; }
	ReObject* ro()					{ return v.ro; }
	BnObject* bo()					{ return v.bo; }
	mpz_t& bn()						{ return v.bo->bn; }
	boost::regex& re()				{ return v.ro->re; }
	string& re_str() const			{ return v.ro->str; }
	IntPair& sl()					{ return v.sl; }
	InternalFunction& internal()	{ return v.internal; }

	mark_t& mark()					{ return v.mark; }
	
	// for change ( use orcaData for creation() )
	void i(int i)					{ v.i = i; } 
	void b(bool b)					{ b==true ? v.i = 1 : v.i = 0; }
	void r(double r)				{ v.r = r; }
	void o(orcaObject* o)			{ v.o = o; }
	void s(string& s)				{ v.so->s.swap(s); }
	void s(const string& s)			{ v.so->s = s; }
	void s(char* s)					{ v.so->s = s; }
	void re(string& s)				{ v.ro->set(s); }
	void re(char* s)				{ v.ro->set(s); }
	void bn(mpz_t b)				{ mpz_set(v.bo->bn, b); }
	void internal(int idx, const char* name)
									{ 
										v.internal.idx = idx;
										v.internal.name = name;
									}
	

	void i_set(int i)				{ t=TYPE_INT; v.i = i; } 
	void r_set(double r)			{ t=TYPE_REAL; v.r = r; }
	void o_set(orcaObject* o)		{ t=TYPE_OBJ; v.o = o; }
	void s_set(const string& s)		{ t=TYPE_STR; v.so = new StringObject(s); }
	void s_set(string& s)			{ t=TYPE_STR; v.so = new StringObject(s); }
	void s_set(char* s)				{ t=TYPE_STR; v.so = new StringObject(s); }
	void s_set(const char* s)				{ t=TYPE_STR; v.so = new StringObject(s); }
	void re_set(string& s)			{ t=TYPE_REGEX; v.ro = new ReObject(s); }
	void re_set(const string& s)	{ t=TYPE_REGEX; v.ro = new ReObject(s); }
	void re_set(char* s)			{ t=TYPE_REGEX; v.ro = new ReObject(s); }
	void bn_set(mpz_t& bn)			{ t=TYPE_BIGNUM; v.bo = new BnObject(bn); }
	void bn_set(const char* s)		{ t=TYPE_BIGNUM; v.bo = new BnObject(s); }
	void bn_set(long long ll)		{ t=TYPE_BIGNUM; v.bo = new BnObject(ll); }
	void pair_set(int i, int j)		{ t=TYPE_PAIR; v.sl.from=i; v.sl.to=j; }
	void extract_set(orcaObject* o)	{ t=TYPE_EXTRACT; v.o = o; }

	void type_set(orcaData d);
	type_t& type_get();

	void mark_catch(CatchList* c)	{ 
		t=TYPE_MARK; 
		v.mark.type = MARK_CATCH; 
		v.mark.vp = (void*)c; 
	}
 
	void mark_scope(orcaObject* o)	{
		t=TYPE_MARK;
		v.mark.type = MARK_SCOPE;
		v.mark.vp = (void*)o; 
	}

	void mark_for() {
		t=TYPE_MARK;
		v.mark.type = MARK_FOR;
		v.mark.vp = NULL;
	}

	void mark_decode() {
		t=TYPE_MARK;
		v.mark.type = MARK_DECODE;
		v.mark.vp = NULL;
	}

	void mark_stack() {
		t=TYPE_MARK;
		v.mark.type = MARK_STACK;
		v.mark.vp = NULL;
	}

	void mark_switch() {
		t=TYPE_MARK;
		v.mark.type = MARK_SWITCH;
		v.mark.vp = NULL;
	}

	void mark_select() {
		t=TYPE_MARK;
		v.mark.type = MARK_SELECT;
		v.mark.vp = NULL;
	}


	// native call
	orcaData native_call(orcaVM* vm, int param_n);

	void set_type(orcaType type)	{ t = type; }
	orcaType get_type() const		{ return t; }

	// operators
	orcaData operator_add(orcaVM* vm, orcaData& rhs);
	orcaData operator_sub(orcaVM* vm, orcaData& rhs);
	orcaData operator_mul(orcaVM* vm, orcaData& rhs);
	orcaData operator_div(orcaVM* vm, orcaData& rhs);
	orcaData operator_mod(orcaVM* vm, orcaData& rhs);

	orcaData operator_and(orcaVM* vm, orcaData& rhs);
	orcaData operator_or(orcaVM* vm, orcaData& rhs);
	orcaData operator_lt(orcaVM* vm, orcaData& rhs);
	orcaData operator_le(orcaVM* vm, orcaData& rhs);
	orcaData operator_gt(orcaVM* vm, orcaData& rhs);
	orcaData operator_ge(orcaVM* vm, orcaData& rhs);
	orcaData operator_eq(orcaVM* vm, orcaData& rhs);
	orcaData operator_neq(orcaVM* vm, orcaData& rhs);

	orcaData operator+(orcaData& rhs);
	orcaData operator-(orcaData& rhs);
	orcaData operator*(orcaData& rhs);
	orcaData operator/(orcaData& rhs);
	orcaData operator%(orcaData& rhs);

	bool operator<(const orcaData& rhs) const;
	bool operator<(orcaData& rhs);
	bool operator<=(orcaData& rhs);
	bool operator>(orcaData& rhs);
	bool operator>=(orcaData& rhs);
	bool operator==(orcaData& rhs);
	bool operator!=(orcaData& rhs);

	// for interface
	int Integer();
	double Double();
	string& String();
	bool Boolean();
	orcaObject* Object();


	// str.push_back only
	void __so_set__(StringObject* so)	{ t=TYPE_STR; v.so = so; }
private:
	orcaType t;
	Value v;
};

#ifdef WINDOWS
__declspec(dllimport) orcaData NIL; 
#else
extern orcaData NIL; 
#endif

template <orcaType T>
inline bool is(orcaData d) 
{
	return (d.get_type() == T);
}

template <orcaType T> 
inline bool isall(orcaData d1, orcaData d2)
{
	return (d1.get_type() == T) && (d2.get_type() == T);
}

template <class T>
inline bool isobj(orcaData d)
{
	return (d.get_type() == TYPE_OBJ) && (dynamic_cast<T*>(d.o()) != NULL);
}

inline bool isinternal(orcaData d)
{
	switch(d.get_type())
	{
	case TYPE_INT:
	case TYPE_BIGNUM:
	case TYPE_REAL:
	case TYPE_STR:
	case TYPE_BOOL:
		return true;
	}

	return false;
}

template <class T>
inline T* castobj(orcaData d)
{
	return dynamic_cast<T*>(d.Object());
}

inline bool istrue(orcaData d)
{
	switch(d.get_type())
	{
	case TYPE_NIL:		return false;
	case TYPE_INT:
	case TYPE_REAL:		return d.Integer()!=0?true:false;
	case TYPE_BIGNUM:	return d.Double()!=0?true:false;
	case TYPE_BOOL:		return d.b();
	case TYPE_STR:		return d.s().length()>0?true:false;
	}

	return true;
}

inline bool isfalse(orcaData d)
{
	return !istrue(d);
}



string format_str(orcaVM* vm, string& format, vector<orcaData>& params);
string format_str(orcaVM* vm, string& format, orcaData d);
string get_bn_string(mpz_t& bn);
double get_bn_double(mpz_t& bn); 

#endif


